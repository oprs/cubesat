
#include "TelemThread.h"
#include "Config.h"
#include "devices.h"

#include <cstring> // XXX out!

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TelemThread::TelemThread()
   : Thread( "Telem", 1, SUSPENDED, 512 )
{ ; }


TelemThread::~TelemThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void TelemThread::run( void )
{
   uint8_t *x = new uint8_t[ 4096 ];

   for( ;; ) {
      _wait();
memset( x, 0, 4096 );
      FCACHE.read( 8000, x, 256 );
      hexdump( x, 256 );
      delay( 5000 );
kprintf( "waiting...\r\n" );
   }

   delete[] x;
}


void TelemThread::onSuspend( void )
{
   FCACHE.disable();
   Thread::onSuspend();
}


void TelemThread::onResume( void )
{
   Thread::onResume();
   FCACHE.enable();
}


/*EoF*/
