
#include "device/SPI.h"
#include "device/UART.h"

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
}


SPI::~SPI()
{
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

SPI& SPI::reset( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   QB50DBG( "SPI::reset()\r\n" );

   bus.enable( this );

   SPIx->CR1 = SPI_CR1_MSTR  /* device is master      */
             | 0x0000 << 3   /* baud rate control     */
             | SPI_CR1_SSI   /* internal slave select */
             | SPI_CR1_SSM   /* software slave mgmt.  */
             ;

   bus.disable( this );

   return *this;
}


SPI& SPI::enable( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   QB50DBG( "SPI::enable()\r\n" );

   reset();

   _clkPin.enable()
          .alt( _alt );

   _stMISO.pin.enable()
              .pullUp()
              .alt( _alt );

   _stMOSI.pin.enable()
              .pullUp()
              .alt( _alt );

   _stMISO.dmaStream.enable();
   _stMOSI.dmaStream.enable();

   bus.enable( this );
   SPIx->CR1 |= SPI_CR1_SPE;

   return *this;
}


SPI& SPI::disable( void )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   QB50DBG( "SPI::disable()\r\n" );

   SPIx->CR1 &= ~SPI_CR1_SPE;
   bus.disable( this );

   _stMOSI.dmaStream.disable();
   _stMISO.dmaStream.disable();

   _stMOSI.reset()
          .disable();

   _stMISO.reset()
          .disable();

   _clkPin.reset()
          .disable();

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
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   _stMISO.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     dst     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  (DMAStream::FIXED       )
                    .mIncMode  (DMAStream::INCR        )
                    .direction (DMAStream::P2M         );

   _stMOSI.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     src     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  (DMAStream::FIXED       )
                    .mIncMode  (DMAStream::INCR        )
                    .direction (DMAStream::M2P         );

   SPIx->CR2 |= ( SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN );

   /* enable transmission for both RX and TX streams */

   _stMISO.dmaStream.start();
   _stMOSI.dmaStream.start();

   /*
    * block until the transmission is complete,
    * FreeRTOS will let other threads run in the meantime.
    */

   _stMOSI.dmaStream.wait();
   _stMISO.dmaStream.wait();

   /* we're done: disable both streams and return */

   _stMOSI.dmaStream.stop();
   _stMISO.dmaStream.stop();

   return 0;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void SPI::isr( void )
{ ; }


//  - - - - - - - - - - -  //
//  T R A M P O L I N E S  //
//  - - - - - - - - - - -  //

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
