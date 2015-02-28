#include <stm32f4xx_spi.h>

void readDeviceIdentification(uint8_t resultat[3]);

uint8_t readStatusRegister_1();
uint8_t readStatusRegister_2();
void writeStatusRegister();
void writeStatusRegister(uint8_t register1, uint8_t register2);
uint8_t readDataByte(uint8_t adresse[3]);

/*
 * met la donnée data dans adresse
 */
void pageProgram(uint8_t adresse[3],uint8_t data);
/*
 * met les données du tableau data (contenant dataLength) dans la mémoire à partir de adresse
 */
void pageProgram(uint8_t adresse[3],uint8_t data[],int dataLength);

/*
 * met à 1 l'ensemble des bits du secteur commençant à adresse
 */
void SectorErase(uint8_t adresse[3]);
/*
 * Met à 1 l'ensemble des bits de la mémoire
 */
void chipErase();
/*
 * Renvoi dans le tableau data, dataLength données de la mémoire à partir d'adresse
 */
void readDataByte(uint8_t adresse[3],uint8_t data[],int dataLength);
void ecrireByte(uint8_t adresse[3], uint8_t data);

void WriteExtMemorie(uint8_t donnee, uint8_t adresse[3]);

char ReadExtMemorie(uint8_t adresse[3]);
