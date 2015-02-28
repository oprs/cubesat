#include "decodeurCTCSS.h"
#include <stm32f4xx_gpio.h>



void SetCTCSSOn (){
	GPIO_SetBits(GPIOB,GPIO_Pin_12);



}
void SetCTCSSOff (){

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
