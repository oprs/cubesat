
#include "MainThread.h"
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
   GYR0.disable();
}


void MainThread::onResume( void )
{
   GYR0.enable();
}


void MainThread::run( void )
{
   Timer tm;
   Gyro::vec3d v;

   _wait();

   GYR0.enable();

   GYR0.calibrate();

   for( ;; ) {

      tm.every( 2000 );

      GYR0.omega( v );
      kprintf( "GYR0: [ %0.2f %0.2f %0.2f ]\r\n", v.xr, v.yr, v.zr );

   }
}


/*EoF*/
