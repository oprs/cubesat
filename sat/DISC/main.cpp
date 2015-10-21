
#include "system/qb50.h"
#include "MainThread.h"

using namespace qb50;


int main( void )
{
   (void)registerThread( new MainThread() );
   run();
}

/*EoF*/
