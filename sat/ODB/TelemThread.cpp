
#include "TelemThread.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"
#include "AX25/AX25TX.h"

#include <cstring> // XXX out!

using namespace qb50;

extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TelemThread::TelemThread()
   : Thread( "Telem", 1, SUSPENDED, 512 )
{
   _x = new uint8_t[ 256 ];
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
   AX25.disable();
   WOD.disable();
   Thread::onSuspend();
}


void TelemThread::onResume( void )
{
   Thread::onResume();
   WOD.enable();
   AX25.enable();
}


void TelemThread::run( void )
{
   WodStore::WEH hdr;

   for( ;; ) {

      _wait();

#if 1

      kprintf( "transmit\r\n" );

      AX25.sendUI( (const uint8_t *)"test123 hello", 13 );
      delay( 2000 );

#else
      delay( 2000 );

      (void)WOD.read( &hdr, _x );

      if( hdr.type == WodStore::NONE ) {

         Event *ev = new Event( Event::WOD_EMPTY );
         xQueueSendToBack( evQueue, &ev, portMAX_DELAY );

         delay( 100 );

      } else {

         kprintf( "WOD HEADER:\r\n" );
         kprintf( "  type: %d\r\n",     hdr.type  );
         kprintf( "   len: %d\r\n",     hdr.len   );
         kprintf( "   seq: %d\r\n",     hdr.seq   );
         kprintf( " ticks: %lu\r\n",    hdr.ticks );
         kprintf( "  prev: 0x%08x\r\n", hdr.prev  );
         kprintf( "   crc: %lu\r\n",    hdr.crc   );
         hexdump( _x, hdr.len - sizeof( WodStore::WEH ));
         AX25.sendUIH( _x, hdr.len - sizeof( WodStore::WEH ));
         (void)WOD.read( &hdr, _x );

         delay( 500 );
      }
#endif

   }
}


/*EoF*/
