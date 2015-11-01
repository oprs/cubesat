
#include "device/STM32_RCC.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


uint8_t STM32_RCC::pv[ 16 ] = { 0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9 };

//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_RCC::STM32_RCC( const uint32_t iobase, const char *name )
   : _iobase( iobase ), _name( name )
{ ; }


STM32_RCC::~STM32_RCC()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_RCC& STM32_RCC::init( void )
{
   Clocks clk;

   LOG << _name << ": STM32 reset and clock controller";

   clocks( &clk );

   LOG << _name << ": SYSCLK: " << clk.SYSCLKFreq / ( 1000 * 1000 ) << "MHz"
                << ", HCLK: "   << clk.HCLKFreq   / ( 1000 * 1000 ) << "MHz"
                << ", PCLK1: "  << clk.PCLK1Freq  / ( 1000 * 1000 ) << "MHz"
                << ", PCLK2: "  << clk.PCLK2Freq  / ( 1000 * 1000 ) << "MHz";

   return *this;
}


STM32_RCC& STM32_RCC::enable( BusSlave *dev, bool silent )
{
   RCC_TypeDef *RCCx = (RCC_TypeDef*)_iobase;

   switch( dev->bus.id ) {

      case Bus::AHB1: RCCx->AHB1ENR |= dev->periph; break;
      case Bus::AHB2: RCCx->AHB2ENR |= dev->periph; break;
      case Bus::AHB3: RCCx->AHB3ENR |= dev->periph; break;
      case Bus::APB1: RCCx->APB1ENR |= dev->periph; break;
      case Bus::APB2: RCCx->APB2ENR |= dev->periph; break;

   };

 //if( !silent )
 //   LOG << _name << ": " << dev->name() << " enabled at " << dev->bus.name;

   return *this;
}


STM32_RCC& STM32_RCC::disable( BusSlave *dev, bool silent )
{
   RCC_TypeDef *RCCx = (RCC_TypeDef*)_iobase;

   switch( dev->bus.id ) {

      case Bus::AHB1: RCCx->AHB1ENR &= ~dev->periph; break;
      case Bus::AHB2: RCCx->AHB2ENR &= ~dev->periph; break;
      case Bus::AHB3: RCCx->AHB3ENR &= ~dev->periph; break;
      case Bus::APB1: RCCx->APB1ENR &= ~dev->periph; break;
      case Bus::APB2: RCCx->APB2ENR &= ~dev->periph; break;

   };

 //if( !silent )
 //   LOG << _name << ": " << dev->name() << " disabled";

   return *this;
}


STM32_RCC& STM32_RCC::clocks( Clocks *clk )
{
   RCC_TypeDef *RCCx = (RCC_TypeDef*)_iobase;

   uint32_t SWS = ( RCCx->CFGR & RCC_CFGR_SWS ) >> 2;

   switch( SWS ) {

      case ClockSource::HSI:

         clk->SYSCLKFreq = HSI_VALUE;
         break;

      case ClockSource::HSE:

         clk->SYSCLKFreq = HSE_VALUE;
         break;

      case ClockSource::PLL:
         {
            /* see STM32 ref. manual sec. 6.3.2 "RCC PLL configuration register" */

            uint32_t pllsrc = ( RCCx->PLLCFGR & RCC_PLLCFGR_PLLSRC ) >> 22;
            uint32_t pllp   = ( RCCx->PLLCFGR & RCC_PLLCFGR_PLLP   ) >> 16;
            uint32_t plln   = ( RCCx->PLLCFGR & RCC_PLLCFGR_PLLN   ) >>  6;
            uint32_t pllm   = ( RCCx->PLLCFGR & RCC_PLLCFGR_PLLM   );

            uint32_t pllvco = ( pllsrc == 0 ) ? HSI_VALUE : HSE_VALUE;
                     pllvco = ( pllvco / pllm ) * plln;

            clk->SYSCLKFreq = pllvco / (( pllp + 1 ) << 1 );
         }
         break;

      default:

         clk->SYSCLKFreq = HSI_VALUE;
         break;

   }

   uint32_t HPRE  = ( RCCx->CFGR & RCC_CFGR_HPRE  ) >>  4;
   uint32_t PPRE1 = ( RCCx->CFGR & RCC_CFGR_PPRE1 ) >> 10;
   uint32_t PPRE2 = ( RCCx->CFGR & RCC_CFGR_PPRE1 ) >> 13;

   clk->HCLKFreq  = clk->SYSCLKFreq >> pv[ HPRE  ];
   clk->PCLK1Freq = clk->HCLKFreq   >> pv[ PPRE1 ];
   clk->PCLK2Freq = clk->HCLKFreq   >> pv[ PPRE2 ];

   return *this;
};


uint32_t STM32_RCC::freq( Bus &bus )
{
   Clocks clk;
   clocks( &clk );

   uint32_t rv = 0;

   switch( bus.id ) {

      case Bus::AHB1: rv = clk.HCLKFreq;  break;
      case Bus::AHB2: rv = clk.HCLKFreq;  break;
      case Bus::AHB3: rv = clk.HCLKFreq;  break;
      case Bus::APB1: rv = clk.PCLK1Freq; break;
      case Bus::APB2: rv = clk.PCLK2Freq; break;

   }

   return rv;
}

/*EoF*/
