
#include "T1200Thread.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"
#include "Baseband.h"

#include <ctime>

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
//   PC3.off();
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
//   PC3.on();

   delay( 500 );
}


void T1200Thread::run( void )
{
   uint8_t *x = new uint8_t[ 256 ];
   char stime[ 32 ];
   struct tm stm;

   unsigned len, i, n;

   WodStore::WEH hdr;

PC3.on();
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

         (void)gmtime_r( (const time_t*)&hdr.time, &stm );
         n = strftime( stime, 32, "!%Y%m%d@%H%M%S ", &stm );

         for( i = 0 ; i < n ; ++i ) {
            _wrb( stime[ i ]);
         }

         len = hdr.len - sizeof( WodStore::WEH );

         for( i = 0 ; i < len ; ++i ) {
            _wrb( hexv[ x[ i ] >> 4    ]);
            _wrb( hexv[ x[ i ]  & 0x0f ]);
         }

         _wrb( 0x0d );
         _wrb( 0x0d );
         _wrb( 0x0d );
         _wrb( 0x0a );

         delay( 600 );
      }
   }

   delete[] x;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void T1200Thread::_wrb( const uint8_t tx )
{
   uint8_t rx;
   int i;

   for( i = 0 ; i < 5 ; ++i ) {
      if( tx == 0x0a ) {
         /* 0x0a is not echoed back by the PIC, disable read-back */
         if( UART3.write( tx, 25 ) > 0 ) {
            break;
         }
      } else {
         if( UART3.write( tx, rx, 25 ) > 0 ) {
            break;
         }
      }

    //delay( 100 );
   }

   if( i == 5 ) {
      kprintf( RED( "%s: byte lost: 0x%02x" ) "\r\n", name, tx );
   }
}

/*EoF*/
