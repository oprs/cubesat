
#include "TelemThread.h"
#include "Modem9600.h"
#include "Modem1200.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;

extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TelemThread::TelemThread()
   : Thread( "Telem", 1, SUSPENDED, 512 )
{
   _modem = &M1K2;
   _x     = new uint8_t[ 256 ];
}


TelemThread::~TelemThread()
{
   delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void TelemThread::onSuspend( void )
{
   _modem->disable();
   WOD.disable();
   Thread::onSuspend();
}


void TelemThread::onResume( void )
{
   Thread::onResume();
   WOD.enable();

   if( CONF.getParam( Config::PARAM_MODEM ) == 1 ) {
      _modem = &M1K2;
   } else {
      _modem = &M9K6;
   }

   _modem->enable();
}


void TelemThread::run( void )
{
   WodStore::WEH hdr;

   for( ;; ) {

      _wait();

#if 0
   (void)WOD.peek( &hdr, _x ); // XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX ! XXX !
#else
   (void)WOD.read( &hdr, _x );
#endif

    //if( hdr.type == WodStore::NONE ) {
      if(( hdr.type == WodStore::NONE ) || ( hdr.prev == 0xffffffff )) {

         Event *ev = new Event( Event::WOD_EMPTY );
         xQueueSendToBack( evQueue, &ev, portMAX_DELAY );

         delay( 100 );

      } else {

         kprintf(
            "WOD HEADER - type: %d, len: %d, prev: 0x%08x\r\n",
            hdr.type, hdr.len, hdr.prev
         );

         _modem->send( &hdr, _x, -1 );

      }
   }
}

/*EoF*/
