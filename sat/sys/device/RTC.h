
#ifndef _QB50_SYS_DEVICE_RTC_H
#define _QB50_SYS_DEVICE_RTC_H

#include "Device.h"


namespace qb50 {

   class RTC
   {

      public:

         RTC()
         { ; }

         virtual ~RTC()
         { ; }


         struct Time
         {
            uint16_t year;
            uint8_t  mon;
            uint8_t  day;
            uint8_t  hour;
            uint8_t  min;
            uint8_t  sec;
         };

         virtual RTC& getTime ( Time &t ) = 0;
         virtual RTC& setTime ( Time &t ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_RTC_H*/

/*EoF*/
