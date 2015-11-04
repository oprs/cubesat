
#include "system/qb50.h"
#include "ControlThread.h"

using namespace qb50;


#define LED1 PC5
#define LED2 PB0
#define LED3 PB1
#define LED4 PA1


int main( void )
{
#if 0
   UART6.enable();            /* AX.25      */
   UART1.enable();            /* ADCS       */
   UART2.enable();            /* FiPEX      */
   UART3.enable();            /* GPS        */
#endif
   (void)registerThread( new ControlThread() );
   run();
}

// PWR_BackupAccessCmd
/*EoF*/
