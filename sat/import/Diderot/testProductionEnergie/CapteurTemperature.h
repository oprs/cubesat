#ifndef CCAPTEURTEMPERATURE_H
#define CCAPTEURTEMPERATURE_H
#include "adc.h"
class CCapteurTemperature
{
	private:
		CAdc *m_adc;
		channel m_canal;
	public:
		CCapteurTemperature(CAdc * adc, channel canal);
		~CCapteurTemperature();
		int getTemperature();
};

#endif


