
#ifndef _QB50_SYSTEM_DEVICE_H
#define _QB50_SYSTEM_DEVICE_H

#include "system/Application.h"

namespace qb50 {

   class Device
   {
      public:

         Device() {}
         virtual ~Device() {}

         virtual Device& enable  ( void ) = 0;
         virtual Device& disable ( void ) = 0;
   };

} /* qb50 */


#endif /*_QB50_SYSTEM_DEVICE_H*/

/*EoF*/
