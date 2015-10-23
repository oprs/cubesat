
#include "device/RstClk.h"
#include "device/SPI.h"
#include "device/UART.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPI::SPI( Bus&           bus,
          const uint32_t iobase,
          const uint32_t periph,
          const char    *name,
          Stream&        stMISO,
          Stream&        stMOSI,
          GPIO::Pin&     clkPin,
          GPIO::Alt      alt,
          SPI::ClkDiv    div )
   : Device( name ), BusSlave( bus, iobase, periph ),
     _stMISO( stMISO ),
     _stMOSI( stMOSI ),
     _clkPin( clkPin ),
     _alt( alt ),
     _div( div )
{ ; }


SPI::~SPI()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

SPI& SPI::init( void )
{
   _clkPin.enable().pullDn().alt( _alt );

   _stMISO.init();
   _stMOSI.init();

   LOG << _name << ": System SPI controller at " << bus.name
       << ", clk: " << _clkPin.name()
       << ", miso: " << _stMISO._pin.name()
       << ", mosi: " << _stMOSI._pin.name()
       ;

   return *this;
}


SPI& SPI::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   _stMISO.enable( silent );
   _stMOSI.enable( silent );

   RCC.enable( this, silent );

   SPIx->CR1 &= ~SPI_CR1_SPE;

   SPIx->CR1 = SPI_CR1_MSTR  /* device is master      */
             | _div << 3     /* baud rate control     */
             | SPI_CR1_SSI   /* internal slave select */
             | SPI_CR1_SSM   /* software slave mgmt.  */
             ;

   SPIx->CR2 |= ( SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN );
   SPIx->CR1 |= SPI_CR1_SPE;

   return *this;
}


SPI& SPI::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   SPIx->CR1 &= ~SPI_CR1_SPE;

   RCC.disable( this, silent );

   _stMOSI.disable( silent );
   _stMISO.disable( silent );

   return *this;
}


SPI& SPI::grab( void )
{
   _lock();
   return *this;
}


SPI& SPI::release( void )
{
   _unlock();
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


SPI& SPI::xfer( const void *src, void *dst, size_t len )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   _stMISO.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     dst     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::INCR             )
                    .direction ( DMA::P2M              );

   _stMOSI.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     src     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::INCR             )
                    .direction ( DMA::M2P              );

   return _xfer();
}


SPI& SPI::write( const void *src, size_t len )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   uint8_t dummy;

   _stMISO.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)   &dummy    )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::FIXED            )
                    .direction ( DMA::P2M              );

   _stMOSI.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     src     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::INCR             )
                    .direction ( DMA::M2P              );

   return _xfer();
}


SPI& SPI::read( void *dst, size_t len )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   uint8_t dummy = 0xff;

   _stMISO.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)     dst     )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::INCR             )
                    .direction ( DMA::P2M              );

   _stMOSI.dmaStream.pAddr     ((uint32_t)&( SPIx->DR ))
                    .m0Addr    ((uint32_t)   &dummy    )
                    .counter   ((uint32_t)     len     )
                    .pIncMode  ( DMA::FIXED            )
                    .mIncMode  ( DMA::FIXED            )
                    .direction ( DMA::M2P              );

   return _xfer();
}

/* polling methods */

SPI& SPI::pollXfer( const void *src, void *dst, size_t len )
{
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   uint8_t rx;

   for( size_t i = 0 ; i < len ; ++i ) {
      while( !( SPIx->SR & SPI_SR_TXE )); // XXX hard limit

      if( src == NULL ) {
         SPIx->DR = 0xff;
      } else {
         SPIx->DR = ((uint8_t*)src)[ i ];
      }

      while( !( SPIx->SR & SPI_SR_RXNE )); // XXX hard limit

      rx = SPIx->DR & 0xff;
      if( dst != NULL ) {
         ((uint8_t*)dst)[ i ] = rx;
      }
   }

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

SPI& SPI::_xfer( void )
{
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

   return *this;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void SPI::isr( void )
{ ; }

/*EoF*/
