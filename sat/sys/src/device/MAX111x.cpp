
#include "device/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIOPin& csPin )
	: SPIDevice( spi, csPin, SPIDevice::ActiveLow ),
	  _name( name )
{ ; }


MAX111x::~MAX111x()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::enable( void )
{
	if( _incRef() > 0 )
		return *this;

	_spi.enable();

	LOG << _name << ": MAX111x Serial ADC at " << _spi.name()
	    << ", cs: " << _csPin.name()
	    << std::flush;

	return *this;
}


MAX111x& MAX111x::disable( void )
{ return *this; }


int MAX111x::readChannel( Channel sel )
{
	uint8_t ConvCmd[ 4 ];
	uint8_t ConvRes[ 4 ];

	ConvCmd[ 0 ] = 0x00;
	ConvCmd[ 1 ] = 0x8f | (( sel & 0x07 ) << 4 ) ;
	ConvCmd[ 2 ] = 0x00;
	ConvCmd[ 3 ] = 0x00;

	select();
	_spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));
	deselect();

	//hexdump( ConvRes, 4 );

	return
		(( ConvRes[2] << 8 ) | ConvRes[3] ) >> 6;
}

/*EoF*/
