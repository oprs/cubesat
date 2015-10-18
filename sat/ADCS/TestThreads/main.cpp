
#include "config.h"

using namespace qb50;

void testThreadADC()
{
    int i;

    STM32_ADC::Channel* ch[9] = { &SUN1, &SUN2, &SUN3, &SUN4, &SUN5, &SUN6, &SUN7, &SUN8, &SUN9 };

    for( i = 0 ; i < 9 ; ++i )
        ch[i]->enable();

    for( ;; ) {
        LOG << "------- ADC Test Thread -------";
        LOG << "[DATA ADC]";

        for( i = 0 ; i < 9 ; ++i )
            Current_state.TADC.adc_temp[i] = ch[i]->read();

        LOG << "SUN sensors: [ " << Current_state.TADC.adc_temp[0] << ", "
                                 << Current_state.TADC.adc_temp[1] << ", "
                                 << Current_state.TADC.adc_temp[2] << ", "
                                 << Current_state.TADC.adc_temp[3] << ", "
                                 << Current_state.TADC.adc_temp[4] << ", "
                                 << Current_state.TADC.adc_temp[5] << ", "
                                 << Current_state.TADC.adc_temp[6] << ", "
                                 << Current_state.TADC.adc_temp[7] << ", "
                                 << Current_state.TADC.adc_temp[8] << " ]"
        ;

        delay(5000);
    }
}

void TestThreads( Thread *self)
{
    (void)self;
    testThreadADC();
}

/*EoF*/
