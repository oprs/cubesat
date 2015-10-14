
#include "config.h"

using namespace qb50;



void ODBCommDownThread( Thread *self)
{
    (void)self;

    Current_state.LCR = STOP;

    for(;;){
            delay( 2000 );
            LOG << "------- ODB Communication (DOWN)  Thread -------";
    }
}

/*EoF*/
