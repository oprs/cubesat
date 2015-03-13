
#include "system/qb50.h"
#include <stdio.h>

using namespace qb50;


void thread1( Thread *self )
{
   int cnt = 0;

   (void)self;

   for( ;; ) {
      (void)printf( "hello: %p - %d\r\n", self, cnt );
      ++cnt;
      delay( 500 );
   }
}


int main( void )
{
   /* enable UART2 (debug) */

   UART2.enable();

   /* create worker threads */

   createThread( "Thread 1", thread1 );

   run();

   /* never reached */

   for( ;; );
}

/*EoF*/
