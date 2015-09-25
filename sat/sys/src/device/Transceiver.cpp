
#include "device/Transceiver.h"
#include "system/Application.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Transceiver::Transceiver( const char *name, GPIOPin& enTXPin, GPIOPin& enPAPin )
   : Device( name ), _enTXPin( enTXPin ), _enPAPin( enPAPin )
{ ; }


Transceiver::~Transceiver()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Transceiver& Transceiver::init( void )
{
   LOG << _name << ": AMSAT-F Radio Board (F6FA0)"
       << ", enTX: " << _enTXPin.name()
       << ", enPA: " << _enPAPin.name()
       ;

   _enTXPin.enable().out().off();
   _enPAPin.enable().out().off();

   return *this;
}


Transceiver& Transceiver::enable( void )
{
   if( _incRef() > 0 )
      return *this;

   _enTXPin.on();
   LOG << _name << ": Waiting for 500ms...";

   delay( 500 );

   _enPAPin.on();
   LOG << _name << ": Enabled";

   return *this;
}


Transceiver& Transceiver::disable( void )
{
   if( _decRef() > 0 )
      return *this;

   _enPAPin.off();
   _enTXPin.off();

   LOG << _name << ": Disabled";

   return *this;
}


/*EoF*/
