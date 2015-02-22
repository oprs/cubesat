
#include "device/SPI.h"

#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPI::SPI( Bus&           bus,
          const uint32_t iobase,
          const uint32_t periph,
          SPIStream&     stMISO,
          SPIStream&     stMOSI,
          GPIOPin&       clkPin,
          GPIOPin::Alt   alt )
   : BusDevice( bus, iobase, periph ),
     _stMISO( stMISO ),
     _stMOSI( stMOSI ),
     _clkPin( clkPin ),
     _alt( alt )
{
   _lock    = xSemaphoreCreateMutex();
   _isrRXNE = xSemaphoreCreateBinary();
   _isrTXE  = xSemaphoreCreateBinary();

   reset();
}


SPI::~SPI()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

/*
   See the STM32F4 Reference Manual,
   sec 28.5.1 "SPI control register 1" (pp. 904-906)

   SPI CR1:

    0000001100111100 = 0x033c
    ||||||||||\_/|||
    |||||||||| | ||+- SPI_CR1_CPHA     - Clock phase
    |||||||||| | |+-- SPI_CR1_CPOL     - Clock polarity
    |||||||||| | +--- SPI_CR1_MSTR     - Master selection
    |||||||||| +----- SPI_CR1_BR       - Baud rate control
    |||||||||+------- SPI_CR1_SPE      - SPI enable
    ||||||||+-------- SPI_CR1_LSBFIRST - Frame format
    |||||||+--------- SPI_CR1_SSI      - Internal slave select
    ||||||+---------- SPI_CR1_SSM      - Software slave mgmt.
    |||||+----------- SPI_CR1_RXONLY   - Receive only
    ||||+------------ SPI_CR1_DFF      - Data frame format
    |||+------------- SPI_CR1_CRCNEXT  - CRC transfer next
    ||+-------------- SPI_CR1_CRCEN    - CRC enable
    |+--------------- SPI_CR1_BIDIOE   - Output enable in bidirectional mode
    +---------------- SPI_CR1_BIDIMODE - Bidirectional mode enable
 */

SPI& SPI::reset( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   bus.enable( this );

   SPIx->CR1 = SPI_CR1_MSTR  /* device is master         */
             | 0x0007 << 3   /* baud rate control = 111b */
             | SPI_CR1_SSI   /* internal slave select    */
             | SPI_CR1_SSM   /* software slave mgmt.     */
             ;

   bus.disable( this );

   return *this;
}


SPI& SPI::enable( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   _stMISO.pin.enable()
              .pullUp()
              .alt( _alt );

   _stMOSI.pin.enable()
              .pullUp()
              .alt( _alt );

   _clkPin.enable()
          .alt( _alt );

   bus.enable( this );
   SPIx->CR1 |= SPI_CR1_SPE;

   return *this;
}


SPI& SPI::disable( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   SPIx->CR1 &= ~SPI_CR1_SPE;
   bus.disable( this );

   _clkPin.disable();
   _stMOSI.disable();
   _stMISO.disable();

   return *this;
}


SPI& SPI::master( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   SPIx->CR1 |= SPI_CR1_MSTR;

   return *this;
}


SPI& SPI::slave( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   SPIx->CR1 &= ~SPI_CR1_MSTR;

   return *this;
}


size_t SPI::xfer( const void *src, void *dst, size_t len )
{
   size_t n;

   // acquire the lock

   xSemaphoreTake( _lock, portMAX_DELAY );

   // perform the write

   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   for( n = 0 ; n < len ; ++n ) {
      while(( SPIx->SR & SPI_SR_TXE ) == RESET );
      if( src == NULL ) {
         SPIx->DR = 0xffff;
      } else {
         SPIx->DR = ((uint8_t*)src)[ n ];
      }

      while(( SPIx->SR & SPI_SR_RXNE ) == RESET );
      if( dst != NULL ) {
         ((uint8_t*)dst)[ n ] = SPIx->DR;
      }
   }

   // release the lock

   xSemaphoreGive( _lock );

   return n;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

/*
void SPI::setupNVIC( void )
{
   NVICis.NVIC_IRQChannelPreemptionPriority = 0x0f;
   NVICis.NVIC_IRQChannelSubPriority        = 0x00;
   NVICis.NVIC_IRQChannelCmd                = ENABLE;

   switch( periph ) {

      case RCC_APB2Periph_SPI1:

         NVICis.NVIC_IRQChannel = SPI1_IRQn;
         break;

      case RCC_APB1Periph_SPI2:

         NVICis.NVIC_IRQChannel = SPI2_IRQn;
         break;

      case RCC_APB1Periph_SPI3:

         NVICis.NVIC_IRQChannel = SPI3_IRQn;
         break;

      default:
         ;
   }
}
*/


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void SPI::isr( void )
{
#if 0
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   portBASE_TYPE hpTask  = pdFALSE;
   uint16_t SR = SPIx->SR;

   if( SR & SPI_FLAG_RXNE ) {
      SPIx->SR &= ~SPI_FLAG_RXNE;
      xSemaphoreGiveFromISR( _isrRXNE, &hpTask );
   }

   if( SR & SPI_FLAG_TXE ) {
      SPIx->SR &= ~SPI_FLAG_TXE;
      xSemaphoreGiveFromISR( _isrTXE, &hpTask );
      SPIx->CR1 &= ~SPI_FLAG_TXE;
   }

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
#endif
}

/* trampolines */

#undef SPI1
#undef SPI2
#undef SPI3

void SPI1_IRQHandler( void )
{ qb50::SPI1.isr(); }

void SPI2_IRQHandler( void )
{ qb50::SPI2.isr(); }

void SPI3_IRQHandler( void )
{ qb50::SPI3.isr(); }

/*EoF*/
