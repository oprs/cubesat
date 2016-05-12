
#include "T1200Thread.h"
#include "Modem1200.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"
#include "Baseband.h"

#include <ctime>

using namespace qb50;

extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

T1200Thread::T1200Thread()
   : Thread( "T1200", 1, SUSPENDED, 512 )
{ ; }


T1200Thread::~T1200Thread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void T1200Thread::onSuspend( void )
{
   M12K.disable();
   WOD.disable();
   Thread::onSuspend();
}


void T1200Thread::onResume( void )
{
   Thread::onResume();
   WOD.enable();
   M12K.enable();

   delay( 500 );
}


void T1200Thread::run( void )
{
   uint8_t *x = new uint8_t[ 256 ];

   WodStore::WEH hdr;

   for( ;; ) {

      _wait();

      (void)WOD.read( &hdr, x );

      if( hdr.type == WodStore::NONE ) {

         Event *ev = new Event( Event::WOD_EMPTY );
         xQueueSendToBack( evQueue, &ev, portMAX_DELAY );

         delay( 500 );

      } else {

         kprintf(
            "WOD HEADER - type: %d, len: %d, prev: 0x%08x\r\n",
            hdr.type, hdr.len, hdr.prev
         );

         M12K.send( &hdr, x );

         delay( 600 );

      }
   }

   delete[] x;
}


/*EoF*/
