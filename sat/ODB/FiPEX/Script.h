#ifndef CSCRIPT_H
#define CSCRIPT_H

#include "system/qb50.h"

#include <stdlib.h>
#include <stdio.h>

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
	CScript(const char *commandSequence,int taille,typeScript type);
	~CScript();
	//bool getCommande(int &i,int &j,uint8_t &commandId, uint8_t data[], uint8_t &taille, uint8_t delay[2]);
	bool getCommande(uint8_t &idCommand, uint8_t data[], uint8_t &taille, uint8_t delay[2]);
private:
	bool getCommandeBinaire(uint8_t &idCommand, uint8_t data[], uint8_t &taille, uint8_t delay[2]);
	bool getCommandeASCII(uint8_t &idCommand, uint8_t data[], uint8_t &taille, uint8_t delay[2]);
};

#endif

