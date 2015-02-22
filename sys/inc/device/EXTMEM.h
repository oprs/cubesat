
#ifndef _QB50_SYS_DEVICE_EXTMEM_H
#define _QB50_SYS_DEVICE_EXTMEM_H

#include "Device.h"


namespace qb50 {

   class EXTMEM : public Device
   {
      public:

         EXTMEM( unsigned id );
         ~EXTMEM();

         EXTMEM& reset   ( void );
         EXTMEM& enable  ( void );
         EXTMEM& disable ( void );

      private:

         unsigned id;
   };

   extern qb50::EXTMEM EXTMEM1;
   extern qb50::EXTMEM EXTMEM2;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_EXTMEM_H*/

/*EoF*/
