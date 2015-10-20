
#include "config.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ODB::ODB( const char *name,
          GPIO::Pin& selPin,
          GPIO::Pin& asPin,
          GPIO::Pin& adPin )
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
   PMU0.init();
   VFLASH.init();
   CONF.init();
 //WDB.init();
   RFTX.init();

   _selPin.enable().in().noPull();
   _asPin.enable().in().noPull();
   _adPin.enable().out().off();

   LOG << _name << ": AMSAT-F micro-satellite";

   switch( id() ) {

      case ODB::FR01:
         LOG << _name << ": ON0FR1 (X-CubeSat - Ecole Polytechnique)";
         break;

      case ODB::FR05:
         LOG << _name << ": ON0FR5 (SpaceCube - Mines ParisTech)";
         break;

      default:
         ;
   }

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
      LOG << "Antenna deployed";
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

   if( aState() == ODB::DEPLOYED )
      LOG << "Antenna deployed";
   else
      LOG << "Giving up on antenna deployment";

   return st;
}


/*EoF*/
