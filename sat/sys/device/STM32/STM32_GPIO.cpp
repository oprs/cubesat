
#include "STM32/STM32_RCC.h"
#include "STM32/STM32_GPIO.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_GPIO::STM32_GPIO( Bus& bus,
                        const uint32_t iobase,
                        const uint32_t periph,
                        const unsigned id,
                        const char *name,
                        const Pin *pins )
   : Device( name ), BusSlave( bus, iobase, periph ), GPIO( pins ), _id( id )
{ ; }


STM32_GPIO::~STM32_GPIO()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

STM32_GPIO& STM32_GPIO::init( void )
{
   LOG << _name << ": STM32F4xx GPIO controller at " << bus.name;
   return *this;
}


STM32_GPIO& STM32_GPIO::enable( bool silent )
{
   if( _incRef() == 0 )
      RCC.enable( this, silent );

   return *this;
}


STM32_GPIO& STM32_GPIO::disable( bool silent )
{
   if( _decRef() == 0 )
      RCC.disable( this, silent );

   return *this;
}

/*EoF*/
