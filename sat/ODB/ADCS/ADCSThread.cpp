
#include "devices.h"
#include "common/Message.h"
#include "ADCSThread.h"


using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADCSThread::ADCSThread()
   : Thread( "ADCS Thread", 1, SUSPENDED, 384 )
{
   _x = new uint8_t[ 256 ];
}


ADCSThread::~ADCSThread()
{
   delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void ADCSThread::run( void )
{
   unsigned n;

   for( ;; ) {
      _wait();

      n = ADCS0.read( _x, sizeof( ADCSMeas ), 5000 );
      if( n == 0 ) {
         (void)kprintf( "%s: waiting...\r\n", name );
         continue;
      }

      ADCSMeas *mp = (ADCSMeas*)_x;
      (void)kprintf( "GOT GYR0: [ %.2f %.2f %.2f ]\r\n", mp->gyr.x, mp->gyr.y, mp->gyr.z );
      (void)kprintf( "GOT MAG0: [ %.2f %.2f %.2f ]\r\n", mp->mag.x, mp->mag.y, mp->mag.z );
   }
}


void ADCSThread::onSuspend()
{
   ADCS0.disable();
   Thread::onSuspend();
}


void ADCSThread::onResume()
{
   Thread::onResume();
   ADCS0.enable();
}


/*EoF*/
