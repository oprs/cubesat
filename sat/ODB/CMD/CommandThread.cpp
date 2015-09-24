
#include "CommandThread.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CommandThread::CommandThread()
   : Thread( "CommandThread", 1 )
{ ; }


CommandThread::~CommandThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CommandThread::run( void )
{
   LOG << "CommandThread::run()";

   for( ;; ) {
      delay( 10 * 1000 );
      LOG << "yop" << std::flush;
   }
}

/*EoF*/
