
#include "config.h"
#include "MainThread.h"
#include "device/Gyro.h"

using namespace qb50;


static void test( Thread *self )
{
   for( ;; ) {
      LOG << "still alive...";
      delay( 2000 );
   }
}


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
   FLASH0.init();
   FLASH1.init();
   GYR0.init();
 //MAG0.init();
}


void MainThread::run( void )
{
   initDevices();

   UART6.enable().baudRate( 115200 );
   SYSLOG.enable();

   LOG << "STM32F4-Discovery board";

   createThread( "test", test );

   Gyro::vec3d v;

   FLASH0.enable();
   FLASH1.enable();

   GYR0.enable();
 //GYR1.enable();

   PC9.enable().out().on();

   delay( 250 ); // see AN4505, sec 2.4, table 5

   GYR0.calibrate();
 //GYR1.calibrate();

   for( ;; ) {
      GYR0.omega( v );
    //GYR1.omega( v );
      LOG << v.xr << '\t' << v.yr << '\t' << v.zr;
      delay( 1000 );
   }
}


/*EoF*/
