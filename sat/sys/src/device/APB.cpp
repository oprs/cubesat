
#include <iostream>
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>

#include "device/APB.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

APB::APB( uint32_t APBn, const char *name ) : Bus( name ), _APBn( APBn )
{ ; }


APB::~APB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

APB& APB::enable( BusDevice *dev )
{
	switch( _APBn ) {

		case 1: RCC->APB1ENR |= dev->periph; break;
		case 2: RCC->APB2ENR |= dev->periph; break;

		default:
			throw 42; /* XXX */
	}

	//std::cout << _name << ": " << dev->name() << " enabled\r\n";

	return *this;
}


APB& APB::disable( BusDevice *dev )
{
	switch( _APBn ) {

		case 1: RCC->APB1ENR &= ~dev->periph; break;
		case 2: RCC->APB2ENR &= ~dev->periph; break;

		default:
			throw 42; /* XXX */
	}

	//std::cout << _name << ": " << dev->name() << " disabled\r\n";

	return *this;
}


uint32_t APB::freq( void )
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq( &clocks );

	uint32_t rv = 0;

	switch( _APBn ) {

		case 1: rv = clocks.PCLK1_Frequency; break;
		case 2: rv = clocks.PCLK2_Frequency; break;

		default:
			throw 42; /* XXX */
	}

	return rv;
}

/*EoF*/
