
#include "device/SPIStream.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIStream::SPIStream( DMAStream&         dmaStream,
                      DMAStream::Channel dmaChannel,
                      GPIOPin&           pin,
                      GPIOPin::Alt       alt )
   : dmaStream( dmaStream ),
     dmaChannel( dmaChannel ),
     _pin( pin ),
     _alt( alt )
{ ; }


SPIStream::~SPIStream()
{ disable(); }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIStream& SPIStream::enable( void )
{
   _pin.enable()
       .pullUp()
       .alt( _alt );

   dmaStream.enable()
            .channel( dmaChannel );

   return *this;
}


SPIStream& SPIStream::disable( void )
{
   dmaStream.disable();
   _pin.disable();

   return *this;
}

/*EoF*/
