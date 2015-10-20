
#include "device/SPI.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPI::Stream::Stream( DMA::Stream&         dmaStream,
                     DMA::Stream::Channel dmaChannel,
                     const char          *name,
                     GPIO::Pin&           pin,
                     GPIO::Pin::Alt       alt )
   : Device( name ),
     dmaStream( dmaStream ),
     dmaChannel( dmaChannel ),
     _pin( pin ),
     _alt( alt )
{ ; }


SPI::Stream::~Stream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPI::Stream& SPI::Stream::init( void )
{
   _pin.enable().pullUp().alt( _alt );
   return *this;
}


SPI::Stream& SPI::Stream::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   dmaStream.enable( silent )
            .channel( dmaChannel );

   return *this;
}


SPI::Stream& SPI::Stream::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   dmaStream.disable( silent );

   return *this;
}

/*EoF*/
