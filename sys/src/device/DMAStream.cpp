
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
{ ; }


DMAStream::~DMAStream()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMAStream& DMAStream::reset( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   DMA_TypeDef        *DMAx  = (DMA_TypeDef*)_dma.iobase;

   //_dma.enable();
QB50DBG( "DMAStream::reset()\r\n" );

   /* reset the stream */

   STRMx->CR  &= ~DMA_SxCR_EN;
   STRMx->CR   = 0x00000000;
   STRMx->NDTR = 0x00000000;
   STRMx->PAR  = 0x00000000;
   STRMx->M0AR = 0x00000000;
   STRMx->M1AR = 0x00000000;
   STRMx->FCR  = 0x00000021;

   /* clear interrupt flags */

   if( _shl & 0x20 ) {
      DMAx->HIFCR |= ( 0x3d << ( _shl & 0x1f ));
   } else {
      DMAx->LIFCR |= ( 0x3d <<   _shl         );
   }

   //_dma.disable();

   return *this;
}


DMAStream& DMAStream::enable( void )
{
QB50DBG( "DMAStream::enable()\r\n" );
   _dma.enable(); /* _dma.refcount */
   reset();

   return *this;
}


DMAStream& DMAStream::disable( void )
{
QB50DBG( "DMAStream::disable()\r\n" );
   _dma.disable(); /* _dma.refcount */
   return *this;
}


DMAStream& DMAStream::start( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->CR |= DMA_SxCR_EN;

   return *this;
}


DMAStream& DMAStream::stop( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->CR &= ~DMA_SxCR_EN;

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

/*EoF*/
