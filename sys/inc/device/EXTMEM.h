
#ifndef _QB50_SYS_DEVICE_EXTMEM_H
#define _QB50_SYS_DEVICE_EXTMEM_H

#include "FreeRTOS.h"
#include "Device.h"


namespace qb50 {

   class EXTMEM : public Device
   {
      public:

         EXTMEM( unsigned id );
         ~EXTMEM();

         void reset   ( void );
         void enable  ( void );
         void disable ( void );

      private:

         unsigned id;
   };

   extern qb50::EXTMEM EXTMEM1;
   extern qb50::EXTMEM EXTMEM2;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_EXTMEM_H*/

/*EoF*/
