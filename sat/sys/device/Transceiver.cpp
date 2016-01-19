
#include "device/Transceiver.h"
#include "system/Application.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Transceiver::Transceiver( const char *name, GPIO::Pin& enTXPin, GPIO::Pin& enPAPin )
   : Device( name ), _enTXPin( enTXPin ), _enPAPin( enPAPin )
{ ; }


Transceiver::~Transceiver()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Transceiver& Transceiver::init( void )
{
   kprintf( "%s: AMSAT-F Radio Board (F6FAO), enTX: %s, enPA: %s\r\n",
            _name, _enTXPin.name(), _enPAPin.name() );

   _enTXPin.out().off();
   _enPAPin.out().off();

   return *this;
}


Transceiver& Transceiver::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _enTXPin.on();
   if( !silent ) {
      kprintf( "%s: Waiting for 500ms...\r\n", _name );
   }

   delay( 500 );

   _enPAPin.on();
   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


Transceiver& Transceiver::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _enPAPin.off();
   _enTXPin.off();

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


/*EoF*/
