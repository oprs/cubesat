
#include "device/UART.h"

#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

UART::UART( Bus& bus,
            const uint32_t iobase,
            const uint32_t periph,
            GPIOPin&       rxPin,
            GPIOPin&       txPin,
            const uint32_t IRQn,
            GPIOPin::Alt   alt )
   : BusDevice( bus, iobase, periph ),
     _rxPin( rxPin ),
     _txPin( txPin ),
     _IRQn( IRQn ),
     _alt( alt )
{
   _rdLock  = xSemaphoreCreateMutex();
   _wrLock  = xSemaphoreCreateMutex();
   _isrRXNE = xSemaphoreCreateBinary();
   _isrTXE  = xSemaphoreCreateBinary();

   reset();
}


UART::~UART()
{
   reset();
   disable();

   vSemaphoreDelete( _wrLock );
   vSemaphoreDelete( _rdLock );
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

UART& UART::reset( void )
{
   USART_TypeDef *UARTx = (USART_TypeDef*)iobase;

   bus.enable( this );

   UARTx->CR1 = USART_CR1_TE | USART_CR1_RE;
   UARTx->CR2 = 0;
   UARTx->CR3 = 0;

   baudRate( 115200 );
   //baudRate( 9600 );

   bus.disable( this );

   return *this;
}


UART& UART::enable( void )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   _rxPin.enable()
         .pullUp()
         .alt( _alt );

   _txPin.enable()
         .pullUp()
         .alt( _alt );

   bus.enable( this );

 //USARTx->CR1 |= ( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   USARTx->CR1 |= ( USART_CR1_UE | USART_CR1_RXNEIE );
   IRQ.enable( _IRQn );

   return *this;
}


UART& UART::disable( void )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   IRQ.disable( _IRQn );
   USARTx->CR1 &= ~( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   bus.disable( this );

   _txPin.reset()
         .disable();

   _rxPin.reset()
         .disable();

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


size_t UART::write( const void *x, size_t len )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
   size_t n;

   xSemaphoreTake( _wrLock, portMAX_DELAY );

   for( n = 0 ; n < len ; ++n ) {
      USARTx->CR1 |= USART_CR1_TXEIE;
      xSemaphoreTake( _isrTXE, portMAX_DELAY );
      USARTx->DR = ((uint8_t*)x)[ n ];
   }

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
      USARTx->SR &= ~USART_SR_TXE;
      xSemaphoreGiveFromISR( _isrTXE, &hpTask );
      USARTx->CR1 &= ~USART_SR_TXE;
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
