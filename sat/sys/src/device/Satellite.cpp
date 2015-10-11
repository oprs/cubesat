
#include "system/qb50.h"

#undef RCC
#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef UART4
#undef UART5
#undef DMA1
#undef DMA2
#undef SPI1
#undef SPI2
#undef SPI3
#undef ADC1
#undef ADC2
#undef ADC3
#undef ADC4

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Satellite::Satellite( const char *name,
                      GPIOPin& selPin,
                      GPIOPin& asPin,
                      GPIOPin& adPin )
   : Device( name ),
     _selPin( selPin ),
     _asPin( asPin ),
     _adPin( adPin )
{ ; }


Satellite::~Satellite()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Satellite& Satellite::init( void )
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
 //WODEX.init();
   RFTX.init();

   _selPin.enable().in().noPull();
   _asPin.enable().in().noPull();
   _adPin.enable().out().off();

   LOG << _name << ": AMSAT-F micro-satellite";

   switch( id() ) {

      case Satellite::FR01:
         LOG << _name << ": ON0FR1 (X-CubeSat - Ecole Polytechnique)";
         break;

      case Satellite::FR05:
         LOG << _name << ": ON0FR5 (SpaceCube - Mines ParisTech)";
         break;

      default:
         ;
   }

   return *this;
}


Satellite& Satellite::enable( bool silent )
{
   SYSLOG.enable( silent );
   return *this;
}


Satellite& Satellite::disable( bool silent )
{
   (void)silent;
/*
   _selPin.disable();
   _asPin.disable();
   _adPin.disable();
*/

   return *this;
}


Satellite::SatSel Satellite::id( void )
{
   return
      _selPin.read() ? Satellite::FR01 : Satellite::FR05;
}


Satellite::AntState Satellite::aState( void )
{
   return
      _asPin.read() ? Satellite::RETRACTED : Satellite::DEPLOYED;
}


Satellite::AntState Satellite::aDeploy( void )
{
   Satellite::AntState st;

   if( aState() == Satellite::DEPLOYED ) {
      LOG << "Antenna deployed";
      return Satellite::DEPLOYED;
   }

   _adPin.on();

   for( int i = 0 ; i < 3 ; ++i )
   {
      LOG << "Trying to deploy antenna (" << ( i + 1 ) << "/3)...";
      delay( 4999 );

      st = aState();
      if( st == Satellite::DEPLOYED )
         break;
   }

   _adPin.off();

   if( aState() == Satellite::DEPLOYED )
      LOG << "Antenna deployed";
   else
      LOG << "Giving up on antenna deployment";

   return st;
}


/*EoF*/
