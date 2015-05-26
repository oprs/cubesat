#ifndef CSCRIPT_H
#define CSCRIPT_H
#include "SerialPort.h"
#include <stdlib.h>

enum typeScript
{
	binaire=0,
	ascii=1,
};

class CScript
{
private:
	typeScript m_type;
	int m_position;
	char *m_posDebutCommande;
	char *m_bCommande;
	int m_taille;
public:
	CScript(char *commandSequence,int taille,typeScript type);
	~CScript();
	//bool getCommande(int &i,int &j,byte &commandId, byte data[], byte &taille, byte delay[2]);
	bool getCommande(byte &idCommand, byte data[], byte &taille, byte delay[2]);
private:
	bool getCommandeBinaire(byte &idCommand, byte data[], byte &taille, byte delay[2]);
	bool getCommandeASCII(byte &idCommand, byte data[], byte &taille, byte delay[2]);
};

#endif

