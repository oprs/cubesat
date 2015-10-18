
#include "device/ADC.h"
#include "system/Logger.h"

using namespace qb50;


static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADC::ADC( const char *name )
   : Device( name )
{
   _ioQueue = xQueueCreate( 1, sizeof( IOReq* ));
}


ADC::~ADC()
{
   vQueueDelete( _ioQueue );
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ADC& ADC::init( void )
{
   (void)xTaskCreate( _trampoline, _name, 384, this, configMAX_PRIORITIES - 1, &_ioTask );

/*
   LOG << _name << ": System UART controller at " << bus.name
       << ", rx: " << _rxPin.name()
       << ", tx: " << _txPin.name()
       ;
*/

   return *this;
}


ADC& ADC::enable( bool silent )
{
   IOReq_enable req( silent );
   _ioctl( &req );

   return *this;
}


ADC& ADC::disable( bool silent )
{
   IOReq_disable req( silent );
   _ioctl( &req );

   return *this;
}


adcval_t ADC::read( Channel& ch )
{
   IOReq_read req( ch );
   _ioctl( &req );

   return req._rv;
}


adcval_t ADC::read( unsigned cid )
{
   return 0;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

static void _trampoline( void *x )
{
   ADC *self = (ADC*)x;
   self->_run();
   vTaskDelete( NULL );
}


void ADC::_ioctl( IOReq *req, TickType_t maxWait )
{
   (void)xQueueSend( _ioQueue, &req, maxWait );
   (void)ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
}


void ADC::_run( void )
{
   IOReq *req;

   for( ;; ) {
      if( xQueueReceive( _ioQueue, &req, portMAX_DELAY ) != pdPASS )
         continue;

      _lock();

      switch( req->_op ) {
         case ENABLE:  _enable  (  (IOReq_enable*)req ); break;
         case DISABLE: _disable ( (IOReq_disable*)req ); break;
       //case RESET:   _reset   (   (IOReq_reset*)req ); break;
         case READ:    _read    (    (IOReq_read*)req ); break;
      }

      _unlock();
      (void)xTaskNotifyGive( req->_handle );
   }
}

/*EoF*/
