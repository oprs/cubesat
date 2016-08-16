
#include "config.h"
#include "MainThread.h"

using namespace qb50;

extern void AttitudeControlThread           ( Thread *self );  //Thread for Attitude Control
extern void AttitudeDeterThread             ( Thread *self );  //Thread for Attitude Determination
extern void ODBCommUpThread                 ( Thread *self );  //Thread for Communication with ODB (Sending Data)
extern void ODBCommDownThread               ( Thread *self );  //Thread for Communication with ODB (Receiving Data)
extern void TestThreads                     ( Thread *self );  //Thread for testing purposes only

static void initDevices( void );


void CoilThread( Thread *self )
{
   (void)self;

   for( ;; ) {

      F1.toggle();
      R1.toggle();
      F2.toggle();
      R2.toggle();
      F3.toggle();
      R3.toggle();

      delay( 5 * 1000 );
   }
}


//Principal Thread for ADCS
void Main_Thread( Thread *self )
{
   (void)self;

   initDevices();

   GPIOA.enable();
   GPIOB.enable();
   GPIOC.enable();

   PB15.out().off();

/*
   R1.out().off();
   R2.out().off();
   R3.out().off();
*/
   F1.out().off();
   F2.out().off();
   F3.out().off();

/*
   R1 - PB13 - TIM1_CH1N
   R2 - PB11 - TIM2_CH4
 */

   R1.out().alt( STM32_GPIO::TIM1 ); /* PB13 */
   R2.out().alt( STM32_GPIO::TIM2 ); /* PB11 */
//   R3.out().alt( STM32_GPIO::TIM8 ); /* PA5  */
   R3.out().on();

   UART6.enable();
   SYSLOG.enable();
   BKP.enable( true );

#if 0
   createThread( "Coil Thread", CoilThread );

#if 0
   createThread( "Thread 1", testThread1 );
#else
//   createThread( "ADC Test Thread", TestThreads);
   //createThread( "ODB Comm Up Thread", ODBCommUpThread);
//   createThread( "ODB Comm Down Thread", ODBCommDownThread);
   //createThread( "Attitude Determination Thread", AttitudeDeterThread);
   //createThread( "Attitude Control Thread", AttitudeControlThread);
#endif

   Gyro::vec3d v;

   Timer tm;

    for(;;){
          //tm.every( 2000 );
            delay( 2000 );
            kprintf( "------- Main Thread -------\r\n" );
            switch (Current_state.LCR)
            {
                case PING:
                    kprintf( "------- ODB is pinging us -------\r\n" );
                    break;
                case MODE_ATT_DET:
                    kprintf( "------- Attitude determination mode on -------\r\n" );
                    break;
                case MODE_ATT_CON:
                    kprintf( "------- Attitude Control Mode on -------\r\n" );
                    break;
                case ASK_ATT:
                    kprintf( "------- ODB asks for attitude -------\r\n" );
                    break;
                case ASK_MAG_RAW:
                    kprintf( "------- ODB asks for raw mag data -------\r\n" );
                    break;
                case ASK_SUN_RAW:
                    kprintf( "------- ODB asks for sun data -------\r\n" );
                    for (int i = 0; i < 5; i++) {
                        kprintf( "SUN Sensor 1: %d\r\n", Current_state.TADC.adc_temp[i] );
                     }
                    break;
                case STOP:
                    kprintf( "------- ODB asks to stop ADCS -------\r\n" );
                    break;
                default:
                    kprintf( "------- ODB hasn't told us anything :( -------\r\n" );
            }

      GYR0.omega( v );
      kprintf( "GYR0: [ %02f %02f %02f ]\r\n", v.xr, v.yr, v.zr );

    }
#endif
}


void initDevices( void )
{
   SYSLOG.init();
      RCC.init();
      PWR.init();
      BKP.init();
    GPIOA.init().enable();
    GPIOB.init().enable();
    GPIOC.init().enable();
    UART1.init();
    UART6.init();
     SPI3.init();
     ADC1.init();
   FLASH0.init();
     GYR0.init();
     MAG0.init();
}


int main( void )
{
#if 0
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
#endif

   /* initialize devices */

   initDevices();

   PB15.out().on();

/*
   R1.out().off();
   R2.out().off();
   R3.out().off();
*/

   R1.out().off();
   R2.out().off();
   R3.out().off();
   F1.out().off();
   F2.out().off();
   F3.out().off();

   UART6.enable();
   SYSLOG.enable();
   BKP.enable( true );

   /* create worker threads */

#if 0
PC8.out().on();  // XXX disable LSM303D
PC9.out().on();  // XXX disable LSM303D
PA15.out().on(); // XXX disable flash
#endif

   (void)registerThread( new MainThread() );
 //createThread( "Coil Thread", CoilThread );

   run();

}

/*EoF*/
