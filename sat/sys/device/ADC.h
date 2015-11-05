
#ifndef _QB50_SYS_DEVICE_ADC_H
#define _QB50_SYS_DEVICE_ADC_H

#include "Device.h"
#include <task.h>


namespace qb50 {

   typedef uint16_t adcval_t;

   class ADC : public Device
   {

      protected:

         struct IOReq;

      public:

         #include "ADC_Channel.h"

         ADC( const char *name )
         : Device( name )
         { ; }

         virtual ~ADC()
         { ; }

         virtual ADC&     init    ( void         ) = 0;
       //virtual ADC&     reset   ( void         ) = 0;
         virtual ADC&     enable  ( bool silent  ) = 0;
         virtual ADC&     disable ( bool silent  ) = 0;
         virtual adcval_t read    ( Channel& ch  ) = 0;
       //virtual adcval_t read    ( unsigned cid ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_ADC_H*/

/*EoF*/
