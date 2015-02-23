
#ifndef _QB50_SYS_DEVICE_EXTMEM_H
#define _QB50_SYS_DEVICE_EXTMEM_H

#include "device/SPI.h"
#include "device/GPIOPin.h"


namespace qb50 {

   class EXTMEM : public Device
   {
      public:

         EXTMEM( uint32_t id, SPI& spi, GPIOPin& csPin );
         ~EXTMEM();

         EXTMEM& reset   ( void );
         EXTMEM& enable  ( void );
         EXTMEM& disable ( void );

      private:

         uint32_t _id;
         SPI&     _spi;
         GPIOPin& _csPin;
   };

   extern qb50::EXTMEM EXTMEM1;
   extern qb50::EXTMEM EXTMEM2;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_EXTMEM_H*/

/*EoF*/
