
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include "device/SPIDevice.h"


namespace qb50 {

   class MAX111x : public SPIDevice
   {

      private:

         struct IOReq;

      public:

         MAX111x( SPI& spi, const char *name, GPIOPin& csPin );
         ~MAX111x();

         MAX111x& init( void );

         MAX111x& ioctl( IOReq *req, TickType_t maxWait = portMAX_DELAY );

         /* channel selection */

         enum Channel {
            CH0 = 0, /*!< channel 0 */
            CH1 = 4, /*!< channel 1 */
            CH2 = 1, /*!< channel 2 */
            CH3 = 5, /*!< channel 3 */
            CH4 = 2, /*!< channel 4 */
            CH5 = 6, /*!< channel 5 */
            CH6 = 3, /*!< channel 6 */
            CH7 = 7  /*!< channel 7 */
         };

         MAX111x& enable      ( void );
         MAX111x& disable     ( void );
         int      readChannel ( Channel sel );
         int      readChannel ( int n );
         void     readAll     ( void );

         void run( void );

      private:

         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

         enum IOCTL {
            ENABLE  = 0,
            DISABLE = 1,
            RDCH    = 2,
            RDALL   = 3
         };

         struct IOReq
         {
            IOCTL        _op;
            TaskHandle_t _handle;

            IOReq( IOCTL op ) : _op( op )
            { _handle = xTaskGetCurrentTaskHandle(); }

            ~IOReq()
            { ; }
         };

         struct IOReq_RDCH : public IOReq
         {
            Channel _ch;
            uint8_t _raw;

            IOReq_RDCH( Channel ch )
            : IOReq( RDCH ), _ch( ch )
            { ; }
         };

         struct IOReq_RDALL : public IOReq
         {
            uint8_t *_raw;

            IOReq_RDALL() : IOReq( RDALL )
            { ; }
         };

         /* operations */

         void _RDCH  ( IOReq_RDCH  *req );
         void _RDALL ( IOReq_RDALL *req );

   };

   extern qb50::MAX111x ADC1;
   extern qb50::MAX111x ADC2;
   extern qb50::MAX111x ADC3;
   extern qb50::MAX111x ADC4;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
