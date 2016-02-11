
#include "FipexThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FipexThread::FipexThread()
   : Thread( "Fipex", 1, true )
{ ; }


FipexThread::~FipexThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

static uint8_t cmd_ping[]    = { 0x7e, 0x00, 0x00, 0x00 };
static uint8_t cmd_hk[]      = { 0x7e, 0x20, 0x00, 0x20 };
static uint8_t cmd_sp_mt10[] = { 0x7e, 0x11, 0x03, 0x02, 0x0a, 0x00, 0x1a };
static uint8_t cmd_sm[]      = { 0x7e, 0x0c, 0x00, 0x0c };
static uint8_t cmd_sp_si1[]  = { 0x7e, 0x11, 0x03, 0x08, 0x01, 0x00, 0x1b };


void FipexThread::cmd( uint8_t *cmd, size_t len )
{
   uint8_t *x = new uint8_t[ 256 ];
   char    *o = new char[ 32 ];
   size_t dlen;

   UART2.write( cmd, len );
   UART2.read( x, 205 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."

   dlen = x[2];

   kprintf( "%s: < 0x%02x 0x%02x 0x%02x 0x%02x\r\n", name, x[0], x[1], x[2], x[3] );
   kprintf( "%s: len: %zu\r\n", name, dlen );
   kprintf( "%s: seq: %d\r\n", name, x[3] );

   delete[] o;
   delete[] x;
}


void FipexThread::test( void )
{
   uint8_t *x = new uint8_t[ 256 ];
   char    *o = new char[ 32 ];
   unsigned i5;
   size_t   n;

   kprintf( "%s: FIPEX Functional Test Procedure\r\n", name );

   kprintf( "%s: STEP #5 - switching FIPEX on\r\n", name );
   PB14.out().off();
   // Req: FPX-SW-0240 - "The OBC shall wait 500ms before initializing the UART interface [...]"
   delay( 500 );

   kprintf( "%s: STEP #6 - SU_PING @NOW\r\n", name );
   cmd( cmd_ping, 4 );
   delay( 100 );

   kprintf( "%s: STEP #7 - SU_HK @NOW\r\n", name );
   cmd( cmd_hk, 4 );
   delay( 100 );

   kprintf( "%s: STEP #8 - SU_SP meas_time = 10 @00:01\r\n", name );
   cmd( cmd_sp_mt10, 7 );
   delay( 1000 );

   kprintf( "%s: STEP #9 - SU_SM @NOW\r\n", name );
   cmd( cmd_sm, 4 );
   delay( 100 );

   for( int i = 0 ; i < 4 ; ++i ) {
      UART2.read( x, 205 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."
      kprintf( "%s: < 0x%02x 0x%02x 0x%02x 0x%02x\r\n", name, x[0], x[1], x[2], x[3] );
      kprintf( "%s: len: %d\r\n", name, x[2] );
      kprintf( "%s: seq: %d\r\n", name, x[3] );
   }

   for( ;; ) {
      i5 = ADC4CH5.read();
      if( i5 < 10 ) break;
      delay( 100 );
   }

   kprintf( "%s: i5 < 10\r\n", name );

   kprintf( "%s: STEP #11 - SU_SP stm_interval = 1 @01:00\r\n", name );
   cmd( cmd_sp_si1, 7);

   for( ;; ) {
      UART2.read( x, 205 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."
      kprintf( "%s: < 0x%02x 0x%02x 0x%02x 0x%02x\r\n", name, x[0], x[1], x[2], x[3] );
      kprintf( "%s: len: %d\r\n", name, x[2] );
      kprintf( "%s: seq: %d\r\n", name, x[3] );
   }

   delay( 60 * 1000 );

   ;

   delete[] o;
   delete[] x;
}


void FipexThread::run( void )
{
   //LOG << "FipexThread starting..." << std::flush;
   UART2.enable();

   // retrieve script

   Config::pval_t sn = CONF.getParam( Config::PARAM_FIPEX_SCRIPT_N );

 //PC3.enable().out().on(); /* ON_OFF_GPS */

   _wait();
   test();

   for( ;; ) {
      _wait();
      delay( 1000 );
/*
      n = UART2.readLine( x, 128 );
      (void)UART6.write( x, n );
      (void)UART6.write( "\r\n", 2 );
*/
   }
}

/*EoF*/
