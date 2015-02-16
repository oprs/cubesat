
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
   uint8_t rdid[ 4 ] = { 0x9f, 0xff, 0xff, 0xff };
   uint8_t rems[ 6 ] = { 0x90, 0xff, 0xff, 0x00, 0xff, 0xff };
   uint8_t rsr1[ 2 ] = { 0x05, 0xff };
   uint8_t rsr2[ 2 ] = { 0x35, 0xff };

   uint8_t dst[ 8 ];

   SPI3.enable();
   delay( 50 );
   UART6.write( "enabling chip\r\n", 15 );

   for( ;; ) {
      PD12.toggle();
      PC10.toggle();

      /* RDID */

      PA7.off();
      SPI3.xfer( rdid, dst, 4, false );
      PA7.on();
      hexdump( dst, 4 );

      /* REMS */

      PA7.off();
      SPI3.xfer( rems, dst, 6, false );
      PA7.on();
      hexdump( dst, 6 );

      /* RDSR-1 */

      PA7.off();
      SPI3.xfer( rsr1, dst, 2, false );
      PA7.on();
      hexdump( dst, 2 );

      /* RDSR-2 */

      PA7.off();
      SPI3.xfer( rsr2, dst, 2, false );
      PA7.on();
      hexdump( dst, 2 );

      delay( 3000 );
   }
}


int main( void )
{
   UART6.enable();

   GPIOA.enable();
   PA7.out();

   GPIOD.enable();
   PD12.out();
   PD13.out();
   PD14.out();
   PD15.out();
   PD13.on();

   createThread( "Thread 1", thread1 );
   run();

   PD14.on();
   for( ;; );
}

/*EoF*/
