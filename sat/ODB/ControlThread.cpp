
#include "devices.h"

#include "ControlThread.h"
#include "CommandThread.h"
#include "InitThread.h"
#include "CWThread.h"
#include "WodexThread.h"
#include "GPSThread.h"
#include "FiPEX/FipexThread.h"
#include "PMUThread.h"
#include "TelemThread.h"
#include "CTCSSThread.h"
#include "ADCSThread.h"

#include "Event.h"
#include "WodStore.h"

using namespace qb50;

QueueHandle_t evQueue;


uint32_t ControlThread::_mt[ _QB50_NMODES ] = {
  /* +------------- ADCSThread
     |+------------ CTCSSThread
     ||+----------- TelemThread
     |||+---------- CWThread
     ||||+--------- FipexThread
     |||||+-------- GPSThread
     ||||||+------- WodexThread
     |||||||+------ PMUThread
     ||||||||+----- InitThread
     ||||||||| */
   0b000000001, /* mode INIT  */
   0b000100010, /* mode CW    */
   0b000000000, /* mode STDBY */
   0b000000110, /* mode WODEX */
   0b001000010, /* mode TELEM */
   0b000010010, /* mode FiPEX */
   0b000001010, /* mode GPS   */
   0b010000010, /* mode FM    */
   0b000000010  /* mode POWER */
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ControlThread::ControlThread()
   : Thread( "Event Manager", 2 )
{
   evQueue = xQueueCreate( 16, sizeof( Event* ));

   _tv[ 0 ] = new InitThread();
   _tv[ 1 ] = new PMUThread();
   _tv[ 2 ] = new WodexThread();
   _tv[ 3 ] = new GPSThread();
   _tv[ 4 ] = new FipexThread();
   _tv[ 5 ] = new CWThread();
   _tv[ 6 ] = new TelemThread();
   _tv[ 7 ] = new CTCSSThread();
   _tv[ 8 ] = new ADCSThread();

   _ctb = 0x00;
}


ControlThread::~ControlThread()
{
   vQueueDelete( evQueue );
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void ControlThread::run( void )
{
   Event *ev;

   SAT.init();
   WOD.init();

   GPIOA.enable();
   GPIOB.enable();
   GPIOC.enable();
   UART6.enable().baudRate( 115200 );
   SYSLOG.enable();
 //RTC.enable();
   BKP.enable( true );
   WOD.enable( true );

   /*
    * Hardware reset ?
    * -> load the default configuration
    */

   if( RCC.isPwrOn() ) {
      kprintf( "POWER ON - loading default configuration\r\n" );
      CONF.clear();
   }

   /* increment the reset counter */

   kprintf( "Reset count: %d\r\n", CONF.reset() );

   /* display satellite ID */

   switch( SAT.id() ) {

      case ODB::FR01:
         kprintf( "ON0FR1 (X-CubeSat - Ecole Polytechnique)\r\n" );
         break;

      case ODB::FR05:
         kprintf( "ON0FR5 (SpaceCube - Mines ParisTech)\r\n" );
         break;

      default:
         ;
   }

   /* register worker threads */

   (void)registerThread( new CommandThread() );

   for( int i = 0 ; i < _QB50_NTHREADS ; ++i ) {
      delay( 100 );
      (void)registerThread( _tv[i] );
   }

   /* get the last-known mode */

   Config::mode_t mode = CONF.mode();

   if( mode != Config::STDBY ) {
      if( SAT.aState() != ODB::DEPLOYED ) {
         mode = Config::INIT;
      } else {
         kprintf( "Antenna already deployed, resuming previous mode\r\n" );
      }
   }

   _switchModes( mode );

   // ADCS
   // PC13.enable().out().off();

   for( ;; ) {
      xQueueReceive( evQueue, &ev, portMAX_DELAY );
      if( !ev ) continue;

      kprintf( "\033[1mEVENT TYPE #%d - %s\033[0m\r\n", ev->type, ev->name() );

      switch( ev->type ) {

         case Event::AD_SUCCESS:
         case Event::AD_FAILURE:

            if( mode == Config::INIT )
               _switchModes( Config::CW );

            break;

         case Event::VBAT_HIGH:

            if( mode == Config::POWER )
               _switchModes( Config::WODEX );

            break;

         case Event::VBAT_LOW:

            if( mode != Config::POWER ) {
#if 1
               kprintf( RED( "Ignoring VBAT_LOW" ) "\r\n" );
#else
               _switchModes( Config::POWER );
#endif
            }

            break;

         case Event::FORM:
            break;

         default:
            break;

      }
/*
      if( cform.argc > 0 ) {
         std::cout << "+ C" << cform.argv[0];
         for( int i = 1 ; i < cform.argc ; ++i )
            std::cout << ',' << cform.argv[i];
         std::cout << "\r\n";
      }
*/
      mode = CONF.mode();

      delete ev;
   }
}


void ControlThread::_switchModes( Config::mode_t target )
{
   uint32_t delta = _ctb ^ _mt[ target ];
   uint32_t tmp = 0x01;

   for( unsigned i = 0 ; i < _QB50_NTHREADS ; ++i ) {
      if(( delta & tmp ) != 0 ) {
         if(( _ctb & tmp ) != 0 ) {
            _tv[ i ]->suspend();
         } else {
            _tv[ i ]->resume();
         }
         delay( 10 );
      }
      tmp <<= 1;
   }

   _ctb = _mt[ target ];
   CONF.mode( target );

   kprintf( "\033[7m-------- [ %s ] --------\033[0m\r\n", Config::modes[ target ] );
}


/*EoF*/
