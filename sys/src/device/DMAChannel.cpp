
#include "device/DMA.h"
#include "device/DMAChannel.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMAChannel::DMAChannel( Bus& bus, const uint32_t periph, const uint32_t iobase )
   : CoreDevice( bus, periph, iobase )
{
   reset();
}


DMAChannel::~DMAChannel()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

void DMAChannel::reset( void )
{ ; }


void DMAChannel::enable( void )
{ bus.enable( this ); }


void DMAChannel::disable( void )
{ bus.disable( this ); }


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void DMAChannel::isr( void )
{ ; }


/* trampolines */

void DMA1_Stream0_IRQHandler( void )
{ qb50::DMA1.chan[0].isr(); }

void DMA1_Stream1_IRQHandler( void )
{ qb50::DMA1.chan[1].isr(); }

void DMA1_Stream2_IRQHandler( void )
{ qb50::DMA1.chan[2].isr(); }

void DMA1_Stream3_IRQHandler( void )
{ qb50::DMA1.chan[3].isr(); }

void DMA1_Stream4_IRQHandler( void )
{ qb50::DMA1.chan[4].isr(); }

void DMA1_Stream5_IRQHandler( void )
{ qb50::DMA1.chan[5].isr(); }

void DMA1_Stream6_IRQHandler( void )
{ qb50::DMA1.chan[6].isr(); }

void DMA1_Stream7_IRQHandler( void )
{ qb50::DMA1.chan[7].isr(); }

void DMA2_Stream0_IRQHandler( void )
{ qb50::DMA2.chan[0].isr(); }

void DMA2_Stream1_IRQHandler( void )
{ qb50::DMA2.chan[1].isr(); }

void DMA2_Stream2_IRQHandler( void )
{ qb50::DMA2.chan[2].isr(); }

void DMA2_Stream3_IRQHandler( void )
{ qb50::DMA2.chan[3].isr(); }

void DMA2_Stream4_IRQHandler( void )
{ qb50::DMA2.chan[4].isr(); }

void DMA2_Stream5_IRQHandler( void )
{ qb50::DMA2.chan[5].isr(); }

void DMA2_Stream6_IRQHandler( void )
{ qb50::DMA2.chan[6].isr(); }

void DMA2_Stream7_IRQHandler( void )
{ qb50::DMA2.chan[7].isr(); }


/*EoF*/
