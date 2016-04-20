
#include "T9600Thread.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"
#include "AX25/AX25TX.h"

using namespace qb50;

extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

T9600Thread::T9600Thread()
   : Thread( "T9600", 1, SUSPENDED, 512 )
{
   _x = new uint8_t[ 256 ];
}


T9600Thread::~T9600Thread()
{
   delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void T9600Thread::onSuspend( void )
{
   AX25.disable();
   WOD.disable();
   Thread::onSuspend();
}


void T9600Thread::onResume( void )
{
   Thread::onResume();
   WOD.enable();
   AX25.enable();
}


void T9600Thread::run( void )
{
   WodStore::WEH hdr;

   for( ;; ) {

      _wait();

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
         AX25.sendUIH( _x, hdr.len - sizeof( WodStore::WEH ));
         (void)WOD.read( &hdr, _x ); // XXX wow wow wow...

         delay( 500 );

      }
   }
}

/*EoF*/
