#include "gestionADCS.h"
#include "usart.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
void InitADCS(){
	GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

		//Configure tx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		//Configure rx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

		GPIO_Init(GPIOA, &GPIO_InitStructure);

		USART_InitTypeDef USART_InitStr;

		USART_InitStr.USART_BaudRate					= 9600;
		USART_InitStr.USART_WordLength				= USART_WordLength_8b;
		USART_InitStr.USART_StopBits					= USART_StopBits_1;
		USART_InitStr.USART_Parity						= USART_Parity_No;
		USART_InitStr.USART_Mode						= USART_Mode_Tx | USART_Mode_Rx;
		USART_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
		USART_Init(USART1, &USART_InitStr);

		USART_Cmd(USART1, ENABLE);
}



void setADCSOn(){
	GPIO_SetBits(GPIOC,GPIO_Pin_13);

}
void setADCSOff(){
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}


void writeADCS(char * Phrase,int nbCaractere){


for(int i=0;i<nbCaractere;i++)
	envoyerDataUSART1(Phrase[i]);
}

/*
 * A FAIRE
 */
int readADCS(char* Phrase){
	/*
	char RXBUFF[50];

	int i = 0;
	  while(1)
	  {
	   // Wait until a byte is received
	   while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	    // read byte
	    RXBUFF[i++] = USART_ReceiveData(USART1);

	  }
*/
	  return 0;
}
