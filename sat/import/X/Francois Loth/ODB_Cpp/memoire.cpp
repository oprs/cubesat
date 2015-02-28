#include "memoire.h"

#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_spi.h>
#include "spi.h"
#include "usart.h"


int toInt(uint8_t adresse[3]){
	return adresse[0]*256*256+adresse[1]*256+adresse[2];

}
void toOctet (int valeur, uint8_t adresse [3]){
	int temp=valeur%256%256;
	adresse[0]=valeur%256%256;
	valeur=valeur-temp*256*256;
	temp=valeur%256;
	adresse[1]=valeur%256;
	valeur=valeur-temp*256;
	adresse[2]=valeur;
}

void activerChipSelect(){
	char cs [2];
	cs[0]='a';
	cs[1]='7';
	activerChipSelect(cs);
}

void desactiverChipSelect(){
	char cs [2];
	cs[0]='a';
	cs[1]='7';
	desactiverChipSelect(cs);
}

/*
* Renvoi un tableau de 3 élément contenant les informations de la mémoire
* 37 (0011 0111), 30 (0011 0000) et 16 (0001 0110)
*/

void readDeviceIdentification(uint8_t resultat[3])
{
	activerChipSelect();
	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x9F);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);


	//data 37
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	resultat[0] = SPI_I2S_ReceiveData(SPI1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);

	//data 30
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	resultat[1] = SPI_I2S_ReceiveData(SPI1);


	//data 16
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	resultat[2] = SPI_I2S_ReceiveData(SPI1);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}





void writeEnabled()
{
	activerChipSelect();
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x06);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}

void writeDisabled()
{
	activerChipSelect();
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x4);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}

void writeStatusRegister()
{
	activerChipSelect();

	//Instruction

	SPI_I2S_SendData(SPI1, 0x1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	//data

	SPI_I2S_SendData(SPI1, 0x0);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}


void writeStatusRegister(uint8_t register1, uint8_t register2)
{
	writeEnabled();

	activerChipSelect();

	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x1);


	//data
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, register1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, register2);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}


uint8_t readStatusRegister_1()
{
	uint8_t registre1;

	activerChipSelect();

	//Instruction

	SPI_I2S_SendData(SPI1, 0x5);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, 0x0);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);


	SPI_I2S_ReceiveData(SPI1);

	//data
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	registre1 = SPI_I2S_ReceiveData(SPI1);

	desactiverChipSelect();

	return registre1;
}



uint8_t readStatusRegister_2()
{
	uint8_t registre2;

	activerChipSelect();

	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x35);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x0);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);


	//data
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	registre2 = SPI_I2S_ReceiveData(SPI1);

	desactiverChipSelect();

	return registre2;
}


void pageProgram(uint8_t adresse[3],uint8_t data)
{
	writeEnabled();

	activerChipSelect();
	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x02);


	//adresse
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,adresse[0]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[1]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[2]);

	//data
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, data);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();

}

void pageProgram(uint8_t adresse[3],uint8_t data[],int dataLength)
{
	writeEnabled();

	activerChipSelect();
	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x02);


	//adresse
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,adresse[0]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[1]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[2]);

	//data
	for(int i=0;i<dataLength;i++){
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, data[i]);
	}
	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();

}


void SectorErase(uint8_t adresse[3])
{
	writeEnabled();
	activerChipSelect();
	//Instruction

	SPI_I2S_SendData(SPI1, 0x20);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	//addresse 1

	SPI_I2S_SendData(SPI1, adresse[0]);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	//addresse 2
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[1]);


	//addresse 3
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, adresse[2]);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();

}


void chipErase()
{
	writeEnabled();
	activerChipSelect();
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0xc7);


	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();
}


uint8_t readDataByte(uint8_t adresse[3])
{

	writeEnabled();
	SPI_I2S_ClearFlag (SPI1,SPI_I2S_FLAG_TXE);
	SPI_I2S_ClearFlag (SPI1,SPI_I2S_FLAG_RXNE);
	uint8_t data;

	activerChipSelect();
	//Instruction
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1, 0x03);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);

	//addresse 1
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1, adresse[0]);


	//addresse 2
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1,  adresse[1]);


	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);


	//addresse 3
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1,  adresse[2]);


	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1, 0x00);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);

	//data
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
	data = SPI_I2S_ReceiveData(SPI1);

	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();

	return data;
}

void  readDataByte(uint8_t adresse[3],uint8_t data[],int dataLength)
{

	writeEnabled();

	activerChipSelect();

	//Instruction
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x03);

	//addresse 1
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,adresse[0]);


	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);


	//addresse 2
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,adresse[1]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);


	//addresse 3
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,adresse[2]);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, 0x00);

	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);


	for(int i=0;i<dataLength-1;i++){
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, 0x00);

		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		data[i]=SPI_I2S_ReceiveData(SPI1);

	}
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	data[dataLength-1]=SPI_I2S_ReceiveData(SPI1);

	while ((readStatusRegister_1() & 1) != 0) ;

	desactiverChipSelect();

}


/*
 * Présente des soucis à lire 4096 byte d'un coup, à revoir
 */
void ecrireByte(uint8_t adresse[3], uint8_t data)
{

	uint8_t  adresseDataAInserer[3];
	adresseDataAInserer[0]=adresse[0];
	adresseDataAInserer[1]=adresse[1];
	adresseDataAInserer[2]=adresse[2];

	//int secteur = (adresseInt / 4096) * 4096;
	// Debug.Print(secteur.ToString() + " " + (adresseInt / 4096).ToString());
	uint8_t  adresseSecteur[3];
	adresseSecteur[0] = adresse[0];
	//adresseSecteur[1] = adresse[1];
	adresseSecteur[1] = (adresseSecteur[1] & 0xf0);
	adresseSecteur[2] = 0x00;

	uint8_t   contenuSecteur [4096];

	uint8_t temp [1365];
	int adresseSecteurInt;
	adresseSecteurInt=toInt(adresseSecteur);
	for (int i=0;i<3;i++){
		readDataByte(adresseSecteur, temp,1365);
		for(int y=0;y<1365;y++){
			contenuSecteur[y+i*1365]=temp[y];
		}

		adresseSecteurInt+=1365;
		toOctet(adresseSecteurInt,adresseSecteur);
	}
	adresseSecteur[0] = adresse[0];
	//adresseSecteur[1] = adresse[1];
	adresseSecteur[1] = (adresseSecteur[1] & 0xf0);
	adresseSecteur[2] = 0x00;


	SectorErase(adresseSecteur);

	//on met la data dans le tableau de donnése
	//adresse du début de secteur

	// prendre l'adresse de la data en gardant les 12 bits de droite
	int adresseDonne =((adresseDataAInserer[1] & 0x0f)<< 8) + adresseDataAInserer[2];

	contenuSecteur[adresseDonne]=data;

	uint8_t donnee[256];
	uint8_t adresseDonnee[3];

	adresseDonnee[0] = adresseSecteur[0];
	adresseDonnee[1]=adresseSecteur[1];
	adresseDonnee[2] = 0x00;

	//on remet les données dans le secteur par paquet de 256 byte
	for (int i = 0; i < 4096; i = i + 256)
	{
		for (int y = 0; y < 256; y++)
		donnee[y] = contenuSecteur[i+y];

		pageProgram(adresseDonnee,donnee,256);
		adresseDonnee[1]=adresseDonnee[1]+0x01;
	}

}


void WriteExtMemorie(uint8_t donnee, uint8_t adresse[3]){
	ecrireByte(adresse,donnee);
}


char ReadExtMemorie(uint8_t adresse[3]){
	return readDataByte(adresse);
}
