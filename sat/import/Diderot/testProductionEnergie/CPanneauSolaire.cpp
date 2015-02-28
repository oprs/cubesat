#include "CPanneauSolaire.h"

CPanneauSolaire::CPanneauSolaire(configPanneausolaire config)
{
	m_capteurCurrent = new CCapteurCurrent(config.adc,config.canalI);
	m_capteurTemperature = new CCapteurTemperature (config.adc, config.canalT);
	m_capteurVoltage = 	new CCapteurVoltage ( config.adc, config.canalV);


}

CPanneauSolaire::~CPanneauSolaire()
{

}



int CPanneauSolaire::getVoltage()
{
	return m_capteurVoltage->getVoltage();
}


int CPanneauSolaire::getCurrent()
{
	return m_capteurCurrent->getCurrent();
}


int CPanneauSolaire::getTemperature()
{
	return m_capteurTemperature->getTemperature();
}

void CPanneauSolaire::getStatus(statusPanneauSolaire &status)
{
	status.current = getCurrent();
	status.voltage = getVoltage();
	status.temperature = getTemperature();
}

