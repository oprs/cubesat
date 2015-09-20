
#ifndef _QB50_SYS_DEVICE_TRANSCEIVER_H
#define _QB50_SYS_DEVICE_TRANSCEIVER_H

#include "Device.h"
#include "GPIOPin.h"


namespace qb50 {

   class Transceiver : public Device
   {

      public:

         Transceiver( const char *name, GPIOPin& enPin );

         ~Transceiver();

         Transceiver& init    ( void );
         Transceiver& enable  ( void );
         Transceiver& disable ( void );


      private:

         GPIOPin& _enPin;

   };

} /* qb50 */

#endif /*_QB50_SYS_DEVICE_TRANSCEIVER_H*/

/*EoF*/
