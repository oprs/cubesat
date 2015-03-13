
#include "device/MAX111x.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, GPIOPin& csPin )
	: SPIDevice( spi, csPin, SPIDevice::ActiveLow )
{ ; }


MAX111x::~MAX111x()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::enable( void )
{
	_spi.enable();
	return *this;
}


MAX111x& MAX111x::disable( void )
{ return *this; }


MAX111x& MAX111x::conv( Channel sel, ConvResp *resp )
{
	uint8_t ConvCmd[ 4 ];

	ConvCmd[ 0 ] = 0x00;
	ConvCmd[ 1 ] = 0x8f | (( sel & 0x07 ) << 4 ) ;
	ConvCmd[ 2 ] = 0x00;
	ConvCmd[ 3 ] = 0x00;

	select();
	_spi.pollXfer( ConvCmd, resp, sizeof( ConvCmd ));
	deselect();

	return *this;
}

/*EoF*/
