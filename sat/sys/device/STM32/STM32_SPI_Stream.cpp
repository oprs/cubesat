
#include "STM32/STM32_SPI.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_SPI::Stream::Stream( DMA::Stream&     dmaStream,
                           DMA::Channel     dmaChannel,
                           const char      *name,
                           STM32_GPIO::Pin& pin,
                           STM32_GPIO::Alt  alt )
   : SPI::Stream( name ),
     dmaStream( dmaStream ),
     dmaChannel( dmaChannel ),
     _pin( pin ),
     _alt( alt )
{ ; }


STM32_SPI::Stream::~Stream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

STM32_SPI::Stream& STM32_SPI::Stream::init( void )
{
   _pin.enable().pullUp().alt( _alt );
   return *this;
}


STM32_SPI::Stream& STM32_SPI::Stream::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   dmaStream.enable( silent )
            .channel( dmaChannel );

   return *this;
}


STM32_SPI::Stream& STM32_SPI::Stream::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   dmaStream.disable( silent );

   return *this;
}

/*EoF*/
