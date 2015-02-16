
#include "CoreDevice.h"
#include "device/AHB.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

AHB::AHB( unsigned AHBn ) : AHBn( AHBn )
{ ; }


AHB::~AHB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void AHB::enable( CoreDevice *dev )
{
   switch( AHBn ) {

      case 0: RCC_AHB1PeriphClockCmd( dev->periph, ENABLE ); break;
      case 1: RCC_AHB2PeriphClockCmd( dev->periph, ENABLE ); break;
      case 2: RCC_AHB3PeriphClockCmd( dev->periph, ENABLE ); break;

      default:
         throw 42; /* XXX */
   }
}


void AHB::disable( CoreDevice *dev )
{
   switch( AHBn ) {

      case 0: RCC_AHB1PeriphClockCmd( dev->periph, DISABLE ); break;
      case 1: RCC_AHB2PeriphClockCmd( dev->periph, DISABLE ); break;
      case 2: RCC_AHB3PeriphClockCmd( dev->periph, DISABLE ); break;

      default:
         throw 42; /* XXX */
   }
}

/*EoF*/
