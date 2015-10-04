
#include "device/UART.h"
#include "system/Logger.h"

#include <stm32f4xx.h>

using namespace qb50;


static void _trampoline( void *x );


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
     _rxFIFO( FIFO<uint8_t>(   64 )),
     _txFIFO( FIFO<uint8_t>( 2048 )),
     _rxPin ( rxPin ),
     _txPin ( txPin ),
     _IRQn  ( IRQn  ),
     _alt   ( alt   )
{
   _isrRXNE = xSemaphoreCreateBinary();
   _ioQueue = xQueueCreate( 1, sizeof( IOReq* ));
   _enabled = false;
}


UART::~UART()
{
   vQueueDelete( _ioQueue );
   vSemaphoreDelete( _isrRXNE );
}


//  - - - - - - - - - - - - - - - -  //
//  P U B L I C   I N T E R F A C E  //
//  - - - - - - - - - - - - - - - -  //

UART& UART::init( void )
{
   (void)xTaskCreate( _trampoline, _name, 512, this, configMAX_PRIORITIES - 1, &_ioTask );

   LOG << _name << ": System UART controller at " << bus.name()
       << ", rx: " << _rxPin.name()
       << ", tx: " << _txPin.name()
       ;

   return *this;
}


UART& UART::ioctl( IOReq *req, TickType_t maxWait )
{
   (void)xQueueSend( _ioQueue, &req, maxWait );
   (void)ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
   return *this;
}


UART& UART::enable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( ENABLE );
   return ioctl( &req );
}


UART& UART::disable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( DISABLE );
   return ioctl( &req );
}


size_t UART::read( void *x, size_t len )
{
   IOReq_read req( x, len );
   (void)ioctl( &req );
   return req._len;
}


size_t UART::readLine( void *x, size_t len )
{
   IOReq_readLine req( x, len );
   (void)ioctl( &req );
   return req._len;
}


size_t UART::write( const void *x, size_t len )
{
   IOReq_write req( x, len );

   if( _enabled )
      (void)ioctl( &req );
   else
      _write( &req );

   return req._len;
}


UART& UART::baudRate( unsigned rate )
{
   IOReq_baudRate req( rate );
   return ioctl( &req );
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

static void _trampoline( void *x )
{
   UART *self = (UART*)x;
   self->run();
   vTaskDelete( NULL );
}


void UART::run( void )
{
   IOReq *req;

   for( ;; ) {
      if( xQueueReceive( _ioQueue, &req, portMAX_DELAY ) != pdPASS )
         continue;

      _lock();

      switch( req->_op ) {
         case ENABLE:   _enable   (                  req ); break;
         case DISABLE:  _disable  (                  req ); break;
         case READ:     _read     (     (IOReq_read*)req ); break;
         case READLINE: _readLine ( (IOReq_readLine*)req ); break;
         case WRITE:    _write    (    (IOReq_write*)req ); break;
         case BAUDRATE: _baudRate ( (IOReq_baudRate*)req ); break;
      }

      _unlock();
      (void)xTaskNotifyGive( req->_handle );
   }
}


void UART::_enable( IOReq *req )
{
   (void)req;

   if( _incRef() > 0 )
      return;

   _rxPin.enable().pullUp().alt( _alt );
   _txPin.enable().pullUp().alt( _alt );

   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   bus.enable( this );

   USARTx->CR1 = USART_CR1_TE | USART_CR1_RE;
   USARTx->CR2 = 0;
   USARTx->CR3 = 0;

   {
      IOReq_baudRate req( 9600 );
      _baudRate( &req );
   }

   USARTx->CR1 |= ( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   IRQ.enable( _IRQn );

   _enabled = true;
}


void UART::_disable( IOReq *req )
{
   (void)req;

   if( _decRef() > 0 )
      return;

   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   IRQ.disable( _IRQn );
   USARTx->CR1 &= ~( USART_CR1_UE | USART_CR1_RXNEIE | USART_CR1_TXEIE );
   bus.disable( this );

   bus.disable( this );

   _txPin.disable();
   _rxPin.disable();
}


void UART::_read( IOReq_read *req )
{
   uint8_t *x = (uint8_t*)req->_x;
   size_t len = req->_len;
   size_t   n = 0;

   while( n < len ) {
      if( _rxFIFO.isEmpty() ) {
         xSemaphoreTake( _isrRXNE, portMAX_DELAY );
         continue;
      }

      ((uint8_t*)x)[ n++ ] = _rxFIFO.pull();
   }

   req->_len = n;
}


void UART::_readLine( IOReq_readLine *req )
{
   uint8_t *x = (uint8_t*)req->_x;
   size_t len = req->_len;
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

   req->_len = n;
}


void UART::_write( IOReq_write *req )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   const uint8_t *x = (const uint8_t*)req->_x;
   size_t len = req->_len;
   size_t n;

   if( _refCount != 0 )
      USARTx->CR1 &= ~USART_CR1_TXEIE;

   for( n = 0 ; n < len ; ++n ) {
      if( _txFIFO.isFull() ) break;
      (void)_txFIFO.push( ((uint8_t*)x)[ n ] );
   }

   if(( _refCount != 0 ) && ( !_txFIFO.isEmpty() ))
      USARTx->CR1 |= USART_CR1_TXEIE;

   req->_len = n;
}


void UART::_baudRate( IOReq_baudRate *req )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;

   uint32_t idiv, fdiv;
   uint32_t tmp32;

   /* assuming oversampling by 16 (CR1.OVER8 = 0) */

   idiv   = ( 25 * bus.freq() ) / ( 4 * req->_rate );
   tmp32  = idiv / 100;
   fdiv   = idiv - ( 100 * tmp32 );
   tmp32  = tmp32 << 4;
   tmp32 |= ((( fdiv << 4 ) + 50 ) / 100 ) & 0x0f;

   USARTx->BRR = (uint16_t)tmp32;

   LOG << _name << ": Baud rate set to " << req->_rate;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void UART::isr( void )
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
/*
void UART4_IRQHandler( void )
{ qb50::UART4.isr(); }

void UART5_IRQHandler( void )
{ qb50::UART5.isr(); }
*/
void USART6_IRQHandler( void )
{ qb50::UART6.isr(); }


/*EoF*/
