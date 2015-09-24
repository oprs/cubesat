
#include "system/qb50.h"

#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef UART4
#undef UART5
#undef DMA1
#undef DMA2
#undef SPI1
#undef SPI2
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
   AHB1.init();
   APB1.init();
   APB2.init();
   DMA1.init();
   DMA2.init();
   GPIOA.init();
   GPIOB.init();
   GPIOC.init();
   UART1.init();
   UART2.init();
   UART3.init();
   UART6.init().enable();
   SPI1.init();
   SPI2.init();
   ADC1.init();
   ADC2.init();
   ADC3.init();
   ADC4.init();
   MEM0.init();
   MEM1.init();
   RFTX.init();

   _selPin.enable().in().noPull();
   _asPin.enable().in().noPull();
   _adPin.enable().out().off();

   LOG << _name << ": AMSAT-F micro-satellite" << std::flush;

   switch( id() ) {

      case Satellite::FR01:
         LOG << _name << ": ONFR01 (X-CubeSat - Ecole Polytechnique)" << std::flush;
         break;

      case Satellite::FR05:
         LOG << _name << ": ONFR05 (SpaceCube - Mines ParisTech)" << std::flush;
         break;

      default:
         ;
   }

   return *this;
}


Satellite& Satellite::enable( void )
{
/*
   switch( id() ) {

      case Satellite::FR01:
         LOG << _name << ": ONFR01 (X-CubeSat - Ecole Polytechnique)" << std::flush;
         break;

      case Satellite::FR05:
         LOG << _name << ": ONFR05 (SpaceCube - Mines ParisTech)" << std::flush;
         break;

      default:
         ;
   }
*/

   return *this;
}


Satellite& Satellite::disable( void )
{
   _selPin.disable();
   _asPin.disable();
   _adPin.disable();

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
      LOG << "Antenna deployed" << std::flush;
      return Satellite::DEPLOYED;
   }

   _adPin.on();

   for( int i = 0 ; i < 3 ; ++i )
   {
      LOG << "Trying to deploy antenna (" << ( i + 1 ) << "/3)..." << std::flush;
      delay( 4999 );

      st = aState();
      if( st == Satellite::DEPLOYED )
         break;
   }

   _adPin.off();

   if( aState() == Satellite::DEPLOYED )
      LOG << "Antenna deployed" << std::flush;
   else
      LOG << "Giving up on antenna deployment" << std::flush;

   return st;
}


/*EoF*/
