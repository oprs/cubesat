
#include "device/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIOPin& csPin )
   : SPIDevice( spi, csPin, SPIDevice::ActiveLow, name )
{
   _ioQueue = xQueueCreate( 1, sizeof( IOReq* ));
}


MAX111x::~MAX111x()
{ vQueueDelete( _ioQueue ); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::init( void )
{
   (void)SPIDevice::init();

   LOG << _name << ": Onboard MAX111x Serial ADC at " << _spi.name()
       << ", cs: " << _csPin.name();

   (void)xTaskCreate( _trampoline, _name, 512, this, configMAX_PRIORITIES - 1, &_ioTask );

   return *this;
}


MAX111x& MAX111x::ioctl( IOReq *req, TickType_t maxWait )
{
   (void)xQueueSend( _ioQueue, &req, maxWait );
   (void)ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
   return *this;
}


MAX111x& MAX111x::enable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( ENABLE );
   (void)ioctl( &req );
   return *this;
}


MAX111x& MAX111x::disable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( DISABLE );
   (void)ioctl( &req );
   return *this;
}


int MAX111x::readChannel( Channel sel )
{
   IOReq_RDCH req( sel );
   (void)ioctl( &req );

   return (int)req._raw;
}


int MAX111x::readChannel( int n )
{
   Channel ch[ 8 ] = { CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7 };
   return( readChannel( ch[ n & 0x07 ] ));
}


void MAX111x::readAll( void )
{
   ;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

static void _trampoline( void *x )
{
   MAX111x *self = (MAX111x*)x;
   self->run();
   vTaskDelete( NULL );
}


void MAX111x::run( void )
{
   IOReq *req;

   for( ;; ) {
      if( xQueueReceive( _ioQueue, &req, portMAX_DELAY ) != pdPASS )
         continue;

      _spi.grab(); // lock the SPI bus
      select();    // chip select ON

      switch( req->_op ) {
         case ENABLE:  _enable();                      break;
         case DISABLE: _disable();                     break;
         case RDCH:    _RDCH    (  (IOReq_RDCH*)req ); break;
         case RDALL:   _RDALL   ( (IOReq_RDALL*)req ); break;
      }

      deselect();     // chip select OFF
      _spi.release(); // release the SPI bus

      (void)xTaskNotifyGive( req->_handle );
   }
}


void MAX111x::_RDCH( IOReq_RDCH *req )
{
   uint8_t ConvCmd[ 4 ];
   uint8_t ConvRes[ 4 ];

   ConvCmd[ 0 ] = 0x00;
   ConvCmd[ 1 ] = 0x8f | (( req->_ch & 0x07 ) << 4 ) ;
   ConvCmd[ 2 ] = 0x00;
   ConvCmd[ 3 ] = 0x00;

   _spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));

   req->_raw = (( ConvRes[2] << 8 ) | ConvRes[3] ) >> 6;
}


void MAX111x::_RDALL( IOReq_RDALL *req )
{
   (void)req; /* XXX */
}


/*EoF*/
