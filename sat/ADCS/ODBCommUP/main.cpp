
#include "config.h"
#include "common/State.h"

using namespace qb50;

void ODBCommUpThread( Thread *self)
{
    (void)self;

    for(;;){
            delay( 2000 );
            LOG << "------- ODB Communication (UP)  Thread -------";
    }
}

/*EoF*/

