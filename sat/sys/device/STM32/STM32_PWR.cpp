
#include "STM32/STM32_RCC.h"
#include "STM32/STM32_PWR.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_PWR::STM32_PWR( Bus& bus,
                      const uint32_t iobase,
                      const uint32_t periph,
                      const char    *name )
   : STM32_Device( name, bus, iobase, periph )
{ ; }


STM32_PWR::~STM32_PWR()
{ ; }

// RCC_AHB1PeriphClockCmd

/*
  if (NewState != DISABLE)
  {
    RCC->AHB1ENR |= RCC_AHB1Periph;
  }
  else
  {
    RCC->AHB1ENR &= ~RCC_AHB1Periph;
  }
*/

//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_PWR& STM32_PWR::init( void )
{
   kprintf( "%s: STM32F4xx Power controller at %s\r\n", _name, bus.name );
   return *this;
}


STM32_PWR& STM32_PWR::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RCC.enable( this, silent );

   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


STM32_PWR& STM32_PWR::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   RCC.disable( this, silent );

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


STM32_PWR& STM32_PWR::enableBKP( void )
{
   PWR_TypeDef *PWRx = (PWR_TypeDef*)iobase;

   PWRx->CR  |=  PWR_CR_DBP;
   PWRx->CSR |=  PWR_CSR_BRE;
 //PWRx->CR  &= ~PWR_CR_DBP;

   return *this;
}


STM32_PWR& STM32_PWR::disableBKP( void )
{
   PWR_TypeDef *PWRx = (PWR_TypeDef*)iobase;

 // PWRx->CR  |=  PWR_CR_DBP;
   PWRx->CSR &= ~PWR_CSR_BRE;
   PWRx->CR  &= ~PWR_CR_DBP;

   return *this;
}

