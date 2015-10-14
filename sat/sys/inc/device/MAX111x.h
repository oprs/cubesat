
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include "Device.h"
#include "device/SPISlave.h"

#include <task.h>


namespace qb50 {

   class MAX111x : public Device, public SPISlave
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

         MAX111x& enable      ( bool silent = false );
         MAX111x& disable     ( bool silent = false );
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

         struct IOReq_ENABLE : public IOReq
         {
            bool _silent;

            IOReq_ENABLE( bool silent )
            : IOReq( ENABLE ), _silent( silent )
            { ; }
         };

         struct IOReq_DISABLE : public IOReq
         {
            bool _silent;

            IOReq_DISABLE( bool silent )
            : IOReq( DISABLE ), _silent( silent )
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

         void _enable  ( IOReq_ENABLE  *req );
         void _disable ( IOReq_DISABLE *req );
         void _RDCH    ( IOReq_RDCH    *req );
         void _RDALL   ( IOReq_RDALL   *req );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
