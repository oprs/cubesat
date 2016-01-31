
#ifndef _QB50_SYS_DEVICE_ADC_H
#define _QB50_SYS_DEVICE_ADC_H

#include "Device.h"


namespace qb50 {

   typedef uint16_t adcval_t;

   class ADC
   {

      protected:

         struct IOReq;

      public:

         #include "ADC_Channel.h"

         ADC()
         { ; }

         virtual ~ADC()
         { ; }

         virtual adcval_t read    ( Channel& ch  ) = 0;
       //virtual adcval_t read    ( unsigned cid ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_ADC_H*/

/*EoF*/
