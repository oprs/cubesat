
#ifndef _QB50_SYS_DEVICE_A25LXXX_H
#define _QB50_SYS_DEVICE_A25LXXX_H

#include "device/SPI.h"
#include "device/GPIOPin.h"


namespace qb50 {

   class A25Lxxx : public Device
   {
      public:

         A25Lxxx( uint32_t id, SPI& spi, GPIOPin& csPin );
         ~A25Lxxx();

         A25Lxxx& reset   ( void );
         A25Lxxx& enable  ( void );
         A25Lxxx& disable ( void );

      private:

         uint32_t _id;
         SPI&     _spi;
         GPIOPin& _csPin;
   };

   extern qb50::A25Lxxx softMem;
   extern qb50::A25Lxxx dataMem;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_A25LXXX_H*/

/*EoF*/
