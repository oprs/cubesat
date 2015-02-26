
#include "device/MAX111x.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, GPIOPin& csPin )
   : _spi( spi ), _csPin( csPin )
{ ; }


MAX111x::~MAX111x()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::enable( void )
{
   _csPin.enable();

   return *this;
}


MAX111x& MAX111x::disable( void )
{
   _csPin.disable();

   return *this;
}

/*EoF*/
