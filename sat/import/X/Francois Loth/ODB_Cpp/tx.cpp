#include "tx.h"
#include <stm32f4xx_gpio.h>


void setTXOn(){

	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	//timer TX_temporisation

}

void setTXOff(){

	GPIO_ResetBits(GPIOB,GPIO_Pin_14);

}
