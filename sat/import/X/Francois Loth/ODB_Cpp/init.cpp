#include "init.h"
#include <stm32f4xx_gpio.h>
#include "usart.h"
#include "spi.h"
#include <stm32f4xx_rcc.h>
#include "memoire.h"
#include "debug.h"
#ifndef VAR_GLOBALE
#define VAR_GLOBALE
#include "var_globale.h"
#endif
/*
*
* Cet état se produit lors de la mise sous tension du satellite
* ou à chaque Reset suite à un SEU faisant le RESET du microprocesseur.
* L’ODB initialise les ports du processeur,
* lit le nom du satellite (X ou Mines),
* sort la version soft sur la sortie debug,
* vérifie si le précédent état n’était pas en état Stand by,
*  vérifie si les antennes sont sorties,
*  effectue le dégerbage si nécessaire,
*  incrémente le compteur de reset  le  et bascule sur le SW Task Manager.
*
*
*  Nom du port	N° Port ARM	état logique
CS1 (ADC sur carte énergie)	PA4	1
CS2 (ADC sur carte énergie)	PA5	1
CS3 (ADC sur carte ODB)	PA6	1
CS4 (mémoire ODB 32 Mbits)	PA7	1
CS5 (ADCS sur carte FIPEX)	PC4	1
CS6 (mémoire ODB 32 Mbits)	PA0	1
P1	PC5	0
P2	PB0	0
P3	PB1	0
P4	PA1	0
ON/OFF_TX	PB15	0
ON/OFF_PA	PB13	0
DOUT (SPI) MISO	PB4	0
DIN (SPI) MOSI	PB5	INPUT
SCLK (SPI)	PB3	0
ON/OFF_antenne	PA15	0
Status_antenne	PA11	input
ON/OFF_CTCSS	PB12	0
DEC_Tone	PA8	Input
ON/OFF_experience (FIPEX)	PB14	0
TX_FIPEX (ODB ->FIPEX)	PA2	TX port série 9600N81
RX_FIPEX (FIPEX -> ODB)	PA3	RX port série 9600N81
ON/OFF_ADCS	PC13	0
TX_ADCS (ODB -> ADCS)	PA9	TX port série 9600N81
RX_ADCS (ADCS -> ODB)	PA1033	RX port série 9600N81
ON_OFF_GPS	PC3	0
TX_GPS (GPS -> ODB)	PB11	TX port série 9600N81
RX_GPS (ODB -> GPS)	PB10
AX25_RX	PC7	RX port série 9600N81 (interruption)
Debug_TX	PC6	TX port série 9600N81
ON/OFF_9600	PC10	0
DATA_9600	PC8	0
CLK_9600	PC9	Input (interruption)
Selection_Sat	PC11	Input (usart_3 rx)


A FAIRE

CLK_9600	PC9	Input (interruption)


Initialisation de tous les variables type timer, tension, puissance, etc.
Il serait préférable qu’elles soient en EEPROM afin de conserver
les valeurs définies lors des essais.
Liste exhaustive (à vérifier) et une valeur par défaut :
VBAT_critique : 6V
VBAT_mini : 6.4V
Tempo_bat : récurrence de transmission de la tension BAT en CW
Antenna_temporisation : 15s
TX_temporisation : 1s
*
*/

void initPort(){

	GPIO_InitTypeDef  GPIO_InitStructure;

	initialiserUSART1();
	initialiserUSART2();
	initialiserUSART3();
	initialiserUSART6();
	init_spi1();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6
	| GPIO_Pin_7 | GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	GPIO_SetBits(GPIOA,GPIO_Pin_0);

	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14
	| GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_15;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_13
	| GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_8;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC,GPIO_Pin_4);

	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void incrementationCompteurReset(){
	uint8_t adresse[3];
	adresse[0]=0x0;
	adresse[1]=0x0;
	adresse[2]=0x1;

	uint8_t partieUn = ReadExtMemorie(adresse);

	adresse[2]=0x1;
	envoyerDataHexaUSART6(partieUn);
	/*
	uint8_t partieDeux = ReadExtMemorie(adresse);

	uint16_t compteur = (partieUn << 8) | partieDeux;

	compteur++;
	uint16_t temp=compteur;
	partieUn=temp>>8;
	partieDeux=compteur & 0x00FF;

	WriteExtMemorie(partieDeux,adresse);
	adresse[2]=0x0;
	WriteExtMemorie(partieUn,adresse);

	char data[2];
	data[0]=partieUn;
	data[1]=partieDeux;
	envoyerDataDecimalUSART6(partieUn);
	envoyerDataDecimalUSART6(partieDeux);

	writeDebug(data,2);
	*/
}
void envoiVersionSoft(){

	char data[]="version 1";

	writeDebug(data,9);
}

bool OpenAntenna(){

	for(int i=0;i<3;i++){
		GPIO_SetBits(GPIOA,GPIO_Pin_15);

		//Timer Antenna_temporisation seconde
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);
		//lecture PA11 pour vérifier l'ouverture de l'antenne
		if(GPIO_ReadOutputDataBit (GPIOA,GPIO_Pin_11)==0x1)break;

	}
	if(GPIO_ReadOutputDataBit (GPIOA,GPIO_Pin_11)==0x1){
		return 1;
	}

		return 0;

}


void lectureNomSatellite(){

	if(GPIO_ReadOutputDataBit (GPIOC,GPIO_Pin_11)==0x1){
		//X
		id_sat=1;

	}
	else{

		//MINE
		id_sat=0;
	}
}

void initVariable(){

}

void timerTrente(){

}

bool nonStandBy(){
return true;
}

void VoidINIT(){

	initPort();
	envoyerDataUSART6('1');
	lectureNomSatellite();
	envoyerDataUSART6('2');
	envoiVersionSoft();
	envoyerDataUSART6('3');

	if(nonStandBy())
	{
		if(GPIO_ReadOutputDataBit (GPIOA,GPIO_Pin_11)==0x0){
			timerTrente();
			OpenAntenna();
		}

	}
	envoyerDataUSART6('4');
	incrementationCompteurReset();
	envoyerDataUSART6('5');
}
