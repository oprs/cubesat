
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


/*
 * Mask for ( CTCIFx | CHTIFx | CTEIFx | CDMEIFx | CFEIFx )
 *            _____    ______   ______   _______   _____
 *              |        |        |         |        |
 *              |        |        |         |        +- 0x01
 *              |        |        |         +---------- 0x04
 *              |        |        +-------------------- 0x08
 *              |        +----------------------------- 0x10
 *              +-------------------------------------- 0x20
 *                                                     ------
 *                                                      0x3d
 * See the STM32F4 ref. manual, pp. 325-326.
 */

#define DMAStream0_4_IFCR    0x3d
#define DMAStream1_5_IFCR  ( 0x3d <<  6 )
#define DMAStream2_6_IFCR  ( 0x3d << 16 )
#define DMAStream3_7_IFCR  ( 0x3d << 22 )

void DMA::resetStream( DMAStream *stream )
{
   DMA_TypeDef *DMAx = (DMA_TypeDef *)iobase;

   switch( stream->iobase ) {

      case DMA1_Stream0_BASE:
      case DMA2_Stream0_BASE:
         DMAx->LIFCR = DMAStream0_4_IFCR;
         break;

      case DMA1_Stream1_BASE:
      case DMA2_Stream1_BASE:
         DMAx->LIFCR = DMAStream1_5_IFCR;
         break;

      case DMA1_Stream2_BASE:
      case DMA2_Stream2_BASE:
         DMAx->LIFCR = DMAStream2_6_IFCR;
         break;

      case DMA1_Stream3_BASE:
      case DMA2_Stream3_BASE:
         DMAx->LIFCR = DMAStream3_7_IFCR;
         break;

      case DMA1_Stream4_BASE:
      case DMA2_Stream4_BASE:
         DMAx->HIFCR = DMAStream0_4_IFCR;
         break;

      case DMA1_Stream5_BASE:
      case DMA2_Stream5_BASE:
         DMAx->HIFCR = DMAStream1_5_IFCR;
         break;

      case DMA1_Stream6_BASE:
      case DMA2_Stream6_BASE:
         DMAx->HIFCR = DMAStream2_6_IFCR;
         break;

      case DMA1_Stream7_BASE:
      case DMA2_Stream7_BASE:
         DMAx->HIFCR = DMAStream3_7_IFCR;
         break;

      default:
         throw( 42 ); /*XXX*/
   }
}


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
