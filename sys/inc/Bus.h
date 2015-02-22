
#ifndef _QB50_SYSTEM_BUS_H
#define _QB50_SYSTEM_BUS_H

#include <stdint.h>


namespace qb50 {

   class BusDevice;

   class Bus
   {
      public:
         Bus() { ; }
         virtual ~Bus() { ; }

         virtual void enable  ( BusDevice *dev ) = 0;
         virtual void disable ( BusDevice *dev ) = 0;
   };

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_H*/

/*EoF*/
