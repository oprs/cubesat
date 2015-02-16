#include "gestionGPS.h"
#include "usart.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>

void InitGPS(){
	initialiserUSART3();
}



void setGPSOn(){
	GPIO_SetBits(GPIOC,GPIO_Pin_3);

}
void setGPSOff(){
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}


void writeGPS(char * Phrase,int nbCaractere){


for(int i=0;i<nbCaractere;i++)
	envoyerDataUSART3(Phrase[i]);
}

/*
 * A FAIRE
 */
int readAGPS(char* Phrase){
	/*
	char RXBUFF[50];

	int i = 0;
	  while(1)
	  {
	   // Wait until a byte is received
	   while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
	    // read byte
	    RXBUFF[i++] = USART_ReceiveData(USART3);

	  }
*/
	  return 0;
}
