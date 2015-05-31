
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

//Principal Thread for ADCS
void Main_Thread( Thread *self){

    (void)self;

    for(;;){
            delay( 2000 );
            (void)printf(" ------- Main Thread -------\r\n");
            switch (Current_state.LCR)
            {
                case PING:
                    (void)printf(" ------- ODB is pinging us -------\r\n");
                    break;
                case MODE_ATT_DET:
                    (void)printf(" ------- Attitude determination mode on -------\r\n");
                    break;
                case MODE_ATT_CON:
                    (void)printf(" ------- Attitude Control Mode on -------\r\n");
                    break;
                case ASK_ATT:
                    (void)printf(" ------- ODB asks for attitude -------\r\n");
                    break;
                case ASK_MAG_RAW:
                    (void)printf(" ------- ODB asks for raw mag data -------\r\n");
                    break;
                case ASK_SUN_RAW:
                    (void)printf(" ------- ODB asks for sun data -------\r\n");
                    for (int i = 0; i < 5; i++)
                        (void)printf( "SUN Sensor 1: %u\r \n", Current_state.TADC.adc_temp[i]);
                    break;
                case STOP:
                    (void)printf(" ------- ODB asks to stop ADCS -------\r\n");
                    break;
                default:
                    (void)printf(" ------- ODB hasn't told us anything :( -------\r\n");
            }
    }
}
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
   //createThread( "ODB Comm Up Thread", ODBCommUpThread);
   createThread( "ODB Comm Down Thread", ODBCommDownThread);
   //createThread( "Attitude Determination Thread", AttitudeDeterThread);
   //createThread( "Attitude Control Thread", AttitudeControlThread);
   createThread( "Main Thread", Main_Thread);

   run();

   /* never reached */

   for( ;; );
}

/*EoF*/
