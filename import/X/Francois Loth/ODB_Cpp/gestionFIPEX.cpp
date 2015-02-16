#include "gestionFIPEX.h"
#include "usart.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

void setFIPEXOn(){
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
}

void setFIPEXOff(){
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void writeFipex(char* Phrase,int nbCaractere ){
	for(int i=0;i<nbCaractere;i++)
	envoyerDataUSART2(Phrase[i]);
}

/*
* A FAIRE
*/
int readFipex(char* Phrase){
	/*
	char RXBUFF[50];
	int i = 0;
	while(1)
	{
		// Wait until a byte is received
		while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
		// read byte
		RXBUFF[i++] = USART_ReceiveData(USART2);
	}
*/
	return 0;
}

void InitSerialPortFIPEX(){
	initialiserUSART2();
}


