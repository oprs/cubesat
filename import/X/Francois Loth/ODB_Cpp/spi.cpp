#include "spi.h"
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <string.h>
#include "usart.h"

void init_spi1(void){

	GPIO_InitTypeDef  GPIO_InitStruct_spi_1;
	SPI_InitTypeDef SPI_InitStruct_spi_1;

	// enable clock for used IO pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


	// enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);


	/* configure pins used by SPI1
		* PB3 = SCK
		* PB5 = MISO
		* PB4 = MOSI
		*/


	GPIO_InitStruct_spi_1.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_InitStruct_spi_1.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct_spi_1.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_spi_1.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_spi_1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct_spi_1);
	// connect SPI1 pins to SPI alternate function
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);





	/* configure SPI1 in Mode 0
		* CPOL = 0 --> clock is low when idle
		* CPHA = 0 --> data is sampled at the first edge
		*/
	SPI_InitStruct_spi_1.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct_spi_1.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct_spi_1.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct_spi_1.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct_spi_1.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct_spi_1.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct_spi_1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct_spi_1.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first

	SPI_Init(SPI1, &SPI_InitStruct_spi_1);

	SPI_Cmd(SPI1, ENABLE); // enable SPI1
}


void activerChipSelect(char cs[]){

	GPIO_InitTypeDef  GPIO_InitStruct_cs;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_0 |GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct_cs);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct_cs);


	//cs6
	if (strcmp(cs,"a0")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_0);

		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_ResetBits(GPIOA,GPIO_Pin_0);

	}
	//cs5
	else if (strcmp(cs,"c4")==0) {

		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);

		GPIO_ResetBits(GPIOC,GPIO_Pin_4);

	}
	//cs4
	else if (strcmp(cs,"a7")==0){

		GPIO_SetBits(GPIOA,GPIO_Pin_7);

		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
	}
	//cs3
	else if (strcmp(cs,"a6")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_6);

		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_ResetBits(GPIOA,GPIO_Pin_6);

	}
	//cs2
	else if (strcmp(cs,"a5")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_5);

		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_ResetBits(GPIOA,GPIO_Pin_5);

	}
	//cs1
	else if (strcmp(cs,"a4")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_4);

		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_4);

		GPIO_ResetBits(GPIOA,GPIO_Pin_4);

	}


}

void desactiverChipSelect(char cs[]){

	GPIO_InitTypeDef  GPIO_InitStruct_cs;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_0 |GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct_cs);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct_cs);


	//cs6
	if (strcmp(cs,"a0")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_0);


	}
	//cs5
	else if (strcmp(cs,"c4")==0) {

		GPIO_SetBits(GPIOC,GPIO_Pin_4);


	}
	//cs4
	else if (strcmp(cs,"a7")==0){

		GPIO_SetBits(GPIOA,GPIO_Pin_7);


	}
	//cs3
	else if (strcmp(cs,"a6")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_6);


	}
	//cs2
	else if (strcmp(cs,"a5")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_5);



	}
	//cs1
	else if (strcmp(cs,"a4")==0) {

		GPIO_SetBits(GPIOA,GPIO_Pin_4);



	}


}
