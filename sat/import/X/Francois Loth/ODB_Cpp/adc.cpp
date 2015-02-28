#include "adc.h"
#include <stm32f4xx_gpio.h>
#include "stm32f4xx_spi.h"
#include "spi.h"
#include "usart.h"

GPIO_InitTypeDef  GPIO_InitStruct_adc;
uint8_t READ(int CS,int canal)
{



	/* Configure the chip select pin
		in this case we will use PA6 */
	if(CS==1){
		GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_4;
	}
	else if (CS==2) {
		GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_5;
	}	else if (CS==3) {

		GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_6;
	}	else if (CS==5) {
		GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_4;
	}

	GPIO_InitStruct_adc.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_adc.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_adc.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct_adc.GPIO_PuPd = GPIO_PuPd_UP;
	if(CS==5)
	GPIO_Init(GPIOC, &GPIO_InitStruct_adc);
	else{

		GPIO_Init(GPIOA, &GPIO_InitStruct_adc);

	}

	uint8_t Recevie[3];

	uint8_t valeur;
	SPI_Cmd(SPI1, ENABLE);

	uint8_t b7b2 = 0, b1b0 = 0;


	//   valeur = SPI_send((uint8_t)c);
	char cs [2];

	if(CS==1){
		cs[0]='a';
		cs[1]='4';

	}
	else if (CS==2) {
		cs[0]='a';
		cs[1]='5';
	}	else if (CS==3) {

		cs[0]='a';
		cs[1]='6';
	}	else if (CS==5) {
		cs[0]='c';
		cs[1]='4';
	}
	activerChipSelect(cs);

	/*
			canal0 = 128 + 0 + 15=143 (0x8F) [RV7],    // ADCS
			canal1 = 128 + 64 + 15=207 (0xCF),   //I_EXP
			canal2 = 128 + 16 + 15=159 (0x9F),   //I_RX
			canal3 = 128 + 80 + 15=223 (0xDF) [RV5],   //RSSI
			canal4 = 128 + 32 + 15=175 (0xAF) [RV6],   //I_TX
			canal5 = 128 + 96 + 15=239 (0xEF) [RV3],   //P_TX
			canal6 = 128 + 48 + 15=191 (0xBF) [RV1],   //P_PA
			canal7 = 128 + 112 + 15=255(0xFF) [RV4]  //T_PA
			*/
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	if(canal==0){
		SPI_I2S_SendData(SPI1, 0x8F);
	}else if(canal==1){
		SPI_I2S_SendData(SPI1, 0xcf);
	}
	else if(canal==2){
		SPI_I2S_SendData(SPI1, 0x9f);
	}
	else if(canal==3){

		SPI_I2S_SendData(SPI1, 0xdf);
	}
	else if(canal==4){
		SPI_I2S_SendData(SPI1, 0xaf);
	}
	else if(canal==5){
		SPI_I2S_SendData(SPI1, 0xef);
	}
	else if(canal==6){
		SPI_I2S_SendData(SPI1, 0xbf);
	}
	else if(canal==7){
		SPI_I2S_SendData(SPI1, 0xff);
	}



	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
			Recevie[0] = SPI_I2S_ReceiveData(SPI1);


	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	Recevie[1] = SPI_I2S_ReceiveData(SPI1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	Recevie[2] = SPI_I2S_ReceiveData(SPI1);



	desactiverChipSelect(cs);

	b7b2 = (Recevie[1] & 0x3F) << 2;
	b1b0 = (Recevie[2] & 0xC0)>>6;


	valeur = (b7b2 | b1b0);
	//valeur= (b7b2 << 8) | b1b0;
	return valeur;
}
