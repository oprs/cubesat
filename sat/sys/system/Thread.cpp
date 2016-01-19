
#include <FreeRTOS.h>
#include <task.h>
#include <stddef.h>

#include "system/Thread.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Thread::Thread( const char *name, int prio, bool suspended )
   : _suspended( suspended )
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


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

void Thread::suspend( void )
{
   _suspended = true;
}


void Thread::resume( void )
{
   if( _suspended ) {
      _suspended = false;
      (void)xTaskNotifyGive( (TaskHandle_t)handle );
   }
}

/* handlers */

void Thread::onInit( void )
{ ; }


void Thread::onExit( void )
{ ; }


void Thread::onSuspend( void )
{
   kprintf( "[%s] suspended\r\n", name );
}


void Thread::onResume( void )
{
   kprintf( "[%s] resuming\r\n", name );
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void Thread::_wait( void )
{
   while( _suspended ) {
      onSuspend();
      ::ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
      onResume();
   }
}

/*EoF*/
