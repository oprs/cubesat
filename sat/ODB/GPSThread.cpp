
#include "GPSThread.h"
#include "devices.h"
#include "system/Logger.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPSThread::GPSThread()
   : Thread( "GPS", 1, SUSPENDED, 384 )
{ ; }


GPSThread::~GPSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void GPSThread::run( void )
{
   uint8_t *x = new uint8_t[ 128 ];
   size_t n;

   PC3.out().pullDn(); /* ON_OFF_GPS */

   for( ;; ) {
      _wait();
      n = UART3.readLine( x, 128, 10000 );
      if( n > 0 ) {
         UART6.write( x, n );
         UART6.write( "\r\n", 2 );
         //kprintf( "%s: %*s\r\n", name, n, x );
         //kprintf( "%s: OK\r\n", name );
      } else {
         kprintf( "%s: " RED( "timeout in UART3.readLine()" ) "\r\n", name );
      }
   }

   delete[] x;
}


void GPSThread::onSuspend()
{
   UART3.disable();
   PC3.off();
   Thread::onSuspend();
}


void GPSThread::onResume()
{
   Thread::onResume();
   PC3.on();
   UART3.enable();
}

/*EoF*/
