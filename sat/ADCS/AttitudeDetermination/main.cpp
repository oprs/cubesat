#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;

void AttitudeDeterThread( Thread *self)
{
    (void)self;

    for(;;){
            delay( 2000 );
            (void)printf(" ------- Attitude Determination Thread -------\r\n");
    }
}

/*EoF*/
