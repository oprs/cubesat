
#include "device/DMAStream.h"
#include "system/qb50.h"

#include <stm32f4xx.h>

#undef DMA1
#undef DMA2

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMAStream::DMAStream( DMA& dma, const uint32_t iobase )
   : dma( dma ), iobase( iobase )
{
   reset();
}


DMAStream::~DMAStream()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMAStream& DMAStream::reset( void )
{
   DMA_Stream_TypeDef *CHANx = (DMA_Stream_TypeDef*)iobase;

   /* disable the stream */
   //CHANx->CR  &= ~((uint32_t)DMA_SxCR_EN);

   //disable();

   /* reset the stream */
   CHANx->CR   = 0;
   CHANx->NDTR = 0;
   CHANx->PAR  = 0;
   CHANx->M0AR = 0;
   CHANx->M1AR = 0;
   CHANx->FCR  = (uint32_t)0x00000021; /* FIFO control register */

   /* clear interrupt mask */
   dma.resetStream( this );

   return *this;
}


DMAStream& DMAStream::enable( void )
{
   dma.enable();

   DMA_Stream_TypeDef *CHANx = (DMA_Stream_TypeDef*)iobase;
   CHANx->CR |= (uint32_t)DMA_SxCR_EN;

   return *this;
}


DMAStream& DMAStream::disable( void )
{
   DMA_Stream_TypeDef *CHANx = (DMA_Stream_TypeDef*)iobase;
   CHANx->CR &= ~((uint32_t)DMA_SxCR_EN);

   dma.disable();

   return *this;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void DMAStream::isr( void )
{ ; }


/* trampolines */

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
