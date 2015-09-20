
#include "system/qb50.h"

using namespace qb50;


void GPSThread( Thread *self )
{
	uint8_t c;

	(void)self;

	LOG << "GPSThread starting..." << std::flush;

	PC3.enable().out().off(); /* ON_OFF_GPS */

	for( ;; ) {
		(void)UART3.read( &c, 1 );
		(void)UART2.write( &c, 1 );
	}
}

/*EoF*/
