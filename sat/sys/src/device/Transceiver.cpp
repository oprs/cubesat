
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
   LOG << _name << ": AMSAT-F Radio Board (F6FAO)"
       << ", enTX: " << _enTXPin.name()
       << ", enPA: " << _enPAPin.name()
       ;

   _enTXPin.enable().out().off();
   _enPAPin.enable().out().off();

   return *this;
}


Transceiver& Transceiver::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _enTXPin.on();
   if( !silent ) LOG << _name << ": Waiting for 500ms...";

   delay( 500 );

   _enPAPin.on();
   if( !silent ) LOG << _name << ": Enabled";

   return *this;
}


Transceiver& Transceiver::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _enPAPin.off();
   _enTXPin.off();

   if( !silent ) LOG << _name << ": Disabled";

   return *this;
}


/*EoF*/
