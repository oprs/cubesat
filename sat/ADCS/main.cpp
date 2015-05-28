
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

void testThread1( Thread *self )  //Test Thread
{
   int cnt = 0;

   (void)self;

   for( ;; ) {
      (void)printf(" ------- Hello Test  Thread -------\r\n");
      (void)printf( "hello: %p - %d\r\n", self, cnt );
      ++cnt;
      delay( 500 );
   }
}


void testThread2( Thread *self) //Thread to test ADC functionality
{
    (void)self;
    //Enable the GPIO Pins for ADC Functionality
    SUN1.enable();
    SUN2.enable();
    SUN3.enable();
    SUN4.enable();
    SUN5.enable();

    for( ;; ){
            (void)printf(" ------- ADC Test Thread -------\r\n");
            uint16_t temp = 0;
            (void)printf( "[DATA ADC]\r\n" );

            temp = SUN1.getValue_adc();
            Current_state.TADC.adc_temp[0] = temp;

            (void)printf( "SUN Sensor 1: %u\r \n", temp);

            temp = SUN2.getValue_adc();
            Current_state.TADC.adc_temp[0] = temp;

            (void)printf( "SUN Sensor 2: %u\r\n", temp);

            temp = SUN3.getValue_adc();
            Current_state.TADC.adc_temp[0] = temp;

            (void)printf( "SUN Sensor 3: %u\r\n", temp);

            temp = SUN4.getValue_adc();
            Current_state.TADC.adc_temp[0] = temp;

            (void)printf( "SUN Sensor 4: %u\r\n", temp);

            temp = SUN5.getValue_adc();
            Current_state.TADC.adc_temp[0] = temp;

            (void)printf( "SUN Sensor 5: %u\r\n", temp);

            delay(500);
    }

}

int main( void )
{
   /* enable UART1 (debug) */

   UART1.enable();

   /* create worker threads */

   //createThread( "Thread 1", testThread1 );
   createThread( "ADC Test Thread", testThread2);
   //createThread( "ODB Comm Up Thread", ODBCommUpThread);
   //createThread( "ODB Comm Down Thread", ODBCommDownThread);
   //createThread( "Attitude Determination Thread", AttitudeDeterThread);
   //createThread( "Attitude Control Thread", AttitudeControlThread);

   //createThread( "ADC Thread", testThread2);

   run();

   /* never reached */

   for( ;; );
}

/*EoF*/
