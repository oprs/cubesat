#include "device/ADC.h"
#include "stm32f4xx.h" 

using namespace qb50;

ADC::ADC(Bus& bus, 
			const uint32_t iobase, 
			const uint32_t periph, 
			GPIOPin& pin, 
			GPIOPin::Alt alt)
		:BusDevice( bus, iobase, periph), 
		_pin( pin ), 
		_mode ( mode)

ADC::~ADC()
{
	disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ADC& ADC::enable( void )
{
	ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase; 

	_pin.enable()
		.pullup()
		.mode(_mode);

	bus.enable( this );

	//To add ADC configuration methods 

	return *this; 
}

ADC& ADC::disable( void )
{
	ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;

	bus.disable( this );

	_pin.disable();

	return *this; 
}