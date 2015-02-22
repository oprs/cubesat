
#include "device/DMAStream.h"
#include "system/qb50.h"

#include <stm32f4xx.h>

#undef DMA1
#undef DMA2

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMAStream::DMAStream( DMA& dma,
                      const uint32_t iobase,
                      const uint32_t shl )
   : _dma( dma ),
     _iobase( iobase ),
     _shl( shl )
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
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   DMA_TypeDef        *DMAx  = (DMA_TypeDef*)_dma.iobase;

   //_dma.enable();

   /* reset the stream */

   STRMx->CR   = 0x00000000;
   STRMx->NDTR = 0x00000000;
   STRMx->PAR  = 0x00000000;
   STRMx->M0AR = 0x00000000;
   STRMx->M1AR = 0x00000000;
   STRMx->FCR  = 0x00000001;

   /* clear interrupt flags */

   if( _shl & 0x20 ) {
      DMAx->HIFCR |= ( 0x3f << ( _shl & 0x1f ));
   } else {
      DMAx->LIFCR |= ( 0x3f <<   _shl         );
   }

   //_dma.disable();

   return *this;
}


DMAStream& DMAStream::enable( void )
{
   _dma.enable(); /* _dma.refcount */

   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->CR |= DMA_SxCR_EN;

   return *this;
}


DMAStream& DMAStream::disable( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->CR &= ~DMA_SxCR_EN;

   _dma.disable(); /* _dma.refcount */

   return *this;
}


DMAStream& DMAStream::counter( uint16_t cnt )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->NDTR = (uint32_t)cnt;

   return *this;
}


DMAStream& DMAStream::pAddr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->PAR = addr;

   return *this;
}


DMAStream& DMAStream::m0Addr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->M0AR = addr;

   return *this;
}


DMAStream& DMAStream::m1Addr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->M1AR = addr;

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

DMAStream& DMAStream::_updateCR( uint32_t val, uint32_t mask, int shift )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   register uint32_t tmp32;

   tmp32  = STRMx->CR;
   tmp32 &= ~( mask << shift );
   tmp32 |=  (  val << shift );
   STRMx->CR = tmp32;

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
