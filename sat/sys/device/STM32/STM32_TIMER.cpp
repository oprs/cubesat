
#include "STM32/STM32_RCC.h"
#include "STM32/STM32_TIMER.h"
#include "system/Logger.h"
#include "stm32f4xx_tim.h"

#undef RCC

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_TIMER::STM32_TIMER( Bus&  bus,
              const uint32_t    iobase,
              const uint32_t    periph,
              const char       *name,
              STM32_GPIO::Pin&  pin,
              STM32_GPIO::Alt   alt )
   : Device( name ), BusSlave( bus, iobase, periph ),
     _pin( pin ), _alt( alt )
{ ; }


STM32_TIMER::~STM32_TIMER()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_TIMER& STM32_TIMER::init( void )
{
   kprintf( "%s: System timer controller at %s\r\n", _name, bus.name );
   return *this;
}


STM32_TIMER& STM32_TIMER::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RCC.enable( this, silent );
   _pin.pullUp()
       .alt(_alt);

   return *this;
}

STM32_TIMER& STM32_TIMER::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   RCC.disable( this, silent );

   return *this;
}

/*EoF*/
