
#include "device/STM32_RCC.h"
#include "device/DMA.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMA::DMA( Bus& bus,
          const uint32_t iobase,
          const uint32_t periph,
          const char *name )
   : Device( name ), BusSlave( bus, iobase, periph )
{ ; }


DMA::~DMA()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMA& DMA::init( void )
{
   LOG << _name << ": System DMA controller at " << bus.name;
   return *this;
}


DMA& DMA::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RCC.enable( this, silent );

   return *this;
}


DMA& DMA::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   RCC.disable( this, silent );

   return *this;
}

/*EoF*/
