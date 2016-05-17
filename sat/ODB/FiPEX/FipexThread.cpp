
#include "FipexThread.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FipexThread::FipexThread()
   : Thread( "Fipex", 1, SUSPENDED, 512 )
{
   rx = new uint8_t[ 256 ];
}


FipexThread::~FipexThread()
{
   delete[] rx;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

static uint8_t cmd_ping[]    = { 0x7e, 0x00, 0x00, 0x00 };
static uint8_t cmd_hk[]      = { 0x7e, 0x20, 0x00, 0x20 };
static uint8_t cmd_sp_mt10[] = { 0x7e, 0x11, 0x03, 0x02, 0x0a, 0x00, 0x1a };
static uint8_t cmd_sm[]      = { 0x7e, 0x0c, 0x00, 0x0c };
static uint8_t cmd_sp_si1[]  = { 0x7e, 0x11, 0x03, 0x08, 0x01, 0x00, 0x1b };
static uint8_t cmd_stdby[]   = { 0x7e, 0x0a, 0x00, 0x0a };


static const uint8_t FPX_E2E_1_1[] = {
   0x23, 0x6c, 0x06, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_2[] = {
   0x23, 0x98, 0x07, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_3[] = {
   0x23, 0xc4, 0x08, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_4[] = {
   0x23, 0xf0, 0x09, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_5[] = {
   0x23, 0x1c, 0x0b, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_6[] = {
   0x23, 0x48, 0x0c, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_1_7[] = {
   0x23, 0x74, 0x0d, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_2[] = {
   0x29, 0xf8, 0xa6, 0x42, 0x1e, 0x00, 0x00, 0x06,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xfe, 0x06, 0x7e, 0x20, 0x00, 0x20,  0xf4, 0x06, 0x7e, 0x20, 0x00, 0x20, 0x0a, 0x00,
   0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00, 0x7e, 0xff,  0x01, 0xfe
};

static const uint8_t FPX_E2E_5[] = {
   0x29, 0x40, 0x05, 0x42, 0x1e, 0x00, 0x00, 0x06,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x00, 0x00, 0x01,  0x0a, 0x00, 0x7e, 0x20, 0x00, 0x20, 0x0a, 0x00,
   0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00, 0x7e, 0xff,  0x01, 0xfe
};

static const uint8_t FPX_E2E_6[] = {
   0x23, 0x40, 0x05, 0x42, 0x1e, 0x00, 0x00, 0x05,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x0a, 0x00, 0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00,
   0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_7_1[] = {
   0x29, 0x80, 0x5c, 0x41, 0x1e, 0x00, 0x00, 0x06,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20, 0xd2, 0x00,
   0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00, 0x7e, 0xff,  0x01, 0xfe
};

static const uint8_t FPX_E2E_7_2[] = {
   0x0b, 0x00, 0xae, 0x42, 0x1e, 0x00, 0x00, 0x01,  0x7e, 0xff, 0x01, 0xfe
};

static const uint8_t FPX_E2E_7_3[] = {
   0x29, 0x80, 0xff, 0x43, 0x1e, 0x00, 0x00, 0x06,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20,  0xd2, 0x00, 0x7e, 0x20, 0x00, 0x20, 0xd2, 0x00,
   0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00, 0x7e, 0xff,  0x01, 0xfe
};

static const uint8_t FPX_E2E_8[] = {
   0x29, 0xc0, 0x56, 0x43, 0x1e, 0x58, 0x02, 0x06,  0x7e, 0x0f, 0x00, 0x0f, 0x0a, 0x00, 0x7e, 0x20,
   0x00, 0x20, 0x1e, 0x00, 0x7e, 0x20, 0x00, 0x20,  0x1e, 0x00, 0x7e, 0x20, 0x00, 0x20, 0x1e, 0x00,
   0x7e, 0xf0, 0x00, 0xf0, 0x0a, 0x00, 0x7e, 0xff,  0x01, 0xfe
};


static const uint8_t *sv[] = {
//FPX_E2E_5,
   FPX_E2E_1_1,
   FPX_E2E_1_2,
   FPX_E2E_1_3,
   FPX_E2E_1_4,
   FPX_E2E_1_5,
   FPX_E2E_1_6,
   FPX_E2E_1_7,
   FPX_E2E_2,
   FPX_E2E_5,
   FPX_E2E_6,
   FPX_E2E_7_1,
   FPX_E2E_7_2,
   FPX_E2E_7_3,
   FPX_E2E_8
};


static const char *unk = "unknown";
#define UNKNOWN unk

static const char *rsp_ids[ 64 ] = {

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


void FipexThread::cmd( const uint8_t *cmd, size_t len )
{
   size_t n, dlen;

   UART2.write( cmd, len );
   n = UART2.read( rx, 205, 1000 ); // Req: FPX-SW-0190 - "The response packet size shall be 205 bytes."

   if( n == 0 ) {
      kprintf( RED( "%s: n: %lu" ) "\r\n", name, n );
      kprintf( RED( "%s: tiemout in cmd()" ) "\r\n", name );
   } else {
      kprintf( GREEN( "%s: n: %lu" ) "\r\n", name, n );

      dlen = rx[2];

      kprintf( "%s: len: %lu\r\n", name, dlen );
      kprintf( "%s: seq: %d\r\n", name, rx[3] );
    //hexdump( rx, n );

      (void)WOD.write( WodStore::FIPEX, rx, n );
   }
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
   MAX111x::Sample i3, i5;
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
   PB14.out().on();
   UART2.enable();

   // retrieve script

   Config::pval_t sn;

   for( ;; ) {
      _wait();

      sn = CONF.getParam( Config::PARAM_FIPEX_SCRIPT_N );
      kprintf( GREEN( "%s: RUNNING SCRIPT: %d" ) "\r\n", name, sn );

      _runScript( sv[ sn - 1 ], true );

      //test();
      delay( 5000 );
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


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

struct FipexHeader
{
   uint8_t  len;   // script length
   uint32_t stime; // start time
   uint16_t rtime; // repeat time
   uint8_t  cnt;   // command count
} __attribute__(( packed ));

#define VKI_EPOCH 946684800
#define HDRLEN    sizeof( FipexHeader )


void FipexThread::_runScript( const uint8_t *x, bool debug )
{
   const FipexHeader *fh = (const FipexHeader*)x;
   int   len = fh->len;
   int   dt, clen;
   uint8_t sum;

   x   += HDRLEN;
   len -= HDRLEN + 1;

   struct tm stm;
   time_t t = fh->stime + VKI_EPOCH;
   (void)gmtime_r( &t, &stm );

   if( debug ) {
      RTC::Time now;
      RTC0.getTime( now );
      int dt = t - RTC::conv( now );

      kprintf( "%s: script length: %d bytes\r\n", name, fh->len   );
      kprintf( "%s:    start time: %04d-%02d-%02d %02d:%02d:%02d\r\n",
               name, 1900 + stm.tm_year, stm.tm_mon, stm.tm_mday,
                            stm.tm_hour, stm.tm_min, stm.tm_sec );
      if( dt < 0 ) {
         kprintf( "%s:                (%d seconds ago)\r\n", name, -dt );
      } else {
         kprintf( "%s:                (%d seconds from now)\r\n", name, dt );
      }
      kprintf( "%s:   repeat time: %d sec.\r\n",  name, fh->rtime );
      kprintf( "%s: command count: %d\r\n",       name, fh->cnt   );
   }

   for( int i = 0 ; i < fh->cnt; ++i ) {
      if( x[0] != 0x7e ) {
         kprintf( RED( "%s: start byte not found - aborting" ) "\r\n", name );
         break;
      }

      if( x[2] == 0xff ) {

         /* end of script marker */

         if(( x[2] == 0x01 ) && ( x[3] == 0xfe )) {
            if( i != ( fh->cnt - 1 )) {
               kprintf( RED( "%s: unexpected end of script - aborting" ) "\r\n", name );
               break;
            } else {
               kprintf( "%s: END OF SCRIPT\r\n", name );
               break;
            }
         } else {
               kprintf( RED( "%s: got some garbage - aborting" ) "\r\n", name );
               break;
         }

      } else {

         /* regular command */

         if( i == ( fh->cnt - 1 )) {
            kprintf( RED( "%s: end of script not found - aborting" ) "\r\n", name );
            break;
         }

         clen = x[2];
         sum  = 0;

hexdump( x, clen + 6 );

         for( int j = 0 ; j < ( clen + 2 ) ; ++j )
            sum ^= x[ 1 + j ];

         if( sum != x[ clen + 3 ] ) {
            kprintf( RED( "%s: checksum mismatch - aborting" ) "\r\n", name );
            break;
         }

         if( debug ) {
            kprintf( "%s: command 0x%02x, len: %d\r\n", name, x[1], clen );
         }

         cmd( x, clen + 4 );

         x += clen + 4;
         dt = x[0] | ( (int)x[1] << 8 );
         x += 2;

         if( debug ) {
            kprintf( "%s: delay: %d sec.\r\n", name, dt );
         }

         delay( dt * 1000 );

      }
   }
}

/*EoF*/
