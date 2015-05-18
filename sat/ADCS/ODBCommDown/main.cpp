#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;

void ODBCommDownThread( Thread *self)
{
    (void)self;

    for(;;){
            delay( 2000 );
            (void)printf(" ------- ODB Communication (DOWN)  Thread -------\r\n");
    }
}

/*EoF*/
