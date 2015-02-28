#include "gestionModem9600.h"
#include <stm32f4xx_gpio.h>

void setModem9600On(){
	GPIO_SetBits(GPIOC,GPIO_Pin_8);

}

void setModem9600Off(){
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
}

/*
 * A FAIRE
 */

void writeTLM(char * donnee,int nbCaractere){

}

