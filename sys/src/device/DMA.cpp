
#include "device/DMA.h"

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
          DMAStream *streams )
   : BusDevice( bus, periph, iobase ),
     streams( streams )
{
   reset();
}


DMA::~DMA()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMA& DMA::reset( void )
{
   return *this;
}


DMA& DMA::enable( void )
{
   bus.enable( this );
   return *this;
}


DMA& DMA::disable( void )
{
   bus.disable( this );
   return *this;
}


#define DMAStream0_4_IFCR    0x3d
#define DMAStream1_5_IFCR  ( 0x3d <<  6 )
#define DMAStream2_6_IFCR  ( 0x3d << 16 )
#define DMAStream3_7_IFCR  ( 0x3d << 22 )


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void DMA::isr( void )
{ ; }


/* trampolines */

void DMA1_IRQHandler( void )
{ qb50::DMA1.isr(); }

void DMA2_IRQHandler( void )
{ qb50::DMA2.isr(); }


/*EoF*/
