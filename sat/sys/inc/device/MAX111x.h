
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include "device/SPIDevice.h"


namespace qb50 {

   class MAX111x : public SPIDevice
   {
      public:

         MAX111x( SPI& spi, GPIOPin& csPin );
         ~MAX111x();

         MAX111x& enable  ( void );
         MAX111x& disable ( void );

         /* perform conversion */

         struct ConvResp {
            uint8_t rb1;
            uint8_t rb2;
            uint8_t rb3;
            uint8_t rb4;
         } __attribute__(( packed ));

         /* channel selection */

         enum Channel {
            CH0 = 0, /*!< channel 0 */
            CH1 = 1, /*!< channel 1 */
            CH2 = 2, /*!< channel 2 */
            CH3 = 3, /*!< channel 3 */
            CH4 = 4, /*!< channel 4 */
            CH5 = 5, /*!< channel 5 */
            CH6 = 6, /*!< channel 6 */
            CH7 = 7  /*!< channel 7 */
         };

         MAX111x& conv( Channel sel, ConvResp *resp );
   };

   extern qb50::MAX111x maxADC;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
