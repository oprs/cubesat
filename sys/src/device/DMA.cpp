
#include "device/DMA.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMA::DMA( Bus& bus, const uint32_t periph, const uint32_t iobase, DMAChannel *chan )
   : CoreDevice( bus, periph, iobase ), chan( chan )
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

void DMA::reset( void )
{ ; }


void DMA::enable( void )
{ bus.enable( this ); }


void DMA::disable( void )
{ bus.disable( this ); }


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
