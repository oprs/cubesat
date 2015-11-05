
#include "devices.h"

#include "ControlThread.h"
#include "InitThread.h"
#include "CommandThread.h"
#include "PMUThread.h"
#include "CWThread.h"
#include "WodStore.h"

using namespace qb50;


QueueHandle_t evQueue;


uint32_t ControlThread::_mt[ _QB50_NMODES ] = {
         /* +--------------- CTCSSThread
            | +------------- TelemThread
            | | +----------- PMUThread
            | | | +--------- FiPEXThread
            | | | | +------- GPSThread
            | | | | | +----- CWThread
            | | | | | | +--- CommandThread
            | | | | | | | +- InitThread
            | | | | | | | |          */
   0x03, /* 0 0 0 0 0 0 1 1 - INIT   */
   0x26, /* 0 0 1 0 0 1 1 0 - CW     */
   0x02, /* 0 0 ? 0 0 0 1 0 - STDBY  */
   0x22, /* 0 0 1 0 0 0 1 0 - WODEX  */
   0x62, /* 0 1 1 0 0 0 1 0 - TELEM  */
   0x32, /* 0 0 1 1 0 0 1 0 - FiPEX  */
   0xa2, /* 1 0 1 0 0 0 1 0 - FM     */
   0x22, /* 0 0 1 0 0 0 1 0 - POWER  */
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

   SAT.init();
   WOD.init();

   SYSLOG.enable();
 //RTC.enable();
   BKP.enable( true );
   WOD.enable( true );

   /*
    * Hardware reset ?
    * -> load the default configuration
    */

   if( RCC.isPwrOn() ) {
      LOG << "POWER ON - loading default configuration";
      CONF.clear();
   }

   /* increment the reset counter */

   LOG << "Reset count: " << CONF.reset();

   /* display satellite ID */

   switch( SAT.id() ) {

      case ODB::FR01:
         LOG << "ON0FR1 (X-CubeSat - Ecole Polytechnique)";
         break;

      case ODB::FR05:
         LOG << "ON0FR5 (SpaceCube - Mines ParisTech)";
         break;

      default:
         ;
   }

   /* create threads (suspended state) */

   _tv[ 0 ] = registerThread( new InitThread() );
   _tv[ 1 ] = registerThread( new CommandThread() );
   _tv[ 2 ] = registerThread( new CWThread() );
 //_tv[ 3 ] = registerThread( new GPSThread() );
 //_tv[ 4 ] = registerThread( new FiPEXThread() );
   _tv[ 5 ] = registerThread( new PMUThread() );
 //_tv[ 6 ] = registerThread( new TelemThread() );
 //_tv[ 7 ] = registerThread( new CTCSSThread() );

   delay( 100 );

   /* get the last-known mode */

   Config::mode_t mode = CONF.mode();

   if( mode != Config::STDBY ) {
      if( SAT.aState() != ODB::DEPLOYED ) {
         mode = Config::INIT;
      } else {
         LOG << "Antenna already deployed, resuming previous mode";
      }
   }

   _switchModes( mode );

   // ADCS
   // PC13.enable().out().on();

   for( ;; ) {
      xQueueReceive( evQueue, &ev, portMAX_DELAY );
      if( !ev ) continue;

      Event::event_t etype = ev->type();
      LOG << "EVENT TYPE #" << etype << " - " << ev->name();

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

            if( mode != Config::POWER )
               _switchModes( Config::POWER );

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
      delete ev;
   }
}


void ControlThread::_switchModes( Config::mode_t target )
{
   uint32_t ntb = _ctb ^ _mt[ target ];
   uint32_t tmp = 0x01;

   for( unsigned i = 0 ; i < _QB50_NTHREADS ; ++i ) {
      if(( ntb & tmp ) != 0 ) {
         if(( _ctb & tmp ) != 0 ) {
            _tv[ i ]->suspend();
         } else {
            _tv[ i ]->resume();
         }
         delay( 10 );
      }
      tmp <<= 1;
   }

   LOG << "-------- [ " << Config::modes[ target ] << " ] --------";
}


/*EoF*/
