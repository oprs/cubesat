
#include "system/qb50.h"
#include "CTRL/ControlThread.h"

using namespace qb50;


#define LED1 PC5
#define LED2 PB0
#define LED3 PB1
#define LED4 PA1


QueueHandle_t evQueue;


int main( void )
{
   SAT.init();

#if 0
   UART6.enable();            /* AX.25      */
   UART1.enable();            /* ADCS       */
   UART2.enable();            /* FiPEX      */
   UART3.enable();            /* GPS        */
#endif

   LOG << "Starting RTOS" << std::flush;

   Thread *ctrl = registerThread( new ControlThread() );
   ctrl->resume();

   run();
}

/*EoF*/
