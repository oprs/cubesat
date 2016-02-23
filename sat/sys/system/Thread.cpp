
#include <FreeRTOS.h>
#include <task.h>
#include <stddef.h>

#include "system/Thread.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Thread::Thread( const char *name, int prio, State state, unsigned stackDepth )
   : _state( state )
{
   this->name       = name == NULL ? "(generic thread)" : name;
   this->priority   = prio;
   this->stackDepth = stackDepth;

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
   _state = SUSPENDED;
}


void Thread::resume( void )
{
   if( _state == SUSPENDED ) {
      _state = RUNNING;
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
/*
   unsigned su = _stackHWM();
   kprintf( "[%s] suspended (stack usage: %u/%u words)\r\n", name, su, stackDepth );
*/
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
   while( _state == SUSPENDED) {
      onSuspend();
      ::ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
      onResume();
   }
}


unsigned Thread::_stackHWM( void )
{
   uint32_t hwm = uxTaskGetStackHighWaterMark( handle );
   return( stackDepth - hwm );
}

/*EoF*/
