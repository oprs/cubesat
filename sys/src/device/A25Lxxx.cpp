
#include "device/A25Lxxx.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( uint32_t id, SPI& spi, GPIOPin& csPin )
   : _id( id ), _spi( spi ), _csPin( csPin )
{
   reset();
}


A25Lxxx::~A25Lxxx()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::reset( void )
{
   return *this;
}


A25Lxxx& A25Lxxx::enable( void )
{
   _csPin.enable();

   return *this;
}


A25Lxxx& A25Lxxx::disable( void )
{
   _csPin.disable();

   return *this;
}

/*EoF*/
