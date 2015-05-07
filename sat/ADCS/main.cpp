
#ifdef XTRUITES
#include "../XTRUITES/textualInterface.h"
#endif

#include "system/qb50.h"
#include <stdio.h>

using namespace qb50;

extern void AttitudeControlThread           ( Thread *self );  //Thread for Attitude Control
extern void AttitudeDeterThread             ( Thread *self );  //Thread for Attitude Determination
extern void ODBCommUpThread                 ( Thread *self );  //Thread for Communication with ODB (Sending Data)
extern void ODBCommDownThread               ( Thread *self );  //Thread for Communication with ODB (Receiving Data)

void testthread1( Thread *self )  //Test Thread
{
   int cnt = 0;

   (void)self;

   for( ;; ) {
      (void)printf( "hello: %p - %d\r\n", self, cnt );
      ++cnt;
      delay( 500 );
   }
}


void testThread2( Thread *self) //Thread to test ADC functionality
{
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
