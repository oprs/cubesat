
#include "MainThread.h"
#include "CommandThread.h"
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
   UART1.enable();

   Thread::onResume();
}


void MainThread::run( void )
{
   SensorSample<uint16_t> sunv[ 6 ];
   Vec3D gyr, mag;
   Timer tm;

   SUN1.enable();
   SUN2.enable();
   SUN3.enable();
   SUN4.enable();
   SUN5.enable();
   SUN6.enable();

   GYR0.enable();
   MAG0.enable();

   TIM1.enable();
   TIM2.enable();

   UART1.enable();

   (void)registerThread( new CommandThread() );

   ADCSBeat *bp = new ADCSBeat();

   for( ;; ) {

      tm.every( 1000 );

      GYR0.omega( gyr );
      kprintf( "GYR0: [ %0.2f %0.2f %0.2f ]\r\n", gyr.x, gyr.y, gyr.z );

      MAG0.omega( mag );
      kprintf( "MAG0: [ %0.2f %0.2f %0.2f ]\r\n", mag.x, mag.y, mag.z );

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

      bp->ctrl.d = AST0.d;
      bp->ctrl.x = AST0.x;
      bp->ctrl.y = AST0.y;
      bp->ctrl.z = AST0.z;

      bp->meas.gxyz[0] = (int)( gyr.x / 16.0 );
      bp->meas.gxyz[1] = (int)( gyr.y / 16.0 );
      bp->meas.gxyz[2] = (int)( gyr.z / 16.0 );

      bp->meas.mxyz[0] = (int)( mag.x / 16.0 );
      bp->meas.mxyz[1] = (int)( mag.y / 16.0 );
      bp->meas.mxyz[2] = (int)( mag.z / 16.0 );

      bp->meas.xf = sunv[0].value >> 4;
      bp->meas.xr = sunv[1].value >> 4;
      bp->meas.yf = sunv[2].value >> 4;
      bp->meas.yr = sunv[3].value >> 4;
      bp->meas.zf = sunv[4].value >> 4;
      bp->meas.zr = sunv[5].value >> 4;

      (void)UART1.write( (const uint8_t*)bp, sizeof( ADCSBeat ), 100 );

      if( AST0.d > 0 ) {
         /* attitude control */
      }

   }

   delete bp;
}


/*EoF*/
