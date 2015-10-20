
#ifndef _QB50_SYS_DEVICE_DMA_H
#define _QB50_SYS_DEVICE_DMA_H

#include "Device.h"
#include "BusSlave.h"


namespace qb50 {

   class DMA : public Device, public BusSlave
   {

      public:

         #include "_DMA_Stream.h"

         DMA( Bus& bus, const uint32_t iobase, const uint32_t periph, const char *name );
         ~DMA();

         DMA& init    ( void );
         DMA& enable  ( bool silent = false );
         DMA& disable ( bool silent = false );

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


#endif /*_QB50_SYS_DEVICE_DMA_H*/

/*EoF*/
