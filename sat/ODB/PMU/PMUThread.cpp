
#include "PMUThread.h"
#include "system/Application.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "PMUThread", 1 )
{ ; }


PMUThread::~PMUThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void PMUThread::run( void )
{
   LOG << "PMUThread::run()";

   for( ;; ) {
      delay( 1000 );
   }
}

/*EoF*/
