
#include "device/STM32_RCC.h"
#include "device/Power.h"
#include "device/STM32_BKPSRAM.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_BKPSRAM::STM32_BKPSRAM( Bus& bus,
                const uint32_t iobase,
                const uint32_t periph,
                const char    *name )
   : Device( name ), BusSlave( bus, iobase, periph )
{ ; }


STM32_BKPSRAM::~STM32_BKPSRAM()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_BKPSRAM& STM32_BKPSRAM::init( void )
{
   LOG << _name << ": STM32 Backup SRAM controller at " << bus.name;

   return *this;
}


STM32_BKPSRAM& STM32_BKPSRAM::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   PWR.enable( silent );
   RCC.enable( this );
   PWR.enableBKPSRAM();

   return *this;
}


STM32_BKPSRAM& STM32_BKPSRAM::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   PWR.disableBKPSRAM();
   RCC.disable( this );
   PWR.disable( silent );

   return *this;
}


/*EoF*/
