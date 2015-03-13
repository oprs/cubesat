
#include "device/SPIDevice.h"


using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIDevice::SPIDevice( SPI& spi, GPIOPin& csPin, SelectMode csMode )
	: _spi( spi ), _csPin( csPin ), _csMode( csMode )
{
	_csPin.enable();

	if( _csMode == ActiveLow ) {
	   _csPin.on();
	} else {
	   _csPin.off();
	}
}


SPIDevice::~SPIDevice()
{
	_csPin.disable();
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

SPIDevice& SPIDevice::select( void )
{
	_spi.grab();

	if( _csMode == ActiveLow ) {
	   _csPin.off();
	} else {
	   _csPin.on();
	}

	return *this;
}


SPIDevice& SPIDevice::deselect( void )
{
	if( _csMode == ActiveLow ) {
	   _csPin.on();
	} else {
	   _csPin.off();
	}

	_spi.release();

	return *this;
}


/*EoF*/
