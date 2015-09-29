
#include "device/SPIDevice.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPIDevice::SPIDevice( SPI& spi, GPIOPin& csPin, SelectMode csMode, const char *name )
   : Device( name ), _spi( spi ), _csPin( csPin ), _csMode( csMode )
{ ; }


SPIDevice::~SPIDevice()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

SPIDevice& SPIDevice::init( void )
{
   if( _csMode == ActiveLow ) {
      _csPin.enable().out().on();
   } else {
      _csPin.enable().out().off();
   }

   return *this;
}


SPIDevice& SPIDevice::select( void )
{
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

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void SPIDevice::_enable( bool silent )
{
   if( _incRef() == 0 ) {
      _spi.enable( silent );
      if( !silent )
         LOG << _spi.name() << ": " << _name << " enabled";
   }
}


void SPIDevice::_disable( bool silent )
{
   if( _decRef() == 0 ) {
      if( !silent )
         LOG << _spi.name() << ": " << _name << " disabled";
      _spi.disable( silent );
   }
}


/*EoF*/
