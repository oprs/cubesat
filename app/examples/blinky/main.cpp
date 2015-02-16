
#include "qb50.h"

using namespace qb50;

/*
 * LEDS:
 *
 * 12: green
 * 13: orange
 * 14: red
 * 15: blue
 */

void thread1( Thread *self )
{
   for( ;; ) {
      PD12.toggle();
      PC10.toggle();
      delay( 500 );
   }
}

void thread2( Thread *self )
{
   for( ;; ) {
      PD15.toggle();
      UART6.write( "-\r\n", 3 );
      hexdump( 0x0, 384 );
      delay( 5000 );
   }
}

void thread3( Thread *self )
{
   char x[16];

   UART6.enable();
   for( ;; ) {
      UART6.read( x, 1 );
      PC12.toggle();
      UART6.write( x, 1 );
   }
}

int main( void )
{
   GPIOC.enable();
   PC9.in();
   PC10.out();

   GPIOD.enable();
   PD12.out();
   PD13.out();
   PD14.out();
   PD15.out();
   PD13.on();

   createThread( "Thread 1", thread1 );
   createThread( "Thread 2", thread2 );
   createThread( "Thread 3", thread3 );
   run();

   PD14.on();
   for( ;; );
}

/*EoF*/
