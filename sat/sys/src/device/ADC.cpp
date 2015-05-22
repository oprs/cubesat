#include "device/ADC.h"

using namespace qb50;

ADC::ADC(Bus& bus,
			const uint32_t iobase,
			const uint32_t periph,
			GPIOPin& pin,
			GPIOPin::Mode mode,
			GPIOPin::Channel channel)
		:BusDevice( bus, iobase, periph),_pin( pin ),_mode ( mode)
		{
		    _numConversions = 5;
		    _channel  = channel;
		}

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
		.pullUp()
		.mode(_mode);

	bus.enable( this );
    ADCx->CR1 = 0; //Set resolution for the ADC
    uint32_t tmpreg = 0;
    tmpreg = ADCx->CR2;
    tmpreg &= ((uint32_t)0xC0FFF7FD);  //CR2_CLEAR_MASK
    tmpreg |= 0 << 1;
    ADCx->CR2 = tmpreg; //Sets the continuous conversion mode

    tmpreg = ADCx->SQR1;

    tmpreg &= ((uint32_t)0xFF0FFFFF); //SQR1_L_RESET

    //This sets the number of conversions to perform
    //Corresponds to the number of sun sensors on board
    //
    tmpreg |= (uint32_t)(_numConversions-1) << 20;

    ADCx->SQR1 = tmpreg;
	return *this;
}

ADC& ADC::disable( void )
{
	//ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;

	bus.disable( this );

	_pin.disable();

	return *this;
}
//Rather than modifying individual registers we just use the code written for the ADC using the stm32f4 peripheral library
uint16_t ADC::getValue_adc()
{
	uint16_t adc_val = 0;
	ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;
	ADC_RegularChannelConfig(ADCx, _channel, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADCx);

	while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET){;}
	adc_val = ADC_GetConversionValue(ADCx);
	return adc_val;
}
