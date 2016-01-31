
#ifndef _QB50_SYS_DEVICE_GPIO_H
#define _QB50_SYS_DEVICE_GPIO_H


namespace qb50 {

   class GPIO
   {

      public:

         #include "GPIO_Pin.h"

         GPIO( const Pin *pins )
            : _pins( pins )
         { ; }

         virtual ~GPIO()
         { ; }


      protected:

         const Pin *_pins;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_GPIO_H*/

/*EoF*/
