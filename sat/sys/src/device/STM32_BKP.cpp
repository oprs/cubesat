
#include "device/STM32_RCC.h"
#include "device/STM32_PWR.h"
#include "device/STM32_BKP.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_BKP::STM32_BKP( Bus& bus,
                const uint32_t iobase,
                const uint32_t periph,
                const char    *name )
   : Device( name ), BusSlave( bus, iobase, periph )
{ ; }


STM32_BKP::~STM32_BKP()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_BKP& STM32_BKP::init( void )
{
   LOG << _name << ": STM32F4xx Backup  controller at " << bus.name;

   return *this;
}


STM32_BKP& STM32_BKP::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   PWR.enable( silent );
   RCC.enable( this );
   PWR.enableBKP();

   return *this;
}


STM32_BKP& STM32_BKP::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   PWR.disableBKP();
   RCC.disable( this );
   PWR.disable( silent );

   return *this;
}


/*EoF*/
