
#ifndef _QB50_SYS_DEVICE_TRANSCEIVER_H
#define _QB50_SYS_DEVICE_TRANSCEIVER_H

#include "Device.h"
#include "GPIO.h"


namespace qb50 {

   class Transceiver : public Device
   {

      public:

         Transceiver( const char *name, GPIO::Pin& enTXPin, GPIO::Pin& enPAPin );

         ~Transceiver();

         Transceiver& init    ( void );
         Transceiver& enable  ( bool silent = false );
         Transceiver& disable ( bool silent = false );


      private:

         GPIO::Pin& _enTXPin;
         GPIO::Pin& _enPAPin;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_TRANSCEIVER_H*/

/*EoF*/
