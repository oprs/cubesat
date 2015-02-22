
#include "device/SPIStream.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIStream::SPIStream( GPIOPin& pin, DMAStream& ds, uint32_t dc )
   : pin( pin ), ds( ds ), dc( dc )
{ ; }


SPIStream::~SPIStream()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIStream& SPIStream::reset( void )
{
   ds.reset();
   pin.reset();

   return *this;
}


SPIStream& SPIStream::enable( void )
{
   ds.enable();
   pin.enable();

   return *this;
}


SPIStream& SPIStream::disable( void )
{
   ds.disable();
   pin.disable();

   return *this;
}

/*EoF*/
