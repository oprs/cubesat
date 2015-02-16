#ifndef _ADC_H
#define  _ADC_H
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include "spi.h"

typedef uint8_t byte;

enum channel
{
	canal0 = 128 + 0 + 15,    // ADCS
	canal1 = 128 + 64 + 15,   //I_EXP
	canal2 = 128 + 16 + 15,   //I_RX
	canal3 = 128 + 80 + 15,   //RSSI
	canal4 = 128 + 32 + 15,   //I_TX
	canal5 = 128 + 96 + 15,   //P_TX
	canal6 = 128 + 48 + 15,   //P_PA
	canal7 = 128 + 112 + 15   //T_PA
};


class CAdc {
public:
	byte read(channel canal);
	CAdc(CSpi *spi,CS numCS);
	~CAdc();
private:
	CSpi *m_spi;
	CS m_cs;
	GPIO_InitTypeDef  m_GPIO_InitStruct_adc;
};
//uint8_t value(int canal);
#endif


