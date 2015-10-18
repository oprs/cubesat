
#include "device/RstClk.h"
#include "device/Power.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Power::Power( Bus& bus,
              const uint32_t iobase,
              const uint32_t periph,
              const char    *name )
   : Device( name ), BusSlave( bus, iobase, periph )
{ ; }


Power::~Power()
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

Power& Power::init( void )
{
   LOG << _name << ": Power Controller at " << bus.name;
   return *this;
}


Power& Power::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RCC.enable( this, silent );
   return *this;
}


Power& Power::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   RCC.disable( this, silent );
   return *this;
}


Power& Power::enableBKPSRAM( void )
{
   PWR_TypeDef *PWRx = (PWR_TypeDef*)iobase;

   PWRx->CR  |=  PWR_CR_DBP;
   PWRx->CSR |=  PWR_CSR_BRE;
 //PWRx->CR  &= ~PWR_CR_DBP;

   return *this;
}


Power& Power::disableBKPSRAM( void )
{
   PWR_TypeDef *PWRx = (PWR_TypeDef*)iobase;

 // PWRx->CR  |=  PWR_CR_DBP;
   PWRx->CSR &= ~PWR_CSR_BRE;
   PWRx->CR  &= ~PWR_CR_DBP;

   return *this;
}

