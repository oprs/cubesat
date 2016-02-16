
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
   0b000000001, /* mode INIT   */
   0b000100010, /* mode CW     */
   0b000000110, /* mode WODEX  */
   0b100000010, /* mode AMEAS  */
   0b100000010, /* mode DTMB   */
   0b100000010, /* mode ACTRL  */
   0b000010010, /* mode FIPEX  */
   0b010000010, /* mode FM     */
   0b000000000, /* mode STDBY  */
   0b001000010, /* mode TELEM  */
   0b000001010, /* mode GPS    */
   0b000000010, /* mode (11)   */
   0b000000010, /* mode POWER  */
   0b000000010, /* mode (13)   */
   0b000000010, /* mode (14)   */
   0b000000010  /* mode (15)   */
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

   WDG.enable();
   GPIOA.enable();
   GPIOB.enable();
   GPIOC.enable();
   UART6.enable().baudRate( 115200 );
   SYSLOG.enable();
   RTC.enable();
   BKP.enable( true );
   WOD.enable( true );

   // ADCS off

   PC13.out().off();

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

   /* get the last known mode */

   Config::mode_t mode = CONF.mode();

   if( mode != Config::STDBY ) {
      if( SAT.aState() != ODB::DEPLOYED ) {
         mode = Config::INIT;
      } else {
         kprintf( "Antenna already deployed, resuming previous mode\r\n" );
      }
   }

   _switchModes( mode );

   for( ;; ) {
      xQueueReceive( evQueue, &ev, portMAX_DELAY );
      if( !ev ) continue;

      kprintf( "\033[1mEVENT TYPE #%d - %s\033[0m\r\n", ev->type, ev->name() );

      switch( ev->type ) {

         case Event::AD_SUCCESS:
         case Event::AD_FAILURE:

            if( mode == Config::INIT ) {
               _switchModes( Config::CW );
            }

            break;

         case Event::VBAT_HIGH:

            if( mode == Config::POWER ) {
               _switchModes( Config::WODEX );
            }

            break;

         case Event::VBAT_LOW:

            if( mode != Config::POWER ) {
               _switchModes( Config::POWER );
            }

            break;

         case Event::FORM:

            _handleForm( ev->form );
            break;

         default:
            break;

      }

      mode = CONF.mode();

      delete ev;
   }
}


void ControlThread::_handleForm( Form *fp )
{
   switch( fp->type ) {

      case Form::FORM_TYPE_C:
         _handleCForm( &fp->C );
         break;

      default:
         break;
   }
}


void ControlThread::_handleCForm( CForm *fp )
{
   Config::mode_t mode = CONF.mode();

   switch( fp->argv[0] ) {

      /* C1 - passage en mode CW */

      case 1:

         kprintf( "FORM C1\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_CW_CYCLE_TX, fp->argv[1] );
            if( fp->argc > 2 ) {
               (void)CONF.setParam( Config::PARAM_CW_POWER, fp->argv[2] );
            }
         }

         if( mode != Config::CW ) {
            _switchModes( Config::CW );
         }

         break;

      /* C2 - passage en mode WODEX */

      case 2:

         kprintf( "FORM C2\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_WODEX_CYCLE_TX, fp->argv[1] );
            if( fp->argc > 2 ) {
               (void)CONF.setParam( Config::PARAM_WODEX_POWER, fp->argv[2] );
            }
         }

         if( mode != Config::WODEX ) {
            _switchModes( Config::WODEX );
         }

         break;

      /* C3 - passage en mode mesure d'attitude */

      case 3:

         kprintf( "FORM C3\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_ADCS_CYCLE_MEAS, fp->argv[1] );
         }

         if( mode != Config::AMEAS ) {
            _switchModes( Config::AMEAS );
         }

         break;

      /* C4 - passage en mode détumbling */

      case 4:

         kprintf( "FORM C4\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_ADCS_CYCLE_DTMB, fp->argv[1] );
            if( fp->argc > 2 ) {
               (void)CONF.setParam( Config::PARAM_ADCS_CYCLE_MEAS, fp->argv[2] );
            }
         }

         if( mode != Config::DTMB) {
            _switchModes( Config::DTMB );
         }

         break;

         /* C5 - passage en mode contrôle d'attitude */

      case 5:

         kprintf( "FORM C5\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_ADCS_CYCLE_CTRL, fp->argv[1] );
            if( fp->argc > 2 ) {
               (void)CONF.setParam( Config::PARAM_ADCS_CYCLE_MEAS, fp->argv[2] );
            }
         }

         if( mode != Config::ACTRL ) {
            _switchModes( Config::ACTRL );
         }

         break;

      /* C6 - passage en mode FIPEX */

      case 6:

         kprintf( "FORM C6\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_FIPEX_SCRIPT_N, fp->argv[1] );
         }

         if( mode != Config::FIPEX ) {
            _switchModes( Config::FIPEX );
         }

         break;

      /* C7 - passage en mode relais FM */

      case 7:

         kprintf( "FORM C7\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_FM_CYCLE_ON, fp->argv[1] );
            if( fp->argc > 2 ) {
               (void)CONF.setParam( Config::PARAM_FM_POWER, fp->argv[2] );
            }
         }

         if( mode != Config::FM ) {
            _switchModes( Config::FM );
         }

         break;

      /* C8 - passage en mode standby */

      case 8:

         kprintf( "FORM C8\r\n" );

         if( mode != Config::STDBY ) {
            _switchModes( Config::STDBY );
         }

         break;

      /* C9 - passage en mode télémétrie */

      case 9:

         kprintf( "FORM C9\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_WODEX_POWER, fp->argv[1] );
         }

         if( mode != Config::TELEM ) {
            _switchModes( Config::TELEM );
         }

         break;

      /* C10 - passage en mode GPS */

      case 10:

         kprintf( "FORM C10\r\n" );

         if( fp->argc > 1 ) {
            (void)CONF.setParam( Config::PARAM_GPS_CYCLE_ON, fp->argv[1] );
         }

         if( mode != Config::GPS ) {
            _switchModes( Config::GPS );
         }

         break;

      /* C11 - ping */

      case 11:
         kprintf( "FORM C11\r\n" );
         break;

      /* C12 - arrêt télémétries */

      case 12:

         kprintf( "FORM C12\r\n" );

         if( mode != Config::GPS ) {
            _switchModes( Config::WODEX );
         }

         break;

      /* C13 - effacement données FIPEX (SU) */

      case 13:
         kprintf( "FORM C13\r\n" );
         break;

      /* C14 - mode test mesure d'attitude */

      case 14:
         kprintf( "FORM C14\r\n" );
         break;

      /* C15 - mode test contrôle d'attitude */

      case 15:
         kprintf( "FORM C15\r\n" );
         break;

      default:
         break;

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
