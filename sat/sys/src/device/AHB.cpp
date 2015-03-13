
#include <stm32f4xx.h>

#include "device/AHB.h"

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

AHB& AHB::enable( BusDevice *dev )
{
	switch( _AHBn ) {

		case 1: RCC->AHB1ENR |= dev->periph; break;
		case 2: RCC->AHB2ENR |= dev->periph; break;
		case 3: RCC->AHB3ENR |= dev->periph; break;

		default:
			throw 42; /* XXX */
	}

	return *this;
}


AHB& AHB::disable( BusDevice *dev )
{
	switch( _AHBn ) {

		case 1: RCC->AHB1ENR &= ~dev->periph; break;
		case 2: RCC->AHB2ENR &= ~dev->periph; break;
		case 3: RCC->AHB3ENR &= ~dev->periph; break;

		default:
			throw 42; /* XXX */
	}

	return *this;
}


uint32_t AHB::freq( void )
{
	return 0; /* XXX */
}

/*EoF*/
