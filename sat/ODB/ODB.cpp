
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
{ ; }


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
   RTC.init();
   BKP.init();
   DMA1.init();
 //DMA2.init();
   GPIOA.init();
   GPIOB.init();
   GPIOC.init();
   UART1.init();
   UART2.init();
   UART3.init();
   UART6.init();
 //SPI1.init();
 //SPI2.init();
   SPI3.init();
   ADC1.init();
   ADC2.init();
   ADC3.init();
   ADC4.init();
   VFLASH.init();
 //WDB.init();
   RFTX.init();

   _selPin.enable().in().noPull();
   _asPin.enable().in().noPull();
   _adPin.enable().out().off();

   LOG << _name << ": AMSAT-F micro-satellite";

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
   ODB::AntState st;

   if( aState() == ODB::DEPLOYED ) {
      LOG << "Antenna already deployed";
      return ODB::DEPLOYED;
   }

   _adPin.on();

   for( int i = 0 ; i < 3 ; ++i )
   {
      LOG << "Trying to deploy antenna (" << ( i + 1 ) << "/3)...";
      delay( 4999 );

      st = aState();
      if( st == ODB::DEPLOYED )
         break;
   }

   _adPin.off();

   if( st == ODB::DEPLOYED )
      LOG << "Antenna deployed";
   else
      LOG << "Giving up on antenna deployment";

   return st;
}


/*EoF*/
