
#ifndef _QB50_SYS_DEVICE_BACKUP_H
#define _QB50_SYS_DEVICE_BACKUP_H

#include "BusDevice.h"


namespace qb50 {

   class Backup : public BusDevice
   {

      public:

         Backup( Bus& bus,
                 const uint32_t iobase,
                 const uint32_t periph,
                 const char    *name
         );

         ~Backup();

         Backup& init    ( void );
         Backup& enable  ( bool silent = false );
         Backup& disable ( bool silent = false );

   };

   extern qb50::Backup BKP;

}


#endif /*_QB50_SYS_DEVICE_BACKUP_H*/

/*EoF*/