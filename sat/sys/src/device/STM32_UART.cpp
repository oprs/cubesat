
#include "device/STM32_RCC.h"
#include "device/NVIC.h"
#include "device/STM32_UART.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_UART::STM32_UART( Bus& bus,
            const uint32_t iobase,
            const uint32_t periph,
            const char    *name,
            GPIO::Pin&     rxPin,
            GPIO::Pin&     txPin,
            const uint32_t IRQn,
            GPIO::Alt      alt )
   : UART( name ), BusSlave( bus, iobase, periph ),
     _rxFIFO( FIFO<uint8_t>( 64 )),
     _txFIFO( FIFO<uint8_t>( 64 )),
     _rxPin ( rxPin ),
     _txPin ( txPin ),
     _IRQn  ( IRQn  ),
     _alt   ( alt   )
{
   _isrRXNE = xSemaphoreCreateBinary();
   _isrTXE  = xSemaphoreCreateBinary();
}


STM32_UART::~STM32_UART()
{
   vSemaphoreDelete( _isrTXE );
   vSemaphoreDelete( _isrRXNE );
}


//  - - - - - - - - - - - - - - - -  //
//  P U B L I C   I N T E R F A C E  //
//  - - - - - - - - - - - - - - - -  //

STM32_UART& STM32_UART::init( void )
{
   LOG << _name << ": STM32 UART controller at " << bus.name
       << ", rx: " << _rxPin.name()
       << ", tx: " << _txPin.name()
       ;

   return *this;
}


STM32_UART& STM32_UART::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _rxPin.enable().pullUp().alt( _alt );
   _txPin.enable().pullUp().alt( _alt );

   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   RCC.enable( this, silent );

   USARTx->CR1 = USART_CR1_TE | USART_CR1_RE;
   USARTx->CR2 = 0;
   USARTx->CR3 = 0;

   baudRate( 9600 );

   USARTx->CR1 |= ( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   IRQ.enable( _IRQn );

   return *this;
}


STM32_UART& STM32_UART::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   IRQ.disable( _IRQn );
   USARTx->CR1 &= ~( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   RCC.disable( this, silent );

   _txPin.disable();
   _rxPin.disable();

   return *this;
}


size_t STM32_UART::read( void *x, size_t len )
{
   size_t n = 0;

   while( n < len ) {
      if( _rxFIFO.isEmpty() ) {
         xSemaphoreTake( _isrRXNE, portMAX_DELAY );
         continue;
      }

      ((uint8_t*)x)[ n++ ] = _rxFIFO.pull();
   }

   return n;
}


size_t STM32_UART::readLine( void *x, size_t len )
{
   uint8_t ch = 0x00;
   size_t   n = 0;

   while( n < len ) {
      if( _rxFIFO.isEmpty() ) {
         xSemaphoreTake( _isrRXNE, portMAX_DELAY );
         continue;
      }

      ch = _rxFIFO.pull();

      if( ch == 0x0a ) continue;
      if( ch == 0x0d ) break;

      ((uint8_t*)x)[ n++ ] = ch;
   }

   while( ch != 0x0d ) {
      if( _rxFIFO.isEmpty() ) {
         xSemaphoreTake( _isrRXNE, portMAX_DELAY );
         continue;
      }

      ch = _rxFIFO.pull();
   }

   return n;
}


size_t STM32_UART::write( const void *x, size_t len )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   size_t n = 0;

   while( n < len ) {
      if( _txFIFO.isFull() ) {
         xSemaphoreTake( _isrTXE, portMAX_DELAY );
         continue;
      }
      (void)_txFIFO.push( ((uint8_t*)x)[ n++ ] );
   }
   USARTx->CR1 |= USART_CR1_TXEIE;

   return n;
}


STM32_UART& STM32_UART::baudRate( unsigned rate )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   uint32_t idiv, fdiv;
   uint32_t tmp32;

   /* assuming oversampling by 16 (CR1.OVER8 = 0) */

   idiv   = ( 25 * RCC.freq( bus )) / ( 4 * rate );
   tmp32  = idiv / 100;
   fdiv   = idiv - ( 100 * tmp32 );
   tmp32  = tmp32 << 4;
   tmp32 |= ((( fdiv << 4 ) + 50 ) / 100 ) & 0x0f;

   USARTx->BRR = (uint16_t)tmp32;

   LOG << _name << ": Baud rate set to " << rate;

   return *this;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void STM32_UART::isr( void )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
   portBASE_TYPE hpTask  = pdFALSE;

   uint16_t SR = USARTx->SR;
   uint16_t DR = USARTx->DR;

   if( SR & USART_SR_RXNE ) {
      USARTx->SR &= ~USART_SR_RXNE;
      if( !_rxFIFO.isFull() ) {
         (void)_rxFIFO.push( DR & 0xff );
         xSemaphoreGiveFromISR( _isrRXNE, &hpTask );
      }
   }

   if( SR & USART_SR_TXE ) {
      USARTx->SR &= ~USART_SR_TXE;
      if( _txFIFO.isEmpty() ) {
         USARTx->CR1 &= ~USART_CR1_TXEIE;
      } else {
         USARTx->DR = _txFIFO.pull();
         xSemaphoreGiveFromISR( _isrTXE, &hpTask );
      }
   }

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
}

/*EoF*/
