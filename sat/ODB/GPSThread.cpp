
#include "GPSThread.h"
#include "devices.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPSThread::GPSThread()
   : Thread( "GPS", 1, true  )
{ ; }


GPSThread::~GPSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void GPSThread::run( void )
{
	uint8_t c;

	LOG << "GPSThread starting..." << std::flush;

	PC3.out().off(); /* ON_OFF_GPS */

	for( ;; ) {
		(void)UART3.read( &c, 1 );
		(void)UART2.write( &c, 1 );
	}
}

/*EoF*/
