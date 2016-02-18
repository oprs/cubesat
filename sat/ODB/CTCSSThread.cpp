
#include "CTCSSThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CTCSSThread::CTCSSThread()
   : Thread( "CTCSS", 1, SUSPENDED )
{ ; }


CTCSSThread::~CTCSSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CTCSSThread::run( void )
{
   for( ;; ) {
      _wait();
      delay( 1000 );
   }
}

/*EoF*/
