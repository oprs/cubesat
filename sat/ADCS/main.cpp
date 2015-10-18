
#include "config.h"

using namespace qb50;

extern void AttitudeControlThread           ( Thread *self );  //Thread for Attitude Control
extern void AttitudeDeterThread             ( Thread *self );  //Thread for Attitude Determination
extern void ODBCommUpThread                 ( Thread *self );  //Thread for Communication with ODB (Sending Data)
extern void ODBCommDownThread               ( Thread *self );  //Thread for Communication with ODB (Receiving Data)
extern void TestThreads                     ( Thread *self );  //Thread for testing purposes only

static void initDevices( void );


void testThread1( Thread *self )  //Test Thread
{
    int cnt = 0;

    (void)self;

    initDevices();
    SYSLOG.enable();

    for( ;; ) {
        LOG << "test: " << cnt;
/*
        (void)printf(" ------- Hello Test  Thread -------\r\n");
        (void)printf( "hello: %p - %d\r\n", self, cnt );
*/
        ++cnt;
        delay( 500 );
    }
}

//Principal Thread for ADCS
void Main_Thread( Thread *self){

    (void)self;

    initDevices();
    SYSLOG.enable();

#if 0
   createThread( "Thread 1", testThread1 );
#else
   createThread( "ADC Test Thread", TestThreads);
   //createThread( "ODB Comm Up Thread", ODBCommUpThread);
   createThread( "ODB Comm Down Thread", ODBCommDownThread);
   //createThread( "Attitude Determination Thread", AttitudeDeterThread);
   //createThread( "Attitude Control Thread", AttitudeControlThread);
#endif

    for(;;){
            delay( 2000 );
            LOG << "------- Main Thread -------";
            switch (Current_state.LCR)
            {
                case PING:
                    LOG << "------- ODB is pinging us -------";
                    break;
                case MODE_ATT_DET:
                    LOG << "------- Attitude determination mode on -------";
                    break;
                case MODE_ATT_CON:
                    LOG << "------- Attitude Control Mode on -------";
                    break;
                case ASK_ATT:
                    LOG << "------- ODB asks for attitude -------";
                    break;
                case ASK_MAG_RAW:
                    LOG << "------- ODB asks for raw mag data -------";
                    break;
                case ASK_SUN_RAW:
                    LOG << "------- ODB asks for sun data -------";
                    for (int i = 0; i < 5; i++)
                        LOG << "SUN Sensor 1: " << Current_state.TADC.adc_temp[i];
                    break;
                case STOP:
                    LOG << "------- ODB asks to stop ADCS -------";
                    break;
                default:
                    LOG << "------- ODB hasn't told us anything :( -------";
            }
    }
}


void initDevices( void )
{
    SYSLOG.init();
    RCC.init();
    GPIOA.init();
    GPIOB.init();
    GPIOC.init();
    UART1.init();
    ADC1.init();
    FLASH0.init();
}

int main( void )
{
    //Initialize the state to some standard values
    //For testing purposes only

    //Mag_field calculated
    Current_state.MAGFIE.B_x = 0;
    Current_state.MAGFIE.B_y = 0;
    Current_state.MAGFIE.B_z = 0;

    //Position calculated
    Current_state.POS.pos_x =  10;
    Current_state.POS.pos_y = -20;
    Current_state.POS.pos_z =  15;

    //Sun Vector calculated
    Current_state.SUNVEC.s_x = -0.5;
    Current_state.SUNVEC.s_y =  0.6;
    Current_state.SUNVEC.s_z = -0.7;

   /* create worker threads */

   createThread( "Main Thread", Main_Thread);
   run();

   /* never reached */

   for( ;; );
}

/*EoF*/
