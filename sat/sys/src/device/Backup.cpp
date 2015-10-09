
#include "device/RstClk.h"
#include "device/Power.h"
#include "device/Backup.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Backup::Backup( Bus& bus,
                const uint32_t iobase,
                const uint32_t periph,
                const char    *name )
   : BusDevice( bus, iobase, periph, name )
{ ; }


Backup::~Backup()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

Backup& Backup::init( void )
{
   LOG << _name << ": Backup SRAM controller at " << bus.name;

   return *this;
}


Backup& Backup::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   PWR.enable( silent );
   RCC.enable( this );
   PWR.enableBKPSRAM();

   return *this;
}


Backup& Backup::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   PWR.disableBKPSRAM();
   RCC.disable( this );
   PWR.disable( silent );

   return *this;
}


/*EoF*/
