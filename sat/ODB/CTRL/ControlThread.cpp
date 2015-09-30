
#include "ControlThread.h"
#include "CMD/CommandThread.h"
#include "PMU/PMUThread.h"
#include "CW/CWThread.h"

using namespace qb50;


extern QueueHandle_t evQueue;

uint32_t ControlThread::_mt[ _QB50_NMODES ] = {
         /*     +------------ CW
                | +---------- GPS
                | | +-------- ADCS
                | | | +------ Power
                | | | | +---- FiPEX
                | | | | | +-- WODEX
                | | | | | |             */
   0x00, /* 0 0 0 0 0 0 0 0 - INIT      */
   0x00, /* 0 0 0 0 0 0 0 0 - CW        */
   0x00, /* 0 0 0 0 0 0 0 0 - WODEX     */
   0x00, /* 0 0 0 0 0 0 0 0 - FiPEX     */
   0x00, /* 0 0 0 0 0 0 0 0 - PowerSave */
   0x00, /* 0 0 0 0 0 0 0 0 - FM        */
   0x00, /* 0 0 0 0 0 0 0 0 - StandBy   */
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ControlThread::ControlThread()
   : Thread( "Event Manager", 2 )
{
   for( int i = 0 ; i < _QB50_NTHREADS ; ++i )
      _tv[i] = (Thread*)0;

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
   SAT.enable();

FLASH0.enable();
FLASH1.enable();

uint8_t *x = new uint8_t[256];

//for( int i = 0 ; i < 256 ; ++i ) x[i] = (uint8_t)i;
//FLASH0.pageWrite( 0, x );

for( int i = 0 ; i < 256 ; ++i ) x[i] = 0;
FLASH0.pageRead( 0, x );

LOG << "FLASH0 bytes: " << std::hex << (int)x[0] << ' ' << (int)x[1] << ' ' << (int)x[2] << ' ' << (int)x[3] << " ...";
delete[] x;

   LOG << "Waiting for 30mn...";
   delay( 5000 );
   LOG << "Done waiting";

   SAT.aDeploy();

   _tv[ 0 ] = registerThread( new CommandThread() );
   _tv[ 1 ] = registerThread( new CWThread() );
 //_tv[ 2 ] = registerThread( new GPSThread() );
 //_tv[ 3 ] = registerThread( new FiPEXThread() );
   _tv[ 4 ] = registerThread( new PMUThread() );

   for( ;; ) {
      xQueueReceive( evQueue, &ev, portMAX_DELAY );
      if( ev ) {
         LOG << "EVENT TYPE " << ev->type();
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
}


/*EoF*/
