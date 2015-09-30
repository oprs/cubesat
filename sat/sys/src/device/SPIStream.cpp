
#include "device/SPIStream.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIStream::SPIStream( DMAStream&         dmaStream,
                      DMAStream::Channel dmaChannel,
                      const char        *name,
                      GPIOPin&           pin,
                      GPIOPin::Alt       alt )
   : Device( name ),
     dmaStream( dmaStream ),
     dmaChannel( dmaChannel ),
     _pin( pin ),
     _alt( alt )
{ ; }


SPIStream::~SPIStream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIStream& SPIStream::init( void )
{
   _pin.enable().pullUp().alt( _alt );
   return *this;
}


SPIStream& SPIStream::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   dmaStream.enable( silent )
            .channel( dmaChannel );

   return *this;
}


SPIStream& SPIStream::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   dmaStream.disable( silent );

   return *this;
}

/*EoF*/
