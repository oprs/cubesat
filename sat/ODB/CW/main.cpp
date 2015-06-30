
#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;


void CWThread( Thread *self )
{
	(void)self; /* prevent gcc from complaining about self being unused */

	for( ;; ) {
		delay( 3000 );
		(void)printf( "--------[ Morse/CW ]--------\r\n" );
	}
}

/*EoF*/
