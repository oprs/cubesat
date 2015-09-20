
#include "device/Transceiver.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Transceiver::Transceiver( const char *name, GPIOPin& enPin )
	: Device( name ), _enPin( enPin )
{ ; }


Transceiver::~Transceiver()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Transceiver& Transceiver::init( void )
{
   _enPin.enable().pullDn().out();
   return *this;
}


Transceiver& Transceiver::enable( void )
{
   if( _incRef() == 0 )
      _enPin.on();

   return *this;
}


Transceiver& Transceiver::disable( void )
{
   if( _decRef() == 0 )
      _enPin.off();

   return *this;
}


/*EoF*/
