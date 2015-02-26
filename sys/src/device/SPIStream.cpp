
#include "device/SPIStream.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIStream::SPIStream( GPIOPin&           pin,
                      DMAStream&         dmaStream,
                      DMAStream::Channel dmaChannel )
   : pin( pin ),
     dmaStream( dmaStream ),
     dmaChannel( dmaChannel )
{ ; }


SPIStream::~SPIStream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIStream& SPIStream::reset( void )
{
   QB50DBG( "SPIStream::reset()\r\n" );
   dmaStream.reset();
   pin.reset();

   return *this;
}


SPIStream& SPIStream::enable( void )
{
   QB50DBG( "SPIStream::enable()\r\n" );
   dmaStream.enable()
            .channel( dmaChannel );
   pin.enable();

   return *this;
}


SPIStream& SPIStream::disable( void )
{
   QB50DBG( "SPIStream::disable()\r\n" );
   dmaStream.disable();
   pin.disable();

   return *this;
}

/*EoF*/
