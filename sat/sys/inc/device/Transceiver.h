
#ifndef _QB50_SYS_DEVICE_TRANSCEIVER_H
#define _QB50_SYS_DEVICE_TRANSCEIVER_H

#include "Device.h"
#include "GPIOPin.h"


namespace qb50 {

   class Transceiver : public Device
   {

      public:

         Transceiver( const char *name, GPIOPin& enTXPin, GPIOPin& enPAPin );

         ~Transceiver();

         Transceiver& init    ( void );
         Transceiver& enable  ( bool silent = false );
         Transceiver& disable ( bool silent = false );


      private:

         GPIOPin& _enTXPin;
         GPIOPin& _enPAPin;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_TRANSCEIVER_H*/

/*EoF*/
