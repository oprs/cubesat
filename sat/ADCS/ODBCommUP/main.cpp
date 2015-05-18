#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;

void ODBCommUpThread( Thread *self)
{
    (void)self;

    for(;;){
            delay( 2000 );
            (void)printf(" ------- ODB Communication (UP)  Thread -------\r\n");
    }
}

/*EoF*/

