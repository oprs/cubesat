#include <stm32f4xx_spi.h>

void readDeviceIdentification(uint8_t resultat[3]);

uint8_t readStatusRegister_1();
uint8_t readStatusRegister_2();
void writeStatusRegister();
void writeStatusRegister(uint8_t register1, uint8_t register2);
uint8_t readDataByte(uint8_t adresse[3]);

/*
 * met la donn�e data dans adresse
 */
void pageProgram(uint8_t adresse[3],uint8_t data);
/*
 * met les donn�es du tableau data (contenant dataLength) dans la m�moire � partir de adresse
 */
void pageProgram(uint8_t adresse[3],uint8_t data[],int dataLength);

/*
 * met � 1 l'ensemble des bits du secteur commen�ant � adresse
 */
void SectorErase(uint8_t adresse[3]);
/*
 * Met � 1 l'ensemble des bits de la m�moire
 */
void chipErase();
/*
 * Renvoi dans le tableau data, dataLength donn�es de la m�moire � partir d'adresse
 */
void readDataByte(uint8_t adresse[3],uint8_t data[],int dataLength);
void ecrireByte(uint8_t adresse[3], uint8_t data);

void WriteExtMemorie(uint8_t donnee, uint8_t adresse[3]);

char ReadExtMemorie(uint8_t adresse[3]);
