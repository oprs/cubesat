
#include "STM32/STM32_RCC.h"
#include "STM32/TIMERSTM.h"
#include "system/Logger.h"
#include "stm32f4xx_tim.h"

#undef RCC

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TIMER::TIMER( Bus&              bus,
              const uint32_t    iobase,
              const uint32_t    periph,
              const char       *name,
              STM32_GPIO::Pin&  pin,
              STM32_GPIO::Alt   alt )
   : Device( name ), BusSlave( bus, iobase, periph ),
     _pin( pin ), _alt( alt )
{ ; }


TIMER::~TIMER()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

TIMER& TIMER::init( void )
{
   LOG << _name << ": System timer controller at " << bus.name
      //<< ", rx: " << _rxPin.name()
      ;

   return *this;
}


TIMER& TIMER::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RCC.enable( this, silent );
   _pin.enable( silent )
       .pullUp()
       .alt(_alt);

   return *this;
}

TIMER& TIMER::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _pin.disable( silent );
   RCC.disable( this, silent );

   return *this;
}