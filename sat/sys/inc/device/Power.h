
#ifndef _QB50_SYS_DEVICE_POWER_H
#define _QB50_SYS_DEVICE_POWER_H

#include "BusDevice.h"


namespace qb50 {

   class Power : public BusDevice
   {

      public:

         Power( Bus& bus,
               const uint32_t iobase,
               const uint32_t periph,
               const char    *name );

         ~Power();

         Power& init    ( void );

         Power& enable  ( bool silent = false );
         Power& disable ( bool silent = false );

         Power& enableBKPSRAM  ( void );
         Power& disableBKPSRAM ( void );

   };

   extern qb50::Power PWR;

}


#endif /*_QB50_SYS_DEVICE_POWER_H*/

/*EoF*/

