#ifndef CPANNEAUSOLAIRE_H
#define CPANNEAUSOLAIRE_H

#include "CapteurCurrent.h"
#include "CapteurTemperature.h"
#include "CapteurVoltage.h"

struct configPanneausolaire
{
	CAdc *adc;
	channel canalI;
	channel canalV;
	channel canalT;
};

struct statusPanneauSolaire
{
	int temperature;
    int voltage;
    int current;
};

class CPanneauSolaire
{
	private :
		CCapteurCurrent *m_capteurCurrent;
		CCapteurTemperature *m_capteurTemperature;
		CCapteurVoltage *m_capteurVoltage;
		statusPanneauSolaire m_status;
    public :
        CPanneauSolaire(configPanneausolaire config);
        ~CPanneauSolaire();
        int getVoltage();
        int getCurrent();
        int getTemperature();
        void getStatus(statusPanneauSolaire &status);
};
#endif
