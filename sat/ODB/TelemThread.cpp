
#include "TelemThread.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

TelemThread::TelemThread()
   : Thread( "Telem", 1, true )
{ ; }


TelemThread::~TelemThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void TelemThread::run( void )
{
   for( ;; ) {
      _wait();
      delay( 1000 );
   }
}

/*EoF*/
