
#include <stddef.h>

#include "system/Thread.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Thread::Thread( const char *name, ThreadWorker worker )
{
   this->name       = name == NULL ? "(generic thread)" : name;
   this->worker     = worker;
   this->priority   = 1;
   this->stackDepth = 1024;
}

Thread::~Thread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //


/*EoF*/
