
#include "device/AHB.h"
#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

AHB::AHB( uint32_t AHBn ) : _AHBn( AHBn )
{ ; }


AHB::~AHB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void AHB::enable( BusDevice *dev )
{
   switch( _AHBn ) {

      case 1: RCC->AHB1ENR |= dev->periph; break;
      case 2: RCC->AHB2ENR |= dev->periph; break;
      case 3: RCC->AHB3ENR |= dev->periph; break;

      default:
         throw 42; /* XXX */
   }
}


void AHB::disable( BusDevice *dev )
{
   switch( _AHBn ) {

      case 1: RCC->AHB1ENR &= ~dev->periph; break;
      case 2: RCC->AHB2ENR &= ~dev->periph; break;
      case 3: RCC->AHB3ENR &= ~dev->periph; break;

      default:
         throw 42; /* XXX */
   }
}

/*EoF*/
