
#include "FipexThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FipexThread::FipexThread()
   : Thread( "Fipex", 1, SUSPENDED, 512 )
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
static uint8_t cmd_stdby[]   = { 0x7e, 0x0a, 0x00, 0x0a };


static const char *rsp_unk = "unknown";
#define UNKNOWN rsp_unk

static const char *rsp_ids[ 64 ]  = {

   /* 0x00 - 0x0f */

   UNKNOWN,    UNKNOWN,    "SU_R_ACK", "SU_R_NACK",
   "SU_R_ID",  UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,

   /* 0x10 - 0x1f */

   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,

   /* 0x20 - 0x2f */

   "SU_R_HK",  UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,

   /* 0x30 - 0x3f */

   "SU_R_SDP", UNKNOWN,    UNKNOWN,    "SU_R_CAL",
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN,
   UNKNOWN,    UNKNOWN,    UNKNOWN,    UNKNOWN
};


void FipexThread::cmd( uint8_t *cmd, size_t len )
{
   uint8_t *x = new uint8_t[ 256 ];
   char    *o = new char[ 32 ];
   size_t n, dlen;

   UART2.write( cmd, len );
   n = UART2.read( x, 205, 1000 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."

   if( n == 0 ) {
      kprintf( RED( "%s: n: %lu" ) "\r\n", name, n );
      kprintf( RED( "%s: tiemout in cmd()" ) "\r\n", name );
   } else {
      kprintf( GREEN( "%s: n: %lu" ) "\r\n", name, n );

      dlen = x[2];

      kprintf( "%s: len: %lu\r\n", name, dlen );
      kprintf( "%s: seq: %d\r\n", name, x[3] );
      hexdump( x, n );
   }

   delete[] o;
   delete[] x;
}


void FipexThread::dump( uint8_t *x, size_t len )
{
   size_t dlen = x[2];
   const char *name = rsp_ids[ x[1] % 0x3f ];

//hexdump( x, len );

   kprintf( "         SB: 0x%02x\r\n",      x[0] );
   kprintf( "     RSP_ID: 0x%02x (%s)\r\n", x[1], name );
   kprintf( "        LEN: %d\r\n",         dlen );
   kprintf( "    SEQ_CNT: %d\r\n",         x[3] );

   switch( x[1] ) {
      case 0x30: dump_sdp( x + 4, len - 4 ); break;
      default:
         ;
   }
}


void FipexThread::dump_sdp( uint8_t *x, size_t len )
{
   uint32_t tf = x[0] | ( x[1] << 8 ) | ( x[2] << 16 ) | ( x[3] << 24 );
   uint32_t ts = x[4] | ( x[5] << 8 ) | ( x[6] << 16 ) | ( x[7] << 24 );

   kprintf( " TIME_FIPEX: %f\r\n",     0.1 * tf );
   kprintf( "   TIME_STM: %f\r\n",     0.1 * ts );
   kprintf( "         ID: 0x%02x\r\n", x[8] );

   int i = 1;

   size_t off = 9;

   for( ;; ) {
      uint8_t sh = x[ off ];
      uint8_t tp = ( sh >> 6 ) & 0x01;
      kprintf( " - SAMPLE #%d:\r\n", i++ );
      kprintf( " Header byte: 0x%02x\r\n", sh );
      kprintf( "        Gain: %d\r\n", (  sh        & 0x03 ));
      kprintf( "      Sensor: %d\r\n", (( sh >> 3 ) & 0x03 ));

      if( tp == 1 ) {
         /* FIPEX */
         kprintf( "        Type: FIPEX\r\n" );
         hexdump( x + off + 1, 7 );
         off += ( 7 + 1 );
      } else {
         /* STM */
         kprintf( "        Type: STM\r\n" );
         hexdump( x + off + 1, 9 );
         off += ( 9 + 1 );
      }

      if( sh & 0x80 ) break;
   }
}


void FipexThread::test( void )
{
   uint8_t *x = new uint8_t[ 256 ];
   char    *o = new char[ 32 ];
   SensorSample<uint8_t> i3, i5;
   size_t   i, n;

   kprintf( "%s: FIPEX Functional Test Procedure\r\n", name );

   kprintf( "%s: STEP #5 - switching FIPEX on\r\n", name );
   PB14.out().off();
   // Req: FPX-SW-0240 - "The OBC shall wait 500ms before initializing the UART interface [...]"
(void)ADC4CH5.read( &i5 );
(void)ADC4CH3.read( &i3 );
kprintf( "i5: %lu\r\n", i5 );
kprintf( "i3: %lu\r\n", i3 );
   delay( 500 );
(void)ADC4CH5.read( &i5 );
(void)ADC4CH3.read( &i3 );
kprintf( "i5: %lu\r\n", i5 );
kprintf( "i3: %lu\r\n", i3 );

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

   for( i = 0 ; i < 32 ; ++i ) {
      n = UART2.read( x, 205, 1000 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."
      if( n > 0 ) {
       //kprintf( "%s: < 0x%02x 0x%02x 0x%02x 0x%02x\r\n", name, x[0], x[1], x[2], x[3] );
/*
         kprintf( "%s: len: %d\r\n", name, x[2] );
         kprintf( "%s: seq: %d\r\n", name, x[3] );
         hexdump( x, n );
*/
         dump( x, n );
      } else {
         kprintf( RED( "%s: UART2.read() timeout" ) "\r\n", name );
         (void)ADC4CH5.read( &i5 );
         (void)ADC4CH3.read( &i3 );
         kprintf( "i5: %lu\r\n", i5 );
         kprintf( "i3: %lu\r\n", i3 );
         if( i5.value < 3 ) {
            kprintf( GREEN( "%s: i5 < 3" ) "\r\n", name );
            break;
         }
      }
   }

   kprintf( "%s: STEP #11 - SU_SP stm_interval = 1 @01:00\r\n", name );
   cmd( cmd_sp_si1, 7);

   for( i = 0 ; i < 5 ; ++i ) {
      _wait();
      UART2.read( x, 205 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."
    //kprintf( "%s: < 0x%02x 0x%02x 0x%02x 0x%02x\r\n", name, x[0], x[1], x[2], x[3] );
      kprintf( "%s: len: %d\r\n", name, x[2] );
      kprintf( "%s: seq: %d\r\n", name, x[3] );
      //hexdump( x, 205 );
      dump( x, 205 );
(void)ADC4CH5.read( &i5 );
(void)ADC4CH3.read( &i3 );
kprintf( "i5: %lu\r\n", i5 );
kprintf( "i3: %lu\r\n", i3 );
   }

   cmd( cmd_stdby, 4 );

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

   for( ;; ) {
      _wait();
      test();
      delay( 1000 );
   }
}


void FipexThread::onSuspend( void )
{
   PB14.out().on();
   Thread::onSuspend();
}


void FipexThread::onResume( void )
{
   Thread::onResume();
   PB14.out().off();
}


/*EoF*/
