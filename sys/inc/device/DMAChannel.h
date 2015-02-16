
#ifndef _QB50_SYS_DEVICE_DMA_CHANNEL_H
#define _QB50_SYS_DEVICE_DMA_CHANNEL_H

#include "FreeRTOS.h"

#include "stm32f4xx_dma.h"
#include "CoreDevice.h"


namespace qb50 {

   class DMAChannel : public CoreDevice
   {
      public:

         DMAChannel( Bus& bus, const uint32_t periph, const uint32_t iobase );
         ~DMAChannel();

         void reset   ( void );
         void enable  ( void );
         void disable ( void );

         void isr( void );
   };

} /* qb50 */


extern "C" {
   void DMA1_Stream0_IRQHandler( void );
   void DMA1_Stream1_IRQHandler( void );
   void DMA1_Stream2_IRQHandler( void );
   void DMA1_Stream3_IRQHandler( void );
   void DMA1_Stream4_IRQHandler( void );
   void DMA1_Stream5_IRQHandler( void );
   void DMA1_Stream6_IRQHandler( void );
   void DMA1_Stream7_IRQHandler( void );

   void DMA2_Stream0_IRQHandler( void );
   void DMA2_Stream1_IRQHandler( void );
   void DMA2_Stream2_IRQHandler( void );
   void DMA2_Stream3_IRQHandler( void );
   void DMA2_Stream4_IRQHandler( void );
   void DMA2_Stream5_IRQHandler( void );
   void DMA2_Stream6_IRQHandler( void );
   void DMA2_Stream7_IRQHandler( void );
}


#endif /*_QB50_SYS_DEVICE_DMA_CHANNEL_H*/

/*EoF*/
