
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include "device/SPI.h"
#include "device/GPIOPin.h"


namespace qb50 {

   class MAX111x : public Device
   {
      public:

         MAX111x( SPI& spi, GPIOPin& csPin );
         ~MAX111x();

         MAX111x& enable  ( void );
         MAX111x& disable ( void );

      private:

         SPI&     _spi;
         GPIOPin& _csPin;
   };

   extern qb50::MAX111x maxADC;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
