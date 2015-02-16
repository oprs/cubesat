
#include "debug.h"
#include "memoire.h"
#include "adc.h"
#include "spi.h"
#include "usart.h"
#include "init.h"
#include "rtc.h"
//#include "tm.h"
//#include "delay.h"
#include "defines.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_iwdg.h>
#include <stm32f4xx_usart.h>
#include <misc.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <string.h>
#include <stdio.h>

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount);

uint32_t multiplier;

void TM_Delay_Init(void) {
    RCC_ClocksTypeDef RCC_Clocks;

    /* Get system clocks */
    RCC_GetClocksFreq(&RCC_Clocks);

    /* While loop takes 4 cycles */
    /* For 1 us delay, we need to divide with 4M */
    multiplier = RCC_Clocks.HCLK_Frequency / 4000000;
}

void TM_DelayMicros(uint32_t micros) {
    /* Multiply micros with multipler */
    /* Substract 10 */
    micros = micros * multiplier - 10;
    /* 4 cycles for one loop */
    while (micros--);
}

void TM_DelayMillis(uint32_t millis) {
    /* Multiply millis with multipler */
    /* Substract 10 */
    millis = 1000 * millis * multiplier - 10;
    /* 4 cycles for one loop */
    while (millis--);
}

//void USART3_IRQHandler(void);


void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void t1(){
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 |GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	// pin PB13 (on/off pa), PB12 (on/off ctcss), PB14 (on/off tx), PB0 (P2),
	//PB1(P3), PB15(on/off tx)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_12 | GPIO_Pin_14 |GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	//pin PC10 (on/off 9600), PC13(on/off adcs), PC5 (P1), PC3 (on/off gps)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_13 |GPIO_Pin_5 |GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	while(1){
		GPIO_SetBits(GPIOA,GPIO_Pin_15);
		Delay(1194303);
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		Delay(1194303);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		Delay(1194303);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOC,GPIO_Pin_10);
		Delay(1194303);
		GPIO_ResetBits(GPIOC,GPIO_Pin_10);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay(1194303);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		Delay(1194303);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		Delay(1194303);
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		Delay(10194303);
	}
}


void testWatchDog(){
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	Delay(4000000);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
	GPIO_SetBits(GPIOA,GPIO_Pin_1);

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(0x0FFF);
	IWDG_ReloadCounter();
	IWDG_Enable();

	while(1){


	}

	IWDG_ReloadCounter();
}
/*
* Envoie les 4 adc sur le port debug
*/
void verifAllADC(){

	writeDebug("ADC:\r",5);
	for(int y=1;y<6;y++){
		if(y==4)y++;

		envoyerDataUSART6('H');
		envoyerDataDecimalUSART6(y);
		envoyerDataUSART6(':');

		for(int i=0;i<8;i++){
			envoyerDataUSART6('c');
			envoyerDataDecimalUSART6(i);
			envoyerDataUSART6(':');
			envoyerDataHexaUSART6(READ(y,i));
			envoyerDataUSART6(';');
		}
		envoyerDataUSART6('\r');
	}
}


void testRTC(){
	TM_RTC_Time_t t;
		t.date=30;
		t.hours=0;
		t.day=2;
		t.minutes=0;
		t.month=10;
		t.year=14;
		t.seconds=0;

		TM_RTC_Init(TM_RTC_ClockSource_External);
		TM_RTC_SetDateTime(&t,TM_RTC_Format_BIN);

		//TM_RTC_Interrupts(TM_RTC_Int_10s);
	while(1){
		TM_RTC_GetDateTime(&t,TM_RTC_Format_BIN);
			envoyerDataDecimalUSART6(t.seconds);
			Delay(10194303);
	}

}


int main(void)
{
	initialiserUSART1();
	initialiserUSART3();
	initialiserUSART6();
/*
 *
	//Enable HSE clock
	RCC_HSEConfig(RCC_HSE_ON);
	//Wait for clock to stabilize
	while (!RCC_WaitForHSEStartUp());
*/
	SystemInit();

	RCC_DeInit();


	RCC_PLLConfig (RCC_PLLSource_HSE,63,192,8,15);

	RCC_HSEConfig (RCC_HSE_ON);

	RCC_WaitForHSEStartUp();


	init_spi1();




	/*
	NVIC_Config();

	enableUSART1();
*/

	/*
	while  (1){
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)== RESET);
		char resp = USART_ReceiveData(USART1);
		envoyerDataUSART6(resp);
	}
*/
	/*
verifAllADC();
uint8_t adresse[3];
adresse[0]=0x00;
adresse[1]=0x00;
adresse[2]=0x01;
pageProgram(adresse,0x05);
incrementationCompteurReset();
*/




/*
 * uint8_t  resultat[3];

	while(1){

		readDeviceIdentification(resultat);

		envoyerDataUSART6('+');
		envoyerDataHexaUSART6(resultat[0]);
		envoyerDataUSART6('-');
		envoyerDataHexaUSART6(resultat[1]);
		envoyerDataUSART6('-');
		envoyerDataHexaUSART6(resultat[2]);
		envoyerDataUSART6('+');

		Delay(10194303);
	}
*/
	//t1();

uint8_t data[10];
uint8_t adresse[3];
adresse[0]=0x05;
adresse[1]=0x00;
adresse[2]=0x10;
writeStatusRegister();


//chipErase();
SectorErase(adresse);
adresse[2]=0x00;
pageProgram(adresse,0x5);
envoyerDataUSART6('d');
/*
uint8_t caseMemoire;
while(1){
	caseMemoire=readDataByte(adresse);
	envoyerDataHexaUSART6(caseMemoire);
	envoyerDataUSART6('-');
	Delay(10194303);
}
*/
adresse[2]=0x06;
envoyerDataUSART6('.');
ecrireByte(adresse,0x7);
envoyerDataUSART6('.');
envoyerDataUSART6('*');
envoyerDataHexaUSART6(readDataByte(adresse));
envoyerDataUSART6('*');
/*
readDataByte(adresse,data,10);

envoyerDataUSART6('-');
for(int i=0;i<10;i++){
	envoyerDataHexaUSART6(data[i]);
	envoyerDataUSART6('+');
}

envoyerDataUSART6('-');
adresse[2]=0x01;
pageProgram(adresse,0x1);
adresse[2]=0x02;
pageProgram(adresse,0x2);
adresse[2]=0x03;
pageProgram(adresse,0x3);
adresse[2]=0x00;
readDataByte(adresse,data,10);


envoyerDataUSART6('-');
for(int i=0;i<10;i++){
	envoyerDataHexaUSART6(data[i]);
	envoyerDataUSART6('+');
}
envoyerDataUSART6('-');


*/




}

void Delay(__IO uint32_t nCount)
{
	while(nCount--)
	{
	}
}

/*
void USART1_IRQHandler(void){
	envoyerDataUSART6('c');
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		char resp = USART_ReceiveData(USART1);
		envoyerDataUSART6(resp);
	}
}
*/
