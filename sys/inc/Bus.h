
#ifndef _QB50_SYSTEM_BUS_H
#define _QB50_SYSTEM_BUS_H

#include <stdint.h>


namespace qb50 {

   /* forward declaration */
   class CoreDevice;

   class Bus
   {
      public:
         Bus() { ; }
         virtual ~Bus() { ; }

         virtual void enable  ( CoreDevice *dev ) = 0;
         virtual void disable ( CoreDevice *dev ) = 0;
   };

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_H*/

/*EoF*/
