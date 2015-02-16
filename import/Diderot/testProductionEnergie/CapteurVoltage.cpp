#include "CapteurVoltage.h"

CCapteurVoltage::CCapteurVoltage(CAdc *adc,channel canal)
{
	m_adc = adc;
	m_canal=canal;
}

CCapteurVoltage::~CCapteurVoltage()
{

}

int CCapteurVoltage::getVoltage()
{
	return m_adc->read(m_canal);
}

