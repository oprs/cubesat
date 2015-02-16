
#ifndef _QB50_SYSTEM_CORE_DEVICE_H
#define _QB50_SYSTEM_CORE_DEVICE_H

#include "Device.h"
#include "Bus.h"


namespace qb50 {

   class CoreDevice : public Device
   {
      public:

         CoreDevice( Bus& bus, const uint32_t periph, const uint32_t iobase )
            : bus( bus ), periph( periph ), iobase( iobase ) {}
         virtual ~CoreDevice() {}

         Bus&     bus;
         const uint32_t periph;
         const uint32_t iobase;

         virtual void reset   ( void ) = 0;
         virtual void enable  ( void ) = 0;
         virtual void disable ( void ) = 0;
   };

} /* qb50 */


#endif /*_QB50_SYSTEM_CORE_DEVICE_H*/

/*EoF*/
