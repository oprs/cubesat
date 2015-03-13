
#include "system/qb50.h"

using namespace qb50;


void GPSThread( Thread *self )
{
	uint8_t *x = new uint8_t[ 128 ];
	size_t n;

	(void)self; /* prevent gcc from complaining about self being unused */

	UART3.enable();

	for( ;; ) {
		n = UART3.read( x, 128 );
		UART6.write( x, n );
	}
}

/*EoF*/
