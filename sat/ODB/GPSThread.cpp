
#include "GPSThread.h"
#include "devices.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPSThread::GPSThread()
   : Thread( "GPS", 1, SUSPENDED )
{ ; }


GPSThread::~GPSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void GPSThread::run( void )
{
	uint8_t *x = new uint8_t[ 128 ];
	size_t n;

	kprintf( "GPSThread starting...\r\n" );
	UART3.enable();

	PC3.out().off(); /* ON_OFF_GPS */

	for( ;; ) {
		_wait();
		n = UART3.readLine( x, 128 );
		(void)UART6.write( x, n );
		(void)UART6.write( "\r\n", 2 );
	}

	delete[] x;
}

/*EoF*/
