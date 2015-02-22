
#include "device/APB.h"
#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

APB::APB( uint32_t APBn ) : _APBn( APBn )
{ ; }


APB::~APB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void APB::enable( BusDevice *dev )
{
   switch( _APBn ) {

      case 1: RCC->APB1ENR |= dev->periph; break;
      case 2: RCC->APB2ENR |= dev->periph; break;

      default:
         throw 42; /* XXX */
   }
}


void APB::disable( BusDevice *dev )
{
   switch( _APBn ) {

      case 1: RCC->APB1ENR &= ~dev->periph; break;
      case 2: RCC->APB2ENR &= ~dev->periph; break;

      default:
         throw 42; /* XXX */
   }
}

/*EoF*/
