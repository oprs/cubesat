#include "CapteurCurrent.h"


CCapteurCurrent::CCapteurCurrent(CAdc *adc,channel canal )
{
	m_adc = adc;
	m_canal=canal;
}

CCapteurCurrent::~CCapteurCurrent()
{

}

int CCapteurCurrent::getCurrent()
{
	return m_adc->read(m_canal);
}
