
#include "device/EXTMEM.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

EXTMEM::EXTMEM( uint32_t id, SPI& spi, GPIOPin& csPin )
   : _id( id ), _spi( spi ), _csPin( csPin )
{
   reset();
}


EXTMEM::~EXTMEM()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

EXTMEM& EXTMEM::reset( void )
{
   return *this;
}


EXTMEM& EXTMEM::enable( void )
{
   _csPin.enable();

   return *this;
}


EXTMEM& EXTMEM::disable( void )
{
   _csPin.disable();

   return *this;
}

/*EoF*/
