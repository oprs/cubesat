
#include "TelemThread.h"
#include "Event.h"
#include "WodStore.h"
#include "Config.h"
#include "devices.h"

#include <cstring> // XXX out!

using namespace qb50;

extern QueueHandle_t evQueue;

#if 0
//  - - - - - - - - - - - - -  //
//  A X . 2 5   H A N D L E R  //
//  - - - - - - - - - - - - -  //

AX25Handler::AX25Handler( FIFO<bool>& fifo )
   : _fifo( fifo )
{ ; }


AX25Handler::~AX25Handler()
{ ; }


void AX25Handler::handle( EXTI::EXTIn )
{
   bool bit0;
   bool bit1;

   if( !_fifo.isEmpty() ) {
      bit0 = _fifo.pull();
      bit1 = _nrzi.push( bit0 );

      if( bit0 ) {
         LED1.on();
      } else {
         LED1.off();
      }

      if( bit1 ) {
         PC8.on();
      } else {
         PC8.off();
      }
   }
}
#endif

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
   WOD.disable();
   Thread::onSuspend();
}


void TelemThread::onResume( void )
{
   Thread::onResume();
   WOD.enable();
}


void TelemThread::run( void )
{
   WodStore::WEH hdr;

   for( ;; ) {

      _wait();

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
         (void)WOD.read( &hdr, _x );

         delay( 500 );
      }

   }
}


/*EoF*/
