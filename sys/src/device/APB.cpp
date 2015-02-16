
#include "CoreDevice.h"
#include "device/APB.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

APB::APB( unsigned APBn ) : APBn( APBn )
{ ; }


APB::~APB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void APB::enable( CoreDevice *dev )
{
   switch( APBn ) {

      case 0: RCC_APB1PeriphClockCmd( dev->periph, ENABLE ); break;
      case 1: RCC_APB2PeriphClockCmd( dev->periph, ENABLE ); break;

      default:
         throw 42; /* XXX */
   }
}


void APB::disable( CoreDevice *dev )
{
   switch( APBn ) {

      case 0: RCC_APB1PeriphClockCmd( dev->periph, DISABLE ); break;
      case 1: RCC_APB2PeriphClockCmd( dev->periph, DISABLE ); break;

      default:
         throw 42; /* XXX */
   }
}

/*EoF*/
