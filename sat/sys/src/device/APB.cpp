
#include <iostream>
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>

#include "device/APB.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

APB::APB( BusId id, const char *name ) : Bus( name ), _id( id )
{ ; }


APB::~APB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

APB& APB::enable( BusDevice *dev )
{
	switch( _id ) {
		case BUS1: RCC->APB1ENR |= dev->periph; break;
		case BUS2: RCC->APB2ENR |= dev->periph; break;
	}

	//std::cout << _name << ": " << dev->name() << " enabled\r\n";

	return *this;
}


APB& APB::disable( BusDevice *dev )
{
	switch( _id ) {
		case BUS1: RCC->APB1ENR &= ~dev->periph; break;
		case BUS2: RCC->APB2ENR &= ~dev->periph; break;
	}

	//std::cout << _name << ": " << dev->name() << " disabled\r\n";

	return *this;
}


uint32_t APB::freq( void )
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq( &clocks );

	uint32_t rv = 0;

	switch( _id ) {
		case BUS1: rv = clocks.PCLK1_Frequency; break;
		case BUS2: rv = clocks.PCLK2_Frequency; break;
	}

	return rv;
}

/*EoF*/
