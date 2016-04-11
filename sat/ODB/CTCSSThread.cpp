
#include "CTCSSThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CTCSSThread::CTCSSThread()
   : Thread( "CTCSS", 1, SUSPENDED )
{
   _semCTCSS = xSemaphoreCreateBinary();
}


CTCSSThread::~CTCSSThread()
{
   vSemaphoreDelete( _semCTCSS );
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CTCSSThread::onSuspend( void )
{
   PB12.off();
   Thread::onSuspend();
}


void CTCSSThread::onResume( void )
{
   int i, vp;

   Thread::onResume();
   PB12.on();

   vp = xSemaphoreTake( _semCTCSS, 10 / portTICK_RATE_MS );
   for( i = 0 ; i < 10 ; ++i ) {
      if( vp == pdFAIL ) break;
      kprintf( YELLOW( "FLUSHING CTCSS" ) "\r\n" );
      vp = xSemaphoreTake( _semCTCSS, 10 / portTICK_RATE_MS );
   }

   if( i > 2 ) {
      kprintf( RED( "%s: too many pending CTCSS events" ) "\r\n", name );
   }
}


void CTCSSThread::run( void )
{
   int vp;

   PA8  . in()  . noPull(); // DEC_Tone
   PB12 . out() . off();    // ON/OFF_CTCSS

   EXTI.registerHandler( PA8, this, STM32_EXTI::BOTH );

   for( ;; ) {
      _wait();

      vp = xSemaphoreTake( _semCTCSS, 1000 / portTICK_RATE_MS );
      if ( vp == pdPASS ) {
         kprintf( RED( "CTCSS" ) "\r\n" );
      } else {
         kprintf( "waiting for CTCSS...\r\n" );
      }
   }

   // XXX EXTI.removeHandler()
}


//  - - - - - - - - - - - -  //
//  E X T I   H A N D L E R  //
//  - - - - - - - - - - - -  //

void CTCSSThread::handle( STM32_EXTI::EXTIn /* ignored */ )
{
   portBASE_TYPE hpTask = pdFALSE;

   (void)xSemaphoreGiveFromISR( _semCTCSS, &hpTask );

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
}

/*EoF*/
