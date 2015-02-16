#include "pa.h"
#include <stm32f4xx_gpio.h>





int SetPAPuissance (int P){

	if(P<1 || P>4) return -1;


	if(P==1){
		GPIO_SetBits(GPIOC,GPIO_Pin_5);

		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	}
	else if (P==2) {


		GPIO_ResetBits(GPIOC,GPIO_Pin_5);

		GPIO_SetBits(GPIOB,GPIO_Pin_0);

		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);


	} else if (P==3) {

		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);

		GPIO_SetBits(GPIOB,GPIO_Pin_1);

		GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	} else {

		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);

		GPIO_SetBits(GPIOA,GPIO_Pin_1);




	}

	return 0;

}
void  SetPAOn (){

	GPIO_SetBits(GPIOB,GPIO_Pin_13);


}

void  SetPAOff (){
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);

}
