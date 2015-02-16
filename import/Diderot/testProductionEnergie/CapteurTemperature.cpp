#include "CapteurTemperature.h"

CCapteurTemperature::CCapteurTemperature(CAdc *adc,channel canal)
{
	m_adc = adc;
	m_canal=canal;
}

CCapteurTemperature::~CCapteurTemperature()
{

}

int CCapteurTemperature::getTemperature()
{
	return m_adc->read(m_canal);
}

