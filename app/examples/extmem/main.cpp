
#include "qb50.h"

using namespace qb50;

/*
 * LEDS:
 *
 * 12: green   PD12
 * 13: orange  PD13
 * 14: red     PD14
 * 15: blue    PD15
 */

void thread1( Thread *self )
{
   A25Lxxx::RDIDResp rdid;
   A25Lxxx::REMSResp rems;
   A25Lxxx::RDSRResp rdsr;

   uint8_t *buf = new uint8_t[1024];

   dataMem.enable();

   for( ;; ) {
      PD12.toggle();
      //PC10.toggle();
      UART6.write( "---\r\n", 5 );

      dataMem.RDID( &rdid );
      hexdump( &rdid, sizeof( rdid ));

      dataMem.REMS( &rems );
      hexdump( &rems, sizeof( rems ));

      dataMem.RDSR1( &rdsr );
      hexdump( &rdsr, sizeof( rdsr ));

      dataMem.RDSR2( &rdsr );
      hexdump( &rdsr, sizeof( rdsr ));

      dataMem.READ( 0, buf, 256 );
      hexdump( buf, 256 );

      delay( 1000 );
   }

   delete[] buf;
}


int main( void )
{
   UART6.enable();

   GPIOA.enable();
   //PA7.out();

   //GPIOC.enable();
   //PC10.out();

   GPIOD.enable();
   PD12.out();
   PD13.out();
   PD14.out();
   PD15.out();

   PD13.on();

PD14.on();
   createThread( "Thread 1", thread1 );
   run();

   PD14.on();
   for( ;; );
}

/*EoF*/
