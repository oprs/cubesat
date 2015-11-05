
#ifndef _QB50_SYS_DEVICE_GPIO_H
#define _QB50_SYS_DEVICE_GPIO_H

#include "Device.h"


namespace qb50 {

   class GPIO : public Device
   {

      public:

         #include "GPIO_Pin.h"

         GPIO( const char *name, const Pin *pins )
            : Device( name ), _pins( pins )
         { ; }

         virtual ~GPIO()
         { ; }

         virtual GPIO& init    ( void )                = 0;
         virtual GPIO& enable  ( bool silent = false ) = 0;
         virtual GPIO& disable ( bool silent = false ) = 0;


      protected:

         const Pin *_pins;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_GPIO_H*/

/*EoF*/
