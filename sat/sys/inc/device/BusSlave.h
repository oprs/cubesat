
#ifndef _QB50_SYSTEM_BUS_SLAVE_H
#define _QB50_SYSTEM_BUS_SLAVE_H

#include "Bus.h"


namespace qb50 {

   class BusSlave
   {

      public:

         BusSlave( Bus& bus, const uint32_t iobase, const uint32_t periph )
            : bus( bus ), iobase( iobase ), periph( periph )
         { ; }

         virtual ~BusSlave()
         { ; }

         Bus&           bus;
         const uint32_t iobase;
         const uint32_t periph;

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_SLAVE_H*/

/*EoF*/
