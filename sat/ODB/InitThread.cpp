
#include "devices.h"
#include "InitThread.h"
#include "Event.h"
#include "Config.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

InitThread::InitThread()
   : Thread( "Initialization", 1, true )
{ ; }


InitThread::~InitThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void InitThread::run( void )
{
   Event *ev;

   _wait();

   delay( 100 );

   LOG << "Waiting for 30mn...";
   delay( 5000 );
   LOG << "Done waiting";

   if( SAT.aDeploy() == ODB::DEPLOYED ) {
      ev = new Event( Event::AD_SUCCESS );
   } else {
      ev = new Event( Event::AD_FAILURE );
   }

   xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
}

/*EoF*/
