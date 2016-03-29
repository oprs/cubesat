
#ifndef _QB50_SYS_DEVICE_SPI_MAX111x_H
#define _QB50_SYS_DEVICE_SPI_MAX111x_H

#include "SPI/Device.h"
#include "ADC.h"


namespace qb50 {

   class MAX111x : public SPI_Device, public ADC
   {

      private:

         uint8_t *_x;


      public:

         /* channel selection */

         enum ChId {
            CH0 = 0, /*!< channel 0 */
            CH1 = 4, /*!< channel 1 */
            CH2 = 1, /*!< channel 2 */
            CH3 = 5, /*!< channel 3 */
            CH4 = 2, /*!< channel 4 */
            CH5 = 6, /*!< channel 5 */
            CH6 = 3, /*!< channel 6 */
            CH7 = 7  /*!< channel 7 */
         };

         #include "MAX111x_Channel.h"

         MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin );
         ~MAX111x();

         MAX111x& init    ( void );
       //MAX111x& reset   ( void );
         MAX111x& enable  ( bool silent = false );
         MAX111x& disable ( bool silent = false );
         adcval_t read    ( ADC::Channel& ch );
         MAX111x& readAll ( adcval_t *rvp );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_MAX111x_H*/

/*EoF*/
