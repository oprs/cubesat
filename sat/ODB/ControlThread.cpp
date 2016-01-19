
#include "devices.h"

#include "ControlThread.h"
#include "InitThread.h"
#include "CommandThread.h"
#include "CWThread.h"
#include "GPSThread.h"
#include "PMUThread.h"
#include "FiPEX/FipexThread.h"
#include "WodStore.h"

using namespace qb50;

QueueHandle_t evQueue;


uint32_t ControlThread::_mt[ _QB50_NMODES ] = {
  /* +------------ CTCSSThread
     |+----------- TelemThread
     ||+---------- PMUThread
     |||+--------- FiPEXThread
     ||||+-------- GPSThread
     |||||+------- WODEXThread
     ||||||+------ CWThread
     |||||||+----- InitThread
     |||||||| */
   0b00000001, /* mode INIT  */
   0b00110000 /*0b00110010*/, /* mode CW    */
   0b00000000, /* mode STDBY */
   0b00110100, /* mode WODEX */
   0b01100000, /* mode TELEM */
   0b00110000, /* mode FiPEX */
   0b00101000, /* mode GPS   */
   0b10100000, /* mode FM    */
   0b00100000  /* mode POWER */
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ControlThread::ControlThread()
   : Thread( "Event Manager", 2 )
{
   for( int i = 0 ; i < _QB50_NTHREADS ; ++i )
      _tv[i] = (Thread*)0;

   _ctb = 0x00;

   evQueue = xQueueCreate( 16, sizeof( Event* ));
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

/* <INIT> */

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

PB1.out().on();

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

/* </INIT> */


   /* command thread is always running */

   (void)registerThread( new CommandThread() );


   /* create threads (suspended state) */

   _tv[ 0 ] = registerThread( new InitThread()    );
   _tv[ 1 ] = registerThread( new CWThread()      );
 //_tv[ 2 ] = registerThread( new WODEXThread()   );
   _tv[ 3 ] = registerThread( new GPSThread()     );
   _tv[ 4 ] = registerThread( new FipexThread()   );
   _tv[ 5 ] = registerThread( new PMUThread()     );
 //_tv[ 6 ] = registerThread( new TelemThread()   );
 //_tv[ 7 ] = registerThread( new CTCSSThread()   );

   delay( 100 );

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

      Event::event_t etype = ev->type();
      kprintf( "\033[1mEVENT TYPE #%d - %s\033[0m\r\n", etype, ev->name() );

      switch( etype ) {

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
