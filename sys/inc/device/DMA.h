
#ifndef _QB50_SYS_DEVICE_DMA_H
#define _QB50_SYS_DEVICE_DMA_H

#include "FreeRTOS.h"

#include "stm32f4xx_dma.h"
#include "CoreDevice.h"
#include "DMAChannel.h"


namespace qb50 {

   class DMA : public CoreDevice
   {
      public:

         DMA( Bus& bus, const uint32_t periph, const uint32_t iobase, DMAChannel *chan );
         ~DMA();

         void reset   ( void );
         void enable  ( void );
         void disable ( void );

         void isr( void );

         DMAChannel *chan;
   };

   /* CMSIS keeps polluting the whole namespace with
      hundreds of macros, we need to clear those off. */

   #undef DMA1
   #undef DMA2

   extern qb50::DMA DMA1;
   extern qb50::DMA DMA2;

} /* qb50 */


extern "C" {
   void DMA1_IRQHandler( void );
   void DMA2_IRQHandler( void );
}


#endif /*_QB50_SYS_DEVICE_DMA_H*/

/*EoF*/
