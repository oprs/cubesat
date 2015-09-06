
#include <iostream>
#include <stm32f4xx.h>

#include "device/AHB.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

AHB::AHB( BusId id, const char *name ) : Bus( name ), _id( id )
{ ; }


AHB::~AHB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

AHB& AHB::enable( BusDevice *dev )
{
	switch( _id ) {
		case BUS1: RCC->AHB1ENR |= dev->periph; break;
		case BUS2: RCC->AHB2ENR |= dev->periph; break;
		case BUS3: RCC->AHB3ENR |= dev->periph; break;
	}

	//std::cout << _name << ": " << dev->name() << " enabled\r\n";

	return *this;
}


AHB& AHB::disable( BusDevice *dev )
{
	switch( _id ) {
		case BUS1: RCC->AHB1ENR &= ~dev->periph; break;
		case BUS2: RCC->AHB2ENR &= ~dev->periph; break;
		case BUS3: RCC->AHB3ENR &= ~dev->periph; break;
	}

	//std::cout << _name << ": " << dev->name() << " disabled\r\n";

	return *this;
}


uint32_t AHB::freq( void )
{
	return 0; /* XXX */
}

/*EoF*/
