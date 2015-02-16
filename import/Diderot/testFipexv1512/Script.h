#ifndef CSCRIPT_H
#define CSCRIPT_H
#include "SerialPort.h"

class CScript
{
private:
	bool m_isOpened;
	int m_numScript;
	char m_script[7][400];
public:
	CScript();
	~CScript();
	bool open(byte numScript);
	bool getCommande(int &i,int &j,byte &commandId, byte data[], byte &taille, byte delay[2]);
	bool close();
};

#endif
