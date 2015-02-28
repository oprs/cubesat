#ifndef CCAPTEURCURRENT_H
#define CCAPTEURCURRENT_H

#include "adc.h"

class CCapteurCurrent
{
	private:
		CAdc *m_adc;
		channel m_canal;
 	public:
	 	CCapteurCurrent(CAdc * adc, channel canal);
	 	~CCapteurCurrent();
	 	int getCurrent();
};

#endif

