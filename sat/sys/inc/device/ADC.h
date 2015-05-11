#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include <FreeRTOS.h>
#include <semphr.h>

#include "BusDevice.h"
#include "GPIOPin.h"
#include "NVIC.h"

namespace qb50{

	class ADC : public BusDevice
	{
	public: 

		//Constructor
		ADC(Bus& bus, 
			const uint32_t iobase, 
			const uint32_t periph, 
			GPIOPin& pin, 
			GPIOPin::Mode mode
		);

		//Destructor 
		~ADC(); 

		ADC& enable(void);
		ADC& disable(void);		


	private:

		GPIOPin& _pin;
		GPIOPin::Alt  _alt; 
		GPIOPin::Mode _mode;

		//Channels for the ADC 
		enum Channel{
			CH0 = ADC_Channel_0, 
			CH1 = ADC_Channel_1, 
			CH2 = ADC_Channel_2, 
			CH3 = ADC_Channel_3, 
			CH4 = ADC_Channel_4, 
			CH5 = ADC_Channel_5, 
			CH6 = ADC_Channel_6, 
			CH7 = ADC_Channel_7, 
			CH8 = ADC_Channel_8, 
			CH9 = ADC_Channel_9, 
			CH10 = ADC_Channel_10, 
			CH11 = ADC_Channel_11, 
			CH12 = ADC_Channel_12, 
			CH13 = ADC_Channel_13, 
			CH14 = ADC_Channel_14, 
			CH15 = ADC_Channel_15, 
			CH16 = ADC_Channel_16, 
			CH17 = ADC_Channel_17, 
			CH18 = ADC_Channel_18, 
		};
	};

	extern qb50::ADC ADC1;
	extern qb50::ADC ADC2;
	extern qb50::ADC ADC3;
}

#endif
/* ADC_H_INCLUDED */
