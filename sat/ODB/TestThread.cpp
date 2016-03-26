
#include "devices.h"
#include "TestThread.h"
#include "Config.h"
#include "Event.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TestThread::TestThread()
   : Thread( "Test Thread", 1, SUSPENDED, 256 ),
     _mode( ON )
{ ; }


TestThread::~TestThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void TestThread::onSuspend( void )
{
   Thread::onSuspend();
}


void TestThread::onResume( void )
{
   Thread::onResume();
}


void TestThread::run( void )
{
   Event *ev;

   for( ;; ) {

      _wait();

      if( SAT.aState() == ODB::DEPLOYED ) {
         if( _mode == OFF ) {
            _mode = ON;
            ev = new Event( Event::AD_SUCCESS );
            xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
         }
      } else {
         if( _mode == ON ) {
            _mode = OFF;
            ev = new Event( Event::AD_FAILURE );
            xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
         }
      }

      delay( 100 );

   }
}

/*EoF*/
