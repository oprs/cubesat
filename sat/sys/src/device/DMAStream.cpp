
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
                      const uint32_t IRQn,
                      const char *name,
                      const uint32_t shl )
   : Device( name ),
     _dma( dma ),
     _iobase( iobase ),
     _IRQn( IRQn ),
     _shl( shl )
{
   _isrTxIE = xSemaphoreCreateBinary();
}


DMAStream::~DMAStream()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMAStream& DMAStream::init( void )
{ return *this; }


DMAStream& DMAStream::enable( void )
{
   if( _incRef() > 0 )
      return *this;

   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   IRQ.enable( _IRQn );
   _dma.enable();

   /* reset the stream */

   STRMx->CR  &= ~DMA_SxCR_EN;
   STRMx->CR   = 0x00000000;
   STRMx->NDTR = 0x00000000;
   STRMx->PAR  = 0x00000000;
   STRMx->M0AR = 0x00000000;
   STRMx->M1AR = 0x00000000;
   STRMx->FCR  = 0x00000021;

   /* clear interrupt flags */

   _clearIFR( 0x3d );

   return *this;
}


DMAStream& DMAStream::disable( void )
{
   if( _decRef() > 0 )
      return *this;

   _dma.disable(); /* _dma.refcount */
   IRQ.disable( _IRQn );

   return *this;
}


DMAStream& DMAStream::start( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   /* clear interrupt flags */

   _clearIFR( 0x3d );

   STRMx->CR |= ( DMA_SxCR_TCIE | DMA_SxCR_TEIE );
   STRMx->CR |= DMA_SxCR_EN;

   return *this;
}


DMAStream& DMAStream::stop( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   STRMx->CR &= ~DMA_SxCR_EN;
   STRMx->CR &= ~( DMA_SxCR_TCIE | DMA_SxCR_TEIE );

   return *this;
}


DMAStream& DMAStream::wait( void )
{
   xSemaphoreTake( _isrTxIE, portMAX_DELAY );

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


DMAStream& DMAStream::_clearIFR( uint32_t flags )
{
   DMA_TypeDef *DMAx = (DMA_TypeDef*)_dma.iobase;

   if( _shl & 0x20 ) {
      DMAx->HIFCR = ( flags << ( _shl & 0x1f ));
   } else {
      DMAx->LIFCR = ( flags <<   _shl         );
   }

   return *this;
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void DMAStream::isr( void )
{
   DMA_TypeDef  *DMAx   = (DMA_TypeDef*)_dma.iobase;
   portBASE_TYPE hpTask = pdFALSE;
   uint32_t      SR;

   if( _shl & 0x20 ) {
      SR = ( DMAx->HISR >> ( _shl & 0x1f )) & 0x3d;
   } else {
      SR = ( DMAx->LISR >>   _shl         ) & 0x3d;
   }

   if( SR & 0x08 /*TEIF*/ ) {
      /* transfer error */
      _clearIFR( 0x08 );
   }

   if( SR & 0x20 /*TCIF*/) {
      /* transfer complete */
      _clearIFR( 0x20 );
   }

   xSemaphoreGiveFromISR( _isrTxIE, &hpTask );

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
}

/*EoF*/
