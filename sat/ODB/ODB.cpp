
#include "devices.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ODB::ODB( const char *name,
          STM32_GPIO::Pin& selPin,
          STM32_GPIO::Pin& asPin,
          STM32_GPIO::Pin& adPin )
   : _name( name ),
     _selPin( selPin ),
     _asPin( asPin ),
     _adPin( adPin )
{
   maI[0] = maI[1] = maI[2] = maI[3] = 0;
   mvV[0] = mvV[1] = mvV[2] = mvV[3] = 0;
   maIRx  = 0;
   maITx  = 0;
   mvBat  = 0;
   dcBat  = 0;
}


ODB::~ODB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

ODB& ODB::init( void )
{
   SYSLOG.init();
   RCC.init();
   PWR.init();
   BKP.init();
   RTC.init();
   DMA1.init();
   GPIOA.init();
   GPIOB.init();
   GPIOC.init();
   UART1.init();
   UART2.init();
   UART3.init();
   UART6.init();
   SPI3.init();
   ADC1.init();
   ADC2.init();
   ADC3.init();
   ADC4.init();
   VFLASH.init();
 //WDB.init();
   RFTX.init();

   _selPin.in().noPull();
   _asPin.in().noPull();
   _adPin.out().off();

   kprintf( "%s: AMSAT-F micro-satellite\r\n", _name );

   return *this;
}


ODB::SatSel ODB::id( void )
{
   return
      _selPin.read() ? ODB::FR01 : ODB::FR05;
}


ODB::AntState ODB::aState( void )
{
   return
      _asPin.read() ? ODB::RETRACTED : ODB::DEPLOYED;
}


ODB::AntState ODB::aDeploy( void )
{
   ODB::AntState st = ODB::RETRACTED;

   if( aState() == ODB::DEPLOYED ) {
      return ODB::DEPLOYED;
   }

   _adPin.on();

   for( int i = 0 ; i < 3 ; ++i )
   {
      kprintf( "Trying to deploy antenna (%d/3)...\r\n", ( i + 1 ));
      delay( 4999 );

      st = aState();
      if( st == ODB::DEPLOYED )
         break;
   }

   _adPin.off();

   if( st == ODB::DEPLOYED )
      kprintf( "Antenna deployed\r\n" );
   else
      kprintf( "Giving up on antenna deployment\r\n" );

   return st;
}

/*EoF*/
