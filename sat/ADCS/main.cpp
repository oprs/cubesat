
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
extern void TestThreads                     ( Thread *self );  //Thread for testing purposes only

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


/*void testThread2( Thread *self) //Thread to test ADC functionality
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
            Current_state.TADC.adc_temp[0] = SUN1.getValue_adc();

            (void)printf( "SUN Sensor 1: %u\r \n", temp);

            temp = SUN2.getValue_adc();
            Current_state.TADC.adc_temp[1] = SUN2.getValue_adc();

            (void)printf( "SUN Sensor 2: %u\r\n", temp);

            temp = SUN3.getValue_adc();
            Current_state.TADC.adc_temp[2] = SUN3.getValue_adc();

            (void)printf( "SUN Sensor 3: %u\r\n", temp);

            temp = SUN4.getValue_adc();
            Current_state.TADC.adc_temp[3] = SUN4.getValue_adc();

            (void)printf( "SUN Sensor 4: %u\r\n", temp);

            temp = SUN5.getValue_adc();
            Current_state.TADC.adc_temp[4] = SUN5.getValue_adc();

            (void)printf( "SUN Sensor 5: %u\r\n", temp);

            delay(500);
    }

}
*/
int main( void )
{
   /* enable UART1 (debug) */

   UART1.enable();

    //Initialize the state to some standard values
    //For testing purposes only

    //Mag_field calculated
    Current_state.MAGFIE.B_x = 0;
    Current_state.MAGFIE.B_y = 0;
    Current_state.MAGFIE.B_z = 0;

    //Position calculated
    Current_state.POS.pos_x = 10;
    Current_state.POS.pos_y = -20;
    Current_state.POS.pos_z = 15;

    //Sun Vector calculated
    Current_state.SUNVEC.s_x = -0.5;
    Current_state.SUNVEC.s_y = 0.6;
    Current_state.SUNVEC.s_z = -0.7;

   /* create worker threads */

   //createThread( "Thread 1", testThread1 );
   createThread( "ADC Test Thread", TestThreads);
   createThread( "ODB Comm Up Thread", ODBCommUpThread);
   createThread( "ODB Comm Down Thread", ODBCommDownThread);
   createThread( "Attitude Determination Thread", AttitudeDeterThread);
   createThread( "Attitude Control Thread", AttitudeControlThread);

   //createThread( "ADC Thread", testThread2);

   run();

   /* never reached */

   for( ;; );
}

/*EoF*/
