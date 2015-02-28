#include "debug.h"
#include "usart.h"



void writeDebug(char* Phrase,int nbCaractere){

	for(int i=0;i<nbCaractere;i++)
		envoyerDataUSART6(Phrase[i]);
}

void InitSerialPortDebug(){

	initialiserUSART6();
}
