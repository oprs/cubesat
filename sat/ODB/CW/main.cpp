
#include <stdio.h>
#include "Morse.h"

using namespace qb50;


void CWThread( Thread *self )
{
   (void)self; /* prevent gcc from complaining about self being unused */

   Morse cw( PB1 );

   for( ;; ) {
      cw.write( "ON0FR1" );
      delay( 30 * 60 * 1000 );
      (void)printf( "--------[ Morse/CW ]--------\r\n" );
   }
}

/*EoF*/
