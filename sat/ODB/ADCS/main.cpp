
#include <stdio.h>
#include "qb50.h"

using namespace qb50;


void ADCSThread( Thread *self )
{
   (void)self; /* prevent gcc from complaining about self being unused */

   for( ;; ) {
      delay( 2000 );
      (void)printf( "--------[ ADCS ]--------\r\n" );
   }
}

/*EoF*/
