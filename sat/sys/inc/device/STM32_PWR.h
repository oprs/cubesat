
#ifndef _QB50_SYS_DEVICE_STM32_PWR_H
#define _QB50_SYS_DEVICE_STM32_PWR_H

#include "Device.h"
#include "BusSlave.h"


namespace qb50 {

   class STM32_PWR : public Device, public BusSlave
   {

      public:

         STM32_PWR( Bus& bus,
                    const uint32_t iobase,
                    const uint32_t periph,
                    const char    *name );

         ~STM32_PWR();

         STM32_PWR& init    ( void );

         STM32_PWR& enable  ( bool silent = false );
         STM32_PWR& disable ( bool silent = false );

         STM32_PWR& enableBKPSRAM  ( void );
         STM32_PWR& disableBKPSRAM ( void );

   };

   extern qb50::STM32_PWR PWR;

}


#endif /*_QB50_SYS_DEVICE_STM32_PWR_H*/

/*EoF*/

