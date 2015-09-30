
#include "device/DMA.h"
#include "system/Logger.h"

#include <stm32f4xx.h>

#undef DMA1
#undef DMA2

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMA::DMA( Bus& bus,
          const uint32_t iobase,
          const uint32_t periph,
          const char *name )
   : BusDevice( bus, iobase, periph, name )
{ ; }


DMA::~DMA()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMA& DMA::init( void )
{
   LOG << _name << ": System DMA controller at " << bus.name();
   return *this;
}


DMA& DMA::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   bus.enable( this, silent );

   return *this;
}


DMA& DMA::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   bus.disable( this, silent );

   return *this;
}

/*EoF*/
