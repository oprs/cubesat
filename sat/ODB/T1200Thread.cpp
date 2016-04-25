
#include "T1200Thread.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"
#include "Baseband.h"

using namespace qb50;

extern QueueHandle_t evQueue;

static const uint8_t hexv[ 16 ] = {
   '0', '1', '2', '3', '4', '5', '6', '7',
   '8' ,'9', 'a', 'b', 'c', 'd', 'e', 'f'
};


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
   PC3.off();
   BB.disable();
   WOD.disable();
   UART3.disable();
   Thread::onSuspend();
}


void T1200Thread::onResume( void )
{
   Thread::onResume();
   UART3.enable();
   WOD.enable();
   BB.enable();
   PC3.on();
}


void T1200Thread::run( void )
{
   uint8_t *x = new uint8_t[ 256 ];
   uint8_t *y = new uint8_t[ 512 ];

   unsigned len, i;

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
/*
         kprintf( "  type: %d\r\n",     hdr.type  );
         kprintf( "   len: %d\r\n",     hdr.len   );
         kprintf( "   seq: %d\r\n",     hdr.seq   );
         kprintf( " ticks: %lu\r\n",    hdr.ticks );
         kprintf( "  prev: 0x%08x\r\n", hdr.prev  );
         kprintf( "   crc: %lu\r\n",    hdr.crc   );
*/

         len = hdr.len - sizeof( WodStore::WEH );

         for( i = 0 ; i < len ; ++i ) {
            y[ 2*i     ] = hexv[ x[ i ] >> 4    ];
            y[ 2*i + 1 ] = hexv[ x[ i ]  & 0x0f ];
         }

         y[ 2*i     ] = 0x0d;
         y[ 2*i + 1 ] = 0x0a;

         UART3.write( y, 2 * len + 2, 500 );

         delay( 500 );
      }

      //delay( 500 );
   }

   delete[] y;
   delete[] x;
}

/*EoF*/
