
#include "device/UART.h"

#include <iostream>
#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

UART::UART( Bus& bus,
	         const uint32_t iobase,
	         const uint32_t periph,
	         const char    *name,
	         GPIOPin&       rxPin,
	         GPIOPin&       txPin,
	         const uint32_t IRQn,
	         GPIOPin::Alt   alt )
	: BusDevice( bus, iobase, periph, name ),
	  _fo    ( FIFO<uint8_t>(512) ),
	  _rxPin ( rxPin ),
	  _txPin ( txPin ),
	  _IRQn  ( IRQn  ),
	  _alt   ( alt   )
{
	_rdLock  = xSemaphoreCreateMutex();
	_wrLock  = xSemaphoreCreateMutex();
	_isrRXNE = xSemaphoreCreateBinary();
}


UART::~UART()
{
	disable();

	vSemaphoreDelete( _wrLock );
	vSemaphoreDelete( _rdLock );
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

UART& UART::enable( void )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

	if( _incRef() > 0 )
		return *this;

	bus.enable( this );

	std::cout << _name << ": System UART controller at " << bus.name()
	          << ", rx: " << _rxPin.name()
	          << ", tx: " << _txPin.name()
	          << "\r\n";

	_rxPin.enable()
	      .pullUp()
	      .alt( _alt );

	_txPin.enable()
	      .pullUp()
	      .alt( _alt );

	USARTx->CR1 = USART_CR1_TE | USART_CR1_RE;
	USARTx->CR2 = 0;
	USARTx->CR3 = 0;

	baudRate( 9600 );

	USARTx->CR1 |= ( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
	IRQ.enable( _IRQn );

	return *this;
}


UART& UART::disable( void )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

	IRQ.disable( _IRQn );
	USARTx->CR1 &= ~( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
	bus.disable( this );

	_txPin.disable();
	_rxPin.disable();

	return *this;
}


size_t UART::read( void *x, size_t len )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
	size_t n;

	xSemaphoreTake( _rdLock, portMAX_DELAY );

	for( n = 0 ; n < len ; ++n ) {
		xSemaphoreTake( _isrRXNE, portMAX_DELAY );
		((uint8_t*)x)[ n ] = USARTx->DR;
	}

	xSemaphoreGive( _rdLock );

	return n;
}


size_t UART::readLine( void *x, size_t len )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

	uint16_t dr;
	size_t n = 0;

	xSemaphoreTake( _rdLock, portMAX_DELAY );

	while( n < len ) {
		xSemaphoreTake( _isrRXNE, portMAX_DELAY );
		dr = USARTx->DR;

		if( dr == 0x0a ) break;
		if( dr == 0x0d ) continue;

		((uint8_t*)x)[ n++ ] = (uint8_t)dr & 0xff;
	}

	while( dr != 0x0a ) {
		xSemaphoreTake( _isrRXNE, portMAX_DELAY );
		dr = USARTx->DR;
	}

	xSemaphoreGive( _rdLock );

	return n;
}


size_t UART::write( const void *x, size_t len )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
	size_t n;

	xSemaphoreTake( _wrLock, portMAX_DELAY );

	/*
	 * write() might be called early, ie. before the UART is enabled
	 * (boot process), in that case just feed the fifo and return
	 */

	if( _refCount == 0 ) {
		for( n = 0 ; n < len ; ++n ) {
			if( _fo.isFull() ) break;
			(void)_fo.push( ((uint8_t*)x)[ n ] );
		}

		xSemaphoreGive( _wrLock );
		return n;
	}

	/*
	 * otherwise (UART is enabled), make sure that TXE interrupts are
	 * disabled so that we can safely fill up the fifo
	 */

	USARTx->CR1 &= ~USART_CR1_TXEIE;

	/*
	 * any data not fitting in is just discarded;  overruns should not
	 * be a problem since we're not transmitting _that_ much data over
	 * the UARTs (except perhaps debug output, but who cares)
	 */

	for( n = 0 ; n < len ; ++n ) {
		if( _fo.isFull() ) break;
		(void)_fo.push( ((uint8_t*)x)[ n ] );
	}

	/*
	 * enable TXE interrupts again, and let the ISR pull from the fifo
	 * at its own pace (= baud rate for this UART)
	 */

	USARTx->CR1 |= USART_CR1_TXEIE;

	xSemaphoreGive( _wrLock );
	return n;
}


UART& UART::baudRate( unsigned rate )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

	uint32_t idiv, fdiv;
	uint32_t tmp32;

	/* assuming oversampling by 16 (CR1.OVER8 = 0) */

	idiv   = ( 25 * bus.freq() ) / ( 4 * rate );
	tmp32  = idiv / 100;
	fdiv   = idiv - ( 100 * tmp32 );
	tmp32  = tmp32 << 4;
	tmp32 |= ((( fdiv << 4 ) + 50 ) / 100 ) & 0x0f;

	USARTx->BRR = (uint16_t)tmp32;

	std::cout << _name << ": Baud rate set to " << rate << "\r\n";

	return *this;
}

//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void UART::isr( void )
{
	USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
	portBASE_TYPE hpTask  = pdFALSE;

	if( USARTx->SR & USART_SR_RXNE) {
		USARTx->SR &= ~USART_SR_RXNE;
		xSemaphoreGiveFromISR( _isrRXNE, &hpTask );
	}

	if( USARTx->SR & USART_SR_TXE ) {
		if( _fo.isEmpty() ) {
			USARTx->CR1 &= ~USART_CR1_TXEIE;
			USARTx->SR  &= ~USART_SR_TXE;
		} else {
			USARTx->DR = _fo.pull();
		}
	}

	if( hpTask == pdTRUE )
		portEND_SWITCHING_ISR( hpTask );
}


/* trampolines */

#undef UART4
#undef UART5

void USART1_IRQHandler( void )
{ qb50::UART1.isr(); }

void USART2_IRQHandler( void )
{ qb50::UART2.isr(); }

void USART3_IRQHandler( void )
{ qb50::UART3.isr(); }

void UART4_IRQHandler( void )
{ qb50::UART4.isr(); }

void UART5_IRQHandler( void )
{ qb50::UART5.isr(); }

void USART6_IRQHandler( void )
{ qb50::UART6.isr(); }


/*EoF*/
