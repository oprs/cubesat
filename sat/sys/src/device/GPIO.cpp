
#include "device/STM32_RCC.h"
#include "device/GPIO.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIO::GPIO( Bus& bus,
            const uint32_t iobase,
            const uint32_t periph,
            const unsigned id,
            const char *name,
            Pin *pins )
   : Device( name ), BusSlave( bus, iobase, periph ), _id( id ), _pins( pins )
{ ; }


GPIO::~GPIO()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

GPIO& GPIO::init( void )
{
   LOG << _name << ": System GPIO controller at " << bus.name;
   return *this;
}


GPIO& GPIO::enable( bool silent )
{
   if( _incRef() == 0 )
      RCC.enable( this, silent );

   return *this;
}


GPIO& GPIO::disable( bool silent )
{
   if( _decRef() == 0 )
      RCC.disable( this, silent );

   return *this;
}

/*EoF*/
