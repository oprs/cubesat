
#include "device/SPIStream.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIStream::SPIStream( GPIOPin&          pin,
                      DMAStream&         ds,
                      DMAStream::Channel dc )
   : pin( pin ), ds( ds ), dc( dc )
{ ; }


SPIStream::~SPIStream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIStream& SPIStream::reset( void )
{
   QB50DBG( "SPIStream::reset()\r\n" );
   ds.reset();
   pin.reset();

   return *this;
}


SPIStream& SPIStream::enable( void )
{
   QB50DBG( "SPIStream::enable()\r\n" );
   ds.enable().channel( dc );
   pin.enable();

   return *this;
}


SPIStream& SPIStream::disable( void )
{
   QB50DBG( "SPIStream::disable()\r\n" );
   ds.disable();
   pin.disable();

   return *this;
}

/*EoF*/
