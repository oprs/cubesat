
#ifndef _QB50_SYS_DEVICE_DMA_STREAM_H
#define _QB50_SYS_DEVICE_DMA_STREAM_H

#include "Device.h"

#include <stdint.h>


namespace qb50 {

   class DMA;

   class DMAStream : public Device
   {
      public:

         DMAStream( DMA& dma, const uint32_t iobase );
         ~DMAStream();

         DMAStream& reset    ( void );
         DMAStream& enable   ( void );
         DMAStream& disable  ( void );

         //void baseAddr ( void     *addr );
         //void dataSize ( unsigned  mds  );

         // DMA_InitTypeDef
         // DMA_DeInit
         // DMA_Init

         void isr( void );

         DMA&           dma;
         const uint32_t iobase;
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


#endif /*_QB50_SYS_DEVICE_DMA_STREAM_H*/

/*EoF*/
