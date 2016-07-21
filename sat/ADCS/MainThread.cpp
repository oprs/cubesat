
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
   ADCSMeas msg;
   Timer    tm;

    GYR0.enable();
    MAG0.enable();
   UART1.enable().baudRate( 115200 );

   GYR0.calibrate(); // XXX !

   for( ;; ) {

      tm.every( 1000 );

      GYR0.omega( msg.gyr );
      kprintf( "GYR0: [ %0.2f %0.2f %0.2f ]\r\n", msg.gyr.x, msg.gyr.y, msg.gyr.z );

      MAG0.omega( msg.mag );
      kprintf( "MAG0: [ %0.2f %0.2f %0.2f ]\r\n", msg.mag.x, msg.mag.y, msg.mag.z );

      msg.xf = 0.0f;
      msg.xr = 0.0f;
      msg.yf = 0.0f;
      msg.yr = 0.0f;
      msg.zf = 0.0f;
      msg.zr = 0.0f;

      (void)UART1.write( &msg, sizeof( ADCSMeas ), 100 );

   }
}


/*EoF*/
