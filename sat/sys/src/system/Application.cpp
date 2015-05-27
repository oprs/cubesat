
#include <FreeRTOS.h>
#include <task.h>

#include "system/Application.h"


#ifdef DEBUG
 #ifdef __cplusplus
  extern "C" {
 #endif

 void vApplicationTickHook( void );
 void vApplicationIdleHook( void );
 void vApplicationMallocFailedHook( void );
 void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

 #ifdef __cplusplus
  }
 #endif

 void vApplicationTickHook( void )
 { ; }

 void vApplicationIdleHook( void )
 { ; }

 void vApplicationMallocFailedHook( void )
 { for( ;; ); }

 void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
 {
 	(void)pxTask;
 	(void)pcTaskName;

 	for( ;; );
 }
#endif /*DEBUG*/


namespace qb50 {


static void trampoline( void *x )
{
	Thread *thread = (Thread*)x;
	thread->worker( thread );
	vTaskDelete( NULL );
}


Thread *createThread( const char *name, ThreadWorker worker )
{
	Thread *thread = new Thread( name, worker );
	registerThread( thread );

	return thread;
}


void registerThread( Thread *thread )
{
	int rv = xTaskCreate(
		trampoline,
		thread->name,
		thread->stackDepth,
		thread,
		thread->priority,
		&thread->handle
	);

	if( rv != pdTRUE )
		{ throw 42; /* XXX */ }
}


void run( void )
{ ::vTaskStartScheduler(); }


void delay( unsigned ms )
{
	if( ms > portMAX_DELAY )
		ms = portMAX_DELAY;

	::vTaskDelay( (const TickType_t)ms / portTICK_RATE_MS );
}


unsigned ticks( void )
{
   unsigned t = (unsigned)::xTaskGetTickCount();
   return( t / portTICK_RATE_MS );
}


} /* qb50 */

/*EoF*/
