
#ifndef _QB50_SYS_DEVICE_ADC_H
#define _QB50_SYS_DEVICE_ADC_H

#include "Device.h"
#include <task.h>


namespace qb50 {

   typedef uint16_t adcval_t;

   class ADC : public Device
   {

      protected:

         struct IOReq;

      public:

         #include "_ADC_Channel.h"

         ADC( const char *name );
         virtual ~ADC();

         virtual ADC& init    ( void );
         virtual ADC& enable  ( bool silent = false );
         virtual ADC& disable ( bool silent = false );

             adcval_t read    ( Channel& ch );
             adcval_t read    ( unsigned cid );
                 void _run    ( void );


      protected:

         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

         /* IOCTLs */

         enum IOCTL {
            ENABLE   = 0,
            DISABLE  = 1,
            READ     = 2,
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

         struct IOReq_enable : public IOReq
         {
            bool _silent;

            IOReq_enable( bool silent )
            : IOReq( ENABLE ), _silent( silent )
            { ; }
         };

         struct IOReq_disable : public IOReq
         {
            bool _silent;

            IOReq_disable( bool silent )
            : IOReq( DISABLE ), _silent( silent )
            { ; }
         };

         struct IOReq_read : public IOReq
         {
            Channel& _ch;
            adcval_t _rv;

            IOReq_read( Channel& ch )
            : IOReq( READ ), _ch( ch )
            { ; }
         };

         /* operations */

                 void _ioctl   ( IOReq *req, TickType_t maxWait = portMAX_DELAY );

         virtual void _enable  ( IOReq_enable  *req ) = 0;
         virtual void _disable ( IOReq_disable *req ) = 0;
       //virtual void _reset   ( IOReq_reset   *req ) = 0;
         virtual void _read    ( IOReq_read    *req ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_ADC_H*/

/*EoF*/
