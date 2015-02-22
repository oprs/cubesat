
#ifndef _QB50_SYS_DEVICE_DMA_H
#define _QB50_SYS_DEVICE_DMA_H

#include "DMAStream.h"
#include "BusDevice.h"


namespace qb50 {

   class DMA : public BusDevice
   {
      public:

         DMA( Bus& bus, const uint32_t iobase, const uint32_t periph, DMAStream *streams );
         ~DMA();

         DMA& reset   ( void );
         DMA& enable  ( void );
         DMA& disable ( void );

         void isr( void );

         DMAStream *streams;
   };

   extern qb50::DMA DMA1;
   extern qb50::DMA DMA2;

} /* qb50 */


extern "C" {
   void DMA1_IRQHandler( void );
   void DMA2_IRQHandler( void );
}


#endif /*_QB50_SYS_DEVICE_DMA_H*/

/*EoF*/
