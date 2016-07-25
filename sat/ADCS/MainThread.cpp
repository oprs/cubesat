
#include "MainThread.h"
#include "common/Message.h"
#include "config.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MainThread::MainThread()
   : Thread( "Main Thread", 2, RUNNING, 384 )
{
   ;
}


MainThread::~MainThread()
{
   ;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void MainThread::onSuspend( void )
{
   Thread::onSuspend();

   UART1.disable();
    GYR0.disable();
    MAG0.disable();
}


void MainThread::onResume( void )
{
   GYR0.enable();
   MAG0.enable();
   UART1.enable().baudRate( 115200 );

   Thread::onResume();
}


void MainThread::run( void )
{
   SensorSample<uint16_t> sunv[ 6 ];

   ADCSMeas msg;
   Timer    tm;

    SUN1.enable();
    SUN2.enable();
    SUN3.enable();
    SUN4.enable();
    SUN5.enable();
    SUN6.enable();

    GYR0.enable();
    MAG0.enable();

   UART1.enable();

   GYR0.calibrate(); // XXX !

   for( ;; ) {

      tm.every( 1000 );

      GYR0.omega( msg.gyr );
      kprintf( "GYR0: [ %0.2f %0.2f %0.2f ]\r\n", msg.gyr.x, msg.gyr.y, msg.gyr.z );

      MAG0.omega( msg.mag );
      kprintf( "MAG0: [ %0.2f %0.2f %0.2f ]\r\n", msg.mag.x, msg.mag.y, msg.mag.z );

      ADC1.read( SUN1, &sunv[ 0 ]);
      ADC1.read( SUN2, &sunv[ 1 ]);
      ADC1.read( SUN3, &sunv[ 2 ]);
      ADC1.read( SUN4, &sunv[ 3 ]);
      ADC1.read( SUN5, &sunv[ 4 ]);
      ADC1.read( SUN6, &sunv[ 5 ]);

      kprintf(
         "SUNV: [ %u %u %u %u %u %u ]\r\n",
         sunv[0].value, sunv[1].value, sunv[2].value,
         sunv[3].value, sunv[4].value, sunv[5].value
      );

      msg.xf = sunv[0].value >> 4;
      msg.xr = sunv[1].value >> 4;
      msg.yf = sunv[2].value >> 4;
      msg.yr = sunv[3].value >> 4;
      msg.zf = sunv[4].value >> 4;
      msg.zr = sunv[5].value >> 4;

      (void)UART1.write( (const uint8_t*)&msg, sizeof( ADCSMeas ), 100 );

   }
}


/*EoF*/
