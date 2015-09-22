
#include "system/qb50.h"
#include "CMD/FormParser.h"

using namespace std;
using namespace qb50;


#define LED1 PC5
#define LED2 PB0
#define LED3 PB1
#define LED4 PA1

#define _QB50_NMODES  13
#define _QB50_NTHREADS 6


QueueHandle_t cmdQueue;


extern void CMDThread   ( Thread *self );
extern void CWThread    ( Thread *self );
extern void GPSThread   ( Thread *self );
extern void ADCSThread  ( Thread *self );
extern void PMUThread   ( Thread *self );
extern void FiPEXThread ( Thread *self );
extern void WODEXThread ( Thread *self );


static unsigned MT[ _QB50_NMODES ] = {

         /*     +------------ CW
                | +---------- GPS
                | | +-------- ADCS
                | | | +------ Power
                | | | | +---- FiPEX
                | | | | | +-- WODEX
                | | | | | |                            */
   0x00, /* 0 0 0 0 0 0 0 0 - Standby                  */
   0x00, /* 0 0 0 0 0 0 0 0 - Charge batteries         */
   0x00, /* 0 0 0 0 0 0 0 0 - Relais FM                */
   0x00, /* 0 0 0 0 0 0 0 0 - Transmission Telemesures */
   0x00, /* 0 0 0 0 0 0 0 0 - Experience               */
   0x00, /* 0 0 0 0 0 0 0 0 - WOD                      */
   0x00, /* 0 0 0 0 0 0 0 0 - Controle d'attitude      */
   0x00, /* 0 0 0 0 0 0 0 0 - Mesure d'attitude        */
   0x00, /* 0 0 0 0 0 0 0 0 - CW                       */
   0x00, /* 0 0 0 0 0 0 0 0 - Lecture GPS              */
   0x00, /* 0 0 0 0 0 0 0 0 - Initialisation           */
   0x00, /* 0 0 0 0 0 0 0 0 - Test controle d'attitude */
   0x00, /* 0 0 0 0 0 0 0 0 - Test mesure d'attitude   */

};


static Thread *tv[ _QB50_NTHREADS ];


void control( Thread *self )
{
   CForm cform;

   LOG << "[MODE_INIT]" << std::flush;

   SAT.enable();

   //MEM0.enable();
   //MEM1.enable();
   LOG << "Waiting for 30mn..." << std::flush;
   delay( 5000 );
   LOG << "Done waiting" << std::flush;
   //MEM1.disable();
   //MEM0.disable();

   SAT.aDeploy();

   RFTX.enable();

   (void)self;

   (void)createThread( "CMDThread", CMDThread );

   tv[ 5 ] = createThread( "CWThread",    CWThread    );
   tv[ 4 ] = createThread( "GPSThread",   GPSThread   );
/*
   tv[ 3 ] = createThread( "ADCSThread",  ADCSThread  );
   tv[ 2 ] = createThread( "PMUThread",   PMUThread   );
*/
   tv[ 1 ] = createThread( "FiPEXThread", FiPEXThread );
/*
   tv[ 0 ] = createThread( "WODEXThread", WODEXThread );
*/

   for( ;; ) {
      xQueueReceive( cmdQueue, &cform, portMAX_DELAY );
      if( cform.argc > 0 ) {
         std::cout << "+ C" << cform.argv[0];
         for( int i = 1 ; i < cform.argc ; ++i )
            std::cout << ',' << cform.argv[i];
         std::cout << "\r\n";
      }
   }
}


int main( void )
{
   SAT.init();

#if 0
   PA0.enable().out().on();   /* CS6 - MEM0 */
   PA4.enable().out().on();   /* CS1 - ADC1 */
   PA5.enable().out().on();   /* CS2 - ADC2 */
   PA6.enable().out().on();   /* CS3 - ADC3 */
   PA7.enable().out().on();   /* CS4 - MEM1 */
   PC4.enable().out().on();   /* CS5 - ADC4 */

   UART6.enable();            /* AX.25      */
   UART1.enable();            /* ADCS       */
   UART2.enable();            /* FiPEX      */
   UART3.enable();            /* GPS        */

   MEM0.enable();
   MEM1.enable();
   ADC1.enable();
   ADC2.enable();
   ADC3.enable();
   ADC4.enable();
#endif

   // GPS.enable();

   for( int i = 0 ; i < _QB50_NTHREADS ; ++i )
      tv[i] = (Thread*)0;

   cmdQueue = xQueueCreate( 16, sizeof( CForm ));
   (void)createThread( "Control", control );

   LOG << "Starting FreeRTOS" << std::flush;

   run();
}

/*EoF*/
