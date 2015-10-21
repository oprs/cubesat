
#include "config.h"
#include "MainThread.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MainThread::MainThread()
   : Thread( "Main Thread", 2 )
{ ; }


MainThread::~MainThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void MainThread::initDevices( void )
{
   SYSLOG.init();
   RCC.init();
   PWR.init();
   BKP.init();
   DMA1.init();
 //DMA2.init();
   GPIOA.init();
   GPIOB.init();
   GPIOC.init();
   UART6.init();
 //SPI1.init();
 //SPI2.init();
   SPI3.init();
}


void MainThread::run( void )
{
   initDevices();

   SYSLOG.enable();

   LOG << "STM32F4-Discovery board";

   for( ;; ) {
      LOG << "waiting...";
      delay( 5000 );
   }
}


/*EoF*/
