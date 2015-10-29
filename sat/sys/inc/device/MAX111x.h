
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include "device/ADC.h"
#include "device/SPISlave.h"


namespace qb50 {

   class MAX111x : public ADC, public SPISlave
   {

      protected:

         struct IOReq;


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

         /* XXX #include "_MAX111x_Channel.h" */
         struct Channel : public ADC::Channel
         {
            ChId _id;

            Channel( MAX111x& adc, const char *name, ChId id )
            : ADC::Channel( adc, name ), _id( id )
            { ; }

            virtual ~Channel()
            { ; }

            Channel& init    ( void );
            Channel& enable  ( bool silent = false );
            Channel& disable ( bool silent = false );
         };

         MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin );
         ~MAX111x();

         MAX111x& init    ( void );
       //MAX111x& reset   ( void );
         MAX111x& enable  ( bool silent = false );
         MAX111x& disable ( bool silent = false );
         adcval_t read    ( ADC::Channel& ch );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
