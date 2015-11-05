
#include "STM32/DMA.h"
#include "system/qb50.h" // XXX

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

DMA::Stream::Stream( DMA& dma,
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


DMA::Stream::~Stream()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

DMA::Stream& DMA::Stream::init( void )
{ return *this; }


DMA::Stream& DMA::Stream::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   NVIC.enable( _IRQn );
   _dma.enable( silent );

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


DMA::Stream& DMA::Stream::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _dma.disable( silent ); /* _dma.refcount */
   NVIC.disable( _IRQn );

   return *this;
}


DMA::Stream& DMA::Stream::start( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   /* clear interrupt flags */

   _clearIFR( 0x3d );

   STRMx->CR &= ~DMA_SxCR_EN;
   STRMx->CR |= ( DMA_SxCR_TCIE | DMA_SxCR_TEIE );
   STRMx->CR |= DMA_SxCR_EN;

   return *this;
}


DMA::Stream& DMA::Stream::stop( void )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;

   STRMx->CR &= ~DMA_SxCR_EN;
   STRMx->CR &= ~( DMA_SxCR_TCIE | DMA_SxCR_TEIE );

   return *this;
}


DMA::Stream& DMA::Stream::wait( void )
{
   xSemaphoreTake( _isrTxIE, portMAX_DELAY );

   return *this;
}


DMA::Stream& DMA::Stream::counter( uint16_t cnt )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->NDTR = (uint32_t)cnt;

   return *this;
}


DMA::Stream& DMA::Stream::pAddr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->PAR = addr;

   return *this;
}


DMA::Stream& DMA::Stream::m0Addr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->M0AR = addr;

   return *this;
}


DMA::Stream& DMA::Stream::m1Addr( uint32_t addr )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   STRMx->M1AR = addr;

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

DMA::Stream& DMA::Stream::_updateCR( uint32_t val, uint32_t mask, int shift )
{
   DMA_Stream_TypeDef *STRMx = (DMA_Stream_TypeDef*)_iobase;
   register uint32_t tmp32;

   tmp32  = STRMx->CR;
   tmp32 &= ~( mask << shift );
   tmp32 |=  (  val << shift );
   STRMx->CR = tmp32;

   return *this;
}


DMA::Stream& DMA::Stream::_clearIFR( uint32_t flags )
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

void DMA::Stream::isr( void )
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
