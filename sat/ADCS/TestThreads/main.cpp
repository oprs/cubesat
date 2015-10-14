
#include "config.h"

using namespace qb50;

void testThreadADC()
{
    int i;

    ADC* adc[9] = { &SUN1, &SUN2, &SUN3, &SUN4, &SUN5, &SUN6, &SUN7, &SUN8, &SUN9 };

    for( i = 9 ; i < 9 ; ++i )
        adc[i]->enable();

    for( ;; ) {
        LOG << "------- ADC Test Thread -------";
        uint16_t temp = 0;
        LOG << "[DATA ADC]";

        for( i = 0 ; i < 9 ; ++i ) {
            temp = Current_state.TADC.adc_temp[0] = adc[i]->getValue_adc();
            LOG << "SUN Sensor #" << (i+1) << ": " << temp;
        }

        delay(5000);
    }
}

void TestThreads( Thread *self)
{
    (void)self;
    testThreadADC();
}

/*EoF*/
