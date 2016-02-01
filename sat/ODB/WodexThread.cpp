
#include "WodexThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

WodexThread::WodexThread()
   : Thread( "Wodex", 1, true )
{ ; }


WodexThread::~WodexThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void WodexThread::run( void )
{
   for( ;; ) {
      _wait();
      delay( 1000 );
   }
}

/*EoF*/
