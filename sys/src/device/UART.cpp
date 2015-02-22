
#include "device/UART.h"

#include <stm32f4xx.h>
#include <misc.h>
#include <stm32f4xx_usart.h>

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
   return *this;
}


UART& UART::enable( void )
{
   NVIC_InitTypeDef  NVICis;
   USART_InitTypeDef USARTis;

   _rxPin.enable()
         .pullUp()
         .alt( _alt );

   _txPin.enable()
         .pullUp()
         .alt( _alt );

   bus.enable( this );

   USARTis.USART_BaudRate                   = 115200; // 9600;
   USARTis.USART_WordLength                 = USART_WordLength_8b;
   USARTis.USART_StopBits                   = USART_StopBits_1;
   USARTis.USART_Parity                     = USART_Parity_No;
   USARTis.USART_HardwareFlowControl        = USART_HardwareFlowControl_None;
   USARTis.USART_Mode                       = USART_Mode_Rx | USART_Mode_Tx;
   USART_Init(( USART_TypeDef* )iobase, &USARTis );

   NVICis.NVIC_IRQChannelPreemptionPriority = 0x0f;
   NVICis.NVIC_IRQChannelSubPriority        = 0x00;
   NVICis.NVIC_IRQChannelCmd                = ENABLE;

   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
   NVICis.NVIC_IRQChannel = _IRQn;

   USART_ITConfig(( USART_TypeDef* )iobase, USART_IT_RXNE, ENABLE );
 //USART_ITConfig(( USART_TypeDef* )iobase, USART_IT_TXE, ENABLE );

   NVIC_Init( &NVICis );
   USART_Cmd(( USART_TypeDef* )iobase, ENABLE );

   return *this;
}


UART& UART::disable( void )
{
   bus.disable( this );
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
      USARTx->CR1 |= USART_FLAG_TXE;
      xSemaphoreTake( _isrTXE, portMAX_DELAY );
      USARTx->DR = ((uint8_t*)x)[ n ];
   }

   xSemaphoreGive( _wrLock );

   return n;
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
