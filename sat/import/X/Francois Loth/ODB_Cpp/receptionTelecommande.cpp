#include "receptionTelecommande.h"
#include <stm32f4xx_usart.h>
#include "usart.h"
/*
 * A FAIRE
 */
int readRXAX25(char* Phrase){
	/*
		char RXBUFF[50];

		int i = 0;
		  while(1)
		  {
		   // Wait until a byte is received
		   while(USART_GetFlagStatus(USART6, USART_FLAG_RXNE) == RESET);
		    // read byte
		    RXBUFF[i++] = USART_ReceiveData(USART6);

		  }
	*/
		  return 0;

}

void InitSerialPortCMDAX25(){
	initialiserUSART6();
}
