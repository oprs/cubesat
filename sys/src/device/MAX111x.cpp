
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
   _csPin.enable()
         .pullUp()
         .out();

   return *this;
}


MAX111x& MAX111x::disable( void )
{
   _csPin.disable();

   return *this;
}


MAX111x& MAX111x::conv( Channel sel, ConvResp *resp )
{
   uint8_t ConvCmd[ 3 ];

   ConvCmd[ 0 ] = 0x8f | (( sel & 0x07 ) << 4 ) ;
   ConvCmd[ 1 ] = 0xff;
   ConvCmd[ 2 ] = 0xff;

   _csPin.off();
   _spi.pollXfer( ConvCmd, resp, sizeof( ConvCmd ));
   _csPin.on();

   return *this;
}

/*EoF*/
