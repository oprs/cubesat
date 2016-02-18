
#include "devices.h"
#include "ADCSThread.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADCSThread::ADCSThread()
   : Thread( "ADCS Thread", 1, SUSPENDED )
{ ; }


ADCSThread::~ADCSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void ADCSThread::run( void )
{
   PC13.out().off();

   for( ;; ) {
      _wait();
      delay( 100 );
      //kprintf( "--------[ ADCS ]--------\r\n" );
   }
}


void ADCSThread::onSuspend()
{
   PC13.off();
   Thread::onSuspend();
}


void ADCSThread::onResume()
{
   Thread::onResume();
   PC13.on();
}


/*EoF*/
