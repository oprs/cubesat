#ifndef CPRODUCTEURENERGIE_H
#define CPRODUCTEURENERGIE_H
#include "CPanneauSolaire.h"
#include "spi.h"
#include "adc.h"
#include "batterie.h"

class CProducteurEnergie
{
	private:
		CSpi m_spi;		//SPI3 pinpacks1
		CAdc m_adc1;	//CS
		CAdc m_adc2;	//CS
		CPanneauSolaire m_panneauSolaire1;
		CPanneauSolaire m_panneauSolaire2;
		CPanneauSolaire m_panneauSolaire3;
		CPanneauSolaire m_panneauSolaire4;

		Cbatterie m_batterie1;
		Cbatterie m_batterie2;
	public:
		CProducteurEnergie();
		~CProducteurEnergie();
    	void getStatus();

};

#endif
