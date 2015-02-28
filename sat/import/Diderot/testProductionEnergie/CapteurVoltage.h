#ifndef CCAPTEURVOLTAGE_H
#define CCAPTEURVOLTAGE_H
#include "adc.h"

class CCapteurVoltage
{
	private:
		CAdc *m_adc;
		channel m_canal;
	public :
		CCapteurVoltage(CAdc * adc, channel canal);
		~CCapteurVoltage();
        int getVoltage();

};

#endif






