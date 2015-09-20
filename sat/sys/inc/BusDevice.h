
#ifndef _QB50_SYSTEM_BUS_DEVICE_H
#define _QB50_SYSTEM_BUS_DEVICE_H

#include "Device.h"
#include "Bus.h"


namespace qb50 {

   class BusDevice : public Device
   {
      public:

         BusDevice( Bus& bus, const uint32_t iobase, const uint32_t periph, const char *name )
            : Device( name ), bus( bus ), iobase( iobase ), periph( periph )
         { ; }

         virtual ~BusDevice()
         { ; }

         Bus&           bus;
         const uint32_t iobase;
         const uint32_t periph;

         virtual BusDevice& init    ( void ) = 0;
         virtual BusDevice& enable  ( void ) = 0;
         virtual BusDevice& disable ( void ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_DEVICE_H*/

/*EoF*/
