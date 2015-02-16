
#include "device/UART.h"
#include "device/GPIO.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

UART::UART( Bus&           bus,
            const uint32_t periph,
            const uint32_t iobase,
            GPIOPin&       rxPin,
            GPIOPin&       txPin )
   : CoreDevice( bus, periph, iobase ),
     _rxPin( rxPin ),
     _txPin( txPin )
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

void UART::reset( void )
{ ; }


void UART::enable( void )
{
   bus.enable( this );

   GPIO_InitTypeDef  GPIOis;
   NVIC_InitTypeDef  NVICis;
   USART_InitTypeDef USARTis;

   GPIOis.GPIO_Mode                         = GPIO_Mode_AF;
   GPIOis.GPIO_Speed                        = GPIO_Speed_50MHz;
   GPIOis.GPIO_OType                        = GPIO_OType_PP;
   GPIOis.GPIO_PuPd                         = GPIO_PuPd_UP;

   USARTis.USART_BaudRate                   = 115200; // 9600;
   USARTis.USART_WordLength                 = USART_WordLength_8b;
   USARTis.USART_StopBits                   = USART_StopBits_1;
   USARTis.USART_Parity                     = USART_Parity_No;
   USARTis.USART_HardwareFlowControl        = USART_HardwareFlowControl_None;
   USARTis.USART_Mode                       = USART_Mode_Rx | USART_Mode_Tx;

   NVICis.NVIC_IRQChannelPreemptionPriority = 0x0f;
   NVICis.NVIC_IRQChannelSubPriority        = 0x00;
   NVICis.NVIC_IRQChannelCmd                = ENABLE;

   NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

   switch( periph ) {

      case RCC_APB2Periph_USART1:
         GPIOis.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
         GPIOB.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOB_BASE, &GPIOis );

         PB6.alt( GPIO_AF_USART1 );
         PB7.alt( GPIO_AF_USART1 );

         USART_Init(( USART_TypeDef* )iobase, &USARTis );

         NVICis.NVIC_IRQChannel = USART1_IRQn;
         break;

      case RCC_APB1Periph_USART2:
         GPIOis.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
         GPIOA.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOA_BASE, &GPIOis );

         PA2.alt( GPIO_AF_USART2 );
         PA3.alt( GPIO_AF_USART2 );

         USART_Init(( USART_TypeDef* )iobase, &USARTis );

         NVICis.NVIC_IRQChannel = USART2_IRQn;
         break;

      case RCC_APB1Periph_USART3:
         GPIOis.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
         GPIOB.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOB_BASE, &GPIOis );

         PB10.alt( GPIO_AF_USART3 );
         PB11.alt( GPIO_AF_USART3 );

         USART_Init(( USART_TypeDef* )iobase, &USARTis );

         NVICis.NVIC_IRQChannel = USART3_IRQn;
         break;

      case RCC_APB1Periph_UART4:
         GPIOis.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
         GPIOA.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOA_BASE, &GPIOis );

         PA0.alt( GPIO_AF_UART4 );
         PA1.alt( GPIO_AF_UART4 );

         USART_Init(( USART_TypeDef* )iobase, &USARTis );

         NVICis.NVIC_IRQChannel = UART4_IRQn;
         break;

      /*
      case RCC_APB1Periph_UART5:
         break;
      */

      case RCC_APB2Periph_USART6:
         GPIOis.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
         GPIOC.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOC_BASE, &GPIOis );

         PC6.alt( GPIO_AF_USART6 );
         PC7.alt( GPIO_AF_USART6 );

         USART_Init(( USART_TypeDef* )iobase, &USARTis );

         NVICis.NVIC_IRQChannel = USART6_IRQn;
         break;

      default:
         throw( 42 );  /* XXX */
   }

   USART_ITConfig(( USART_TypeDef* )iobase, USART_IT_RXNE, ENABLE );

   NVIC_Init( &NVICis );
   USART_Cmd(( USART_TypeDef* )iobase, ENABLE );
}


void UART::disable( void )
{ bus.disable( this ); }


size_t UART::read( void *x, size_t len, TickType_t timeout )
{
   int rv = 0;

   // acquire the read lock

   if( timeout < portMAX_DELAY )
      timeout = timeout / portTICK_RATE_MS;

   xSemaphoreTake( _rdLock, portMAX_DELAY );

   if( len < 16 ) {
      rv = _readIRQ( x, len, timeout );
   } else {
    //rv = _readDMA( x, len, timeout );
      rv = _readIRQ( x, len, timeout );
   }

   // release the read lock

   xSemaphoreGive( _rdLock );

   return rv;
}


size_t UART::write( const void *x, size_t len, TickType_t timeout )
{
   int rv = 0;

   // acquire the write lock

   if( timeout < portMAX_DELAY )
      timeout = timeout / portTICK_RATE_MS;

   xSemaphoreTake( _wrLock, timeout );

   if( len < 16 ) {
      rv = _writeIRQ( x, len, timeout );
   } else {
    //rv = _writeDMA( x, len, timeout );
      rv = _writeIRQ( x, len, timeout );
   }

   // release the write lock

   xSemaphoreGive( _wrLock );

   return rv;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

size_t UART::_readDMA( void *x, size_t len, TickType_t timeout )
{ return 0; }


size_t UART::_readIRQ( void *x, size_t len, TickType_t timeout )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
   size_t n;

   for( n = 0 ; n < len ; ++n ) {
      xSemaphoreTake( _isrRXNE, timeout );
      ((uint8_t*)x)[ n ] = USARTx->DR;
   }

   return n;
}


size_t UART::_writeDMA( const void *x, size_t len, TickType_t timeout )
{ return 0; }


size_t UART::_writeIRQ( const void *x, size_t len, TickType_t timeout )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
   size_t n;

   for( n = 0 ; n < len ; ++n ) {
      USARTx->CR1 |= USART_FLAG_TXE;
      xSemaphoreTake( _isrTXE, timeout );
      USARTx->DR = ((uint8_t*)x)[ n ];
   }

   return n;
}

//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void UART::isr( void )
{
   USART_TypeDef *USARTx = (USART_TypeDef*)iobase;
   portBASE_TYPE hpTask  = pdFALSE;
   uint16_t SR = USARTx->SR;

   if( SR & USART_FLAG_RXNE ) {
      USARTx->SR &= ~USART_FLAG_RXNE;
      xSemaphoreGiveFromISR( _isrRXNE, &hpTask );
   }

   if( SR & USART_FLAG_TXE ) {
      USARTx->SR &= ~USART_FLAG_TXE;
      xSemaphoreGiveFromISR( _isrTXE, &hpTask );
      USARTx->CR1 &= ~USART_FLAG_TXE;
   }

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
}


/* trampolines */

void USART1_IRQHandler( void )
{ qb50::UART1.isr(); }

void USART2_IRQHandler( void )
{ qb50::UART2.isr(); }

void USART3_IRQHandler( void )
{ qb50::UART3.isr(); }

void UART4_IRQHandler( void )
{ qb50::UART4.isr(); }

/*
void UART5_IRQHandler( void )
{ qb50::UART5.isr(); }
*/

void USART6_IRQHandler( void )
{ qb50::UART6.isr(); }


/*EoF*/
