#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;

void AttitudeControlThread( Thread *self)
{
    void(self);

    for(;;){
            delay( 2000 );
            (void)printf(" ------- Attitude Control Thread -------\r\n")
    }
}

/*EoF*/
