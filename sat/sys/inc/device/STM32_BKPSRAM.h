
#ifndef _QB50_SYS_DEVICE_STM32_BKPSRAM_H
#define _QB50_SYS_DEVICE_STM32_BKPSRAM_H

#include "Device.h"
#include "BusSlave.h"


namespace qb50 {

   class STM32_BKPSRAM : public Device, public BusSlave
   {

      public:

         STM32_BKPSRAM( Bus& bus,
                 const uint32_t iobase,
                 const uint32_t periph,
                 const char    *name
         );

         ~STM32_BKPSRAM();

         STM32_BKPSRAM& init    ( void );
         STM32_BKPSRAM& enable  ( bool silent = false );
         STM32_BKPSRAM& disable ( bool silent = false );

   };

   extern qb50::STM32_BKPSRAM BKP;

}


#endif /*_QB50_SYS_DEVICE_STM32_BKPSRAM_H*/

/*EoF*/
