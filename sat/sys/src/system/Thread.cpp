
#include <FreeRTOS.h>
#include <task.h>
#include <stddef.h>

#include "system/Thread.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Thread::Thread( const char *name, int prio )
{
   this->name       = name == NULL ? "(generic thread)" : name;
   this->priority   = prio;
   this->stackDepth = 2048;

   onInit();
}


Thread::~Thread()
{
   onExit();
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void Thread::suspend( void )
{
   vTaskSuspend( (TaskHandle_t)handle );
   onSuspend();
}


void Thread::resume( void )
{
   onResume();
   vTaskResume( (TaskHandle_t)handle );
}

/* handlers */

void Thread::onInit( void )
{ ; }


void Thread::onExit( void )
{ ; }


void Thread::onSuspend( void )
{
   LOG << "Suspending thread [" << name << ']';
}


void Thread::onResume( void )
{
   LOG << "Resuming thread [" << name << ']';
}

/*EoF*/
