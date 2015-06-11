
#include <stdio.h>
#include "system/qb50.h"
#include "../XTRUITES/textualInterface.h"

using namespace qb50;


void ADCSThread( Thread *self )
{
	(void)self; /* prevent gcc from complaining about self being unused */

	for( ;; ) {
		delay( 2000 );
		(void)cpprintf( "--------[ ADCS ]--------\r\n" );
	}
}

/*EoF*/
