
#include "device/TIMERSTM.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TIMER::TIMER(Bus& bus,
             const uint32_t iobase,
             const uint32_t periph,
             const char *name,
             GPIOPin& pin,
             GPIOPin::Alt alt)
   : BusDevice( bus, iobase, periph, name ),
     _pin( pin ), _alt( alt )
{ ; }


TIMER::~TIMER()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

TIMER& TIMER::init( void )
{
   LOG << _name << ": System timer controller at " << bus.name()
       //<< ", rx: " << _rxPin.name()
       << std::flush;

   return *this;
}


TIMER& TIMER::enable( void )
{
   if( _incRef() > 0 )
      return *this;

   bus.enable(this);
   _pin.enable()
       .pullUp()
       .alt(_alt);

   return *this;
}

TIMER& TIMER::disable( void )
{
   if( _decRef() > 0 )
      return *this;

   _pin.disable();
   bus.disable( this );

   return *this;
}
