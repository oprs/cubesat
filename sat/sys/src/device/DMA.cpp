
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
          const char *name,
          DMAStream *streams )
   : BusDevice( bus, iobase, periph, name ),
     streams( streams )
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


DMA& DMA::enable( void )
{ return *this; }


DMA& DMA::disable( void )
{ return *this; }


//  - - - - - - - - - - -  //
//  T R A M P O L I N E S  //
//  - - - - - - - - - - -  //

void DMA1_Stream0_IRQHandler( void )
{ qb50::DMA1.streams[0].isr(); }

void DMA1_Stream1_IRQHandler( void )
{ qb50::DMA1.streams[1].isr(); }

void DMA1_Stream2_IRQHandler( void )
{ qb50::DMA1.streams[2].isr(); }

void DMA1_Stream3_IRQHandler( void )
{ qb50::DMA1.streams[3].isr(); }

void DMA1_Stream4_IRQHandler( void )
{ qb50::DMA1.streams[4].isr(); }

void DMA1_Stream5_IRQHandler( void )
{ qb50::DMA1.streams[5].isr(); }

void DMA1_Stream6_IRQHandler( void )
{ qb50::DMA1.streams[6].isr(); }

void DMA1_Stream7_IRQHandler( void )
{ qb50::DMA1.streams[7].isr(); }

void DMA2_Stream0_IRQHandler( void )
{ qb50::DMA2.streams[0].isr(); }

void DMA2_Stream1_IRQHandler( void )
{ qb50::DMA2.streams[1].isr(); }

void DMA2_Stream2_IRQHandler( void )
{ qb50::DMA2.streams[2].isr(); }

void DMA2_Stream3_IRQHandler( void )
{ qb50::DMA2.streams[3].isr(); }

void DMA2_Stream4_IRQHandler( void )
{ qb50::DMA2.streams[4].isr(); }

void DMA2_Stream5_IRQHandler( void )
{ qb50::DMA2.streams[5].isr(); }

void DMA2_Stream6_IRQHandler( void )
{ qb50::DMA2.streams[6].isr(); }

void DMA2_Stream7_IRQHandler( void )
{ qb50::DMA2.streams[7].isr(); }

/*EoF*/
