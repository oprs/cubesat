#include "usart.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include <stdio.h>




void initialiserUSART1(){
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


	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void enableUSART1(){
	USART_Cmd(USART1, ENABLE);
}

void initialiserUSART2(){
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	//Configure tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Configure rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
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

void initialiserUSART3(){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	//Configure tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Configure rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStr;

	USART_InitStr.USART_BaudRate					= 9600;
	USART_InitStr.USART_WordLength				= USART_WordLength_8b;
	USART_InitStr.USART_StopBits					= USART_StopBits_1;
	USART_InitStr.USART_Parity						= USART_Parity_No;
	USART_InitStr.USART_Mode						= USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_Init(USART3, &USART_InitStr);
	USART_Cmd(USART3, ENABLE);


}

void initialiserUSART6(){

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

	//Configure tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//Configure rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitTypeDef USART_InitStr;

	USART_InitStr.USART_BaudRate					= 9600;
	USART_InitStr.USART_WordLength				= USART_WordLength_8b;
	USART_InitStr.USART_StopBits					= USART_StopBits_1;
	USART_InitStr.USART_Parity						= USART_Parity_No;
	USART_InitStr.USART_Mode						= USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	USART_Init(USART6, &USART_InitStr);
	USART_Cmd(USART6, ENABLE);


}

void USART_puts(char *s){

	while(*s){
		// wait until data register is empty
		while( !(USART1->SR & 0x00000040) );
		USART_SendData(USART1, *s);
		*s++;
	}
}

void envoyerDataUSART1(uint8_t data){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1,data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void envoyerDataUSART2(uint8_t data){
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2,data);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}

void envoyerDataUSART3(uint8_t data){
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3,data);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

void envoyerDataUSART6(uint8_t data){
	while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
	USART_SendData(USART6,data);
	while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
}

void envoyerDataDecimalUSART1(uint8_t data){

	char buf[4];
	sprintf(buf, "%d", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART1(buf[i]);
		i++;

	}
}

void envoyerDataDecimalUSART2(uint8_t data){

	char buf[4];
	sprintf(buf, "%d", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART2(buf[i]);
		i++;

	}
}

void envoyerDataDecimalUSART3(uint8_t data){


	char buf[4];
	sprintf(buf, "%d", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART3(buf[i]);
		i++;

	}
}

void envoyerDataDecimalUSART6(uint8_t data){


	char buf[4];
	sprintf(buf, "%d", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART6(buf[i]);
		i++;

	}
}

void envoyerDataHexaUSART1(uint8_t data){

	char buf[3];
	sprintf(buf, "%X", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART1(buf[i]);
		i++;

	}
}

void envoyerDataHexaUSART2(uint8_t data){
	char buf[3];
	sprintf(buf, "%X", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART2(buf[i]);
		i++;

	}
}

void envoyerDataHexaUSART3(uint8_t data){

	char buf[3];
	sprintf(buf, "%X", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART3(buf[i]);
		i++;

	}
}

void envoyerDataHexaUSART6(uint8_t data){

	char buf[3];
	sprintf(buf, "%X", data);
	int i=0;
	while(buf[i]!='\0'){
		envoyerDataUSART6(buf[i]);
		i++;

	}
}
