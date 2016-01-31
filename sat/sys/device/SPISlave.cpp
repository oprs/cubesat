
#include "device/SPISlave.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPISlave::SPISlave( SPI& spi, GPIO::Pin& csPin, SelectMode csMode )
   : _spi( spi ), _csPin( csPin ), _csMode( csMode )
{ ; }


SPISlave::~SPISlave()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

SPISlave& SPISlave::init( void )
{
   if( _csMode == ActiveLow ) {
      _csPin.out().on();
   } else {
      _csPin.out().off();
   }

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void SPISlave::_select( void )
{
   if( _csMode == ActiveLow ) {
      _csPin.off();
   } else {
      _csPin.on();
   }
}


void SPISlave::_deselect( void )
{
   if( _csMode == ActiveLow ) {
      _csPin.on();
   } else {
      _csPin.off();
   }
}

/*EoF*/
