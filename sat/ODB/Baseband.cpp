
#include "devices.h"
#include "Baseband.h"

using namespace qb50;


Baseband qb50::BB( "BB", PB15, PB13 ); // global Baseband object


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Baseband::Baseband( const char *name, GPIO::Pin& enTXPin, GPIO::Pin& enPAPin )
   : Device( name ), _enTXPin( enTXPin ), _enPAPin( enPAPin )
{ ; }


Baseband::~Baseband()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Baseband& Baseband::init( void )
{
   kprintf( "%s: AMSAT-F Baseband Interface (F6FAO), enTX: %s, enPA: %s\r\n",
            _name, _enTXPin.name(), _enPAPin.name() );

   _enTXPin.out().off();
   _enPAPin.out().off();

   return *this;
}


Baseband& Baseband::enable( bool silent )
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


Baseband& Baseband::disable( bool silent )
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
