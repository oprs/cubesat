
#ifndef _QB50_SYS_DEVICE_SPI_LSM303_H
#define _QB50_SYS_DEVICE_SPI_LSM303_H

#include "SPI/Device.h"
#include "Gyro.h"


namespace qb50 {

   class LSM303 : public SPI_Device, public Gyro
   {

      public:

         enum Range {
            R250DPS  = 0,
            R500DPS  = 1,
            R2000DPS = 2
         };

         LSM303( SPI&        spi,
                 const char *name,
                 GPIO::Pin&  csPin,
                 Range       r = R250DPS );
         ~LSM303();

         LSM303& init      ( void );
         LSM303& reset     ( void );
         LSM303& enable    ( bool silent = false );
         LSM303& disable   ( bool silent = false );

         LSM303& omega     ( vec3d& v );
         LSM303& range     ( Range  r );
         LSM303& calibrate ( void );


      protected:

         int16_t _calX;
         int16_t _calY;
         int16_t _calZ;
         Range   _range;

         void _WHO_AM_I ( uint8_t& id  );

   };

} /*qb50*/


#endif /*_QB50_SYS_DEVICE_SPI_LSM303_H*/

/*EoF*/
