
#ifndef _QB50_SYS_DEVICE_BASEBAND_H
#define _QB50_SYS_DEVICE_BASEBAND_H

#include "Device.h"
#include "GPIO.h"


namespace qb50 {

   class Baseband : public Device
   {

      public:

         Baseband( const char *name, GPIO::Pin& enTXPin, GPIO::Pin& enPAPin );
         ~Baseband();

         Baseband& init    ( void );
         Baseband& enable  ( bool silent = false );
         Baseband& disable ( bool silent = false );


      private:

         GPIO::Pin& _enTXPin;
         GPIO::Pin& _enPAPin;

   };

   extern qb50::Baseband BB;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_BASEBAND_H*/

/*EoF*/
