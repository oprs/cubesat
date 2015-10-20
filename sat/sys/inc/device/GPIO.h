
#ifndef _QB50_SYS_GPIO_H
#define _QB50_SYS_GPIO_H

#include "Device.h"
#include "BusSlave.h"


namespace qb50 {

   class GPIO : public Device, public BusSlave
   {
      public:

         #include "_GPIO_Pin.h"

         GPIO( Bus& bus, const uint32_t iobase, const uint32_t periph, const unsigned id, const char *name, Pin *pins );
         ~GPIO();

         GPIO& init    ( void );
         GPIO& enable  ( bool silent = false );
         GPIO& disable ( bool silent = false );

         unsigned id ( void ) const { return _id;   }

      private:

         const unsigned _id;
         Pin *_pins;
   };

} /* qb50 */


#endif /*_QB50_SYS_GPIO_H*/

/*EoF*/
