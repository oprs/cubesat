
#ifndef _QB50_SYS_DEVICE_STM32_PWR_H
#define _QB50_SYS_DEVICE_STM32_PWR_H

#include "STM32/STM32_Device.h"


namespace qb50 {

   class STM32_PWR : public STM32_Device
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

         STM32_PWR& enableBKP  ( void );
         STM32_PWR& disableBKP ( void );

   };

   extern qb50::STM32_PWR PWR;

}


#endif /*_QB50_SYS_DEVICE_STM32_PWR_H*/

/*EoF*/

