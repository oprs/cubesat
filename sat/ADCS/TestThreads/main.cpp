#include <stdio.h>
#include "system/qb50.h"

using namespace qb50;

void testThreadADC(){
    //Enable the GPIO Pins for ADC Functionality
    SUN1.enable();
    SUN2.enable();
    SUN3.enable();
    SUN4.enable();
    SUN5.enable();

    for( ;; ){
            (void)printf(" ------- ADC Test Thread -------\r\n");
            uint16_t temp = 0;
            (void)printf( "[DATA ADC]\r\n" );

            temp = SUN1.getValue_adc();
            Current_state.TADC.adc_temp[0] = SUN1.getValue_adc();

            (void)printf( "SUN Sensor 1: %u\r \n", temp);

            temp = SUN2.getValue_adc();
            Current_state.TADC.adc_temp[1] = SUN2.getValue_adc();

            (void)printf( "SUN Sensor 2: %u\r\n", temp);

            temp = SUN3.getValue_adc();
            Current_state.TADC.adc_temp[2] = SUN3.getValue_adc();

            (void)printf( "SUN Sensor 3: %u\r\n", temp);

            temp = SUN4.getValue_adc();
            Current_state.TADC.adc_temp[3] = SUN4.getValue_adc();

            (void)printf( "SUN Sensor 4: %u\r\n", temp);

            temp = SUN5.getValue_adc();
            Current_state.TADC.adc_temp[4] = SUN5.getValue_adc();

            (void)printf( "SUN Sensor 5: %u\r\n", temp);

            delay(500);
    }

}

void TestThreads( Thread *self)
{
    (void)self;

    testThreadADC();

}

/*EoF*/
