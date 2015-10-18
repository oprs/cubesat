
#ifndef _QB50_SYS_DEVICE_DMA_H
#define _QB50_SYS_DEVICE_DMA_H

#include "Device.h"
#include "BusSlave.h"
#include "DMAStream.h"


namespace qb50 {

   class DMA : public Device, public BusSlave
   {

      public:

         DMA( Bus& bus, const uint32_t iobase, const uint32_t periph, const char *name );
         ~DMA();

         DMA& init    ( void );
         DMA& enable  ( bool silent = false );
         DMA& disable ( bool silent = false );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_DMA_H*/

/*EoF*/
