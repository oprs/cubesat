
#include "devices.h"

#include "CTCSS.h"
#include "DECTONEHandler.h"
#include "STM32/STM32_EXTI.h"

using namespace qb50;

#if 0
 #define LED1 PD12
 #define LED2 PD13
 #define LED3 PD14
 #define LED4 PD15
#else
 #define LED1 PC5
 #define LED2 PB0
 #define LED3 PB1
 #define LED4 PA1
#endif




CTCSS::CTCSS( STM32_GPIO::Pin& txPin, STM32_GPIO::Pin& paPin ): _txPin(txPin), _paPin(paPin)
{
    //initialisation temperature commande PA14
    temp_PA14[0] = 73;

    //initialisation temperature commande PA15
    temp_PA15[0] = 60;

    // Parametrage T_PA_MAX
    for( int i = 1; i <= 8; i++ )
    {
        temp_PA14[i] = temp_PA14[i-1] + 2;
    }

    // Parametrage T_PA_MIN
    for( int j = 1; j <= 6; j++ )
    {
        temp_PA15[j] = temp_PA15[j-1] + 2;
    }

    _ctcssRise = xSemaphoreCreateMutex();
    _ctcssFall = xSemaphoreCreateMutex();

    _handleFall = new DECTONEHandler( _ctcssFall );
    EXTI.registerHandler( PA8, _handleFall, STM32_EXTI::FALLING );

    _handleRise = new DECTONEHandler( _ctcssRise );
    EXTI.registerHandler( PA8, _handleRise, STM32_EXTI::RISING );


}


CTCSS::~CTCSS()
{
    disable();
    vSemaphoreDelete( _ctcssRise );
    vSemaphoreDelete( _ctcssFall );
}


CTCSS& CTCSS::enable( void )
{
    _txPin.out().off();
    _paPin.out().off();

    return *this;
}


CTCSS& CTCSS::disable( void )
{
    return *this;
}


void CTCSS::modeRelaisFM()
{

    //TickType_t WAIT_10S = 10000 / portTICK_RATE_MS;
    TickType_t WAIT_1S = 1000 / portTICK_RATE_MS;

    int vp = xSemaphoreTake( _ctcssRise, /*WAIT_10S*/portMAX_DELAY );
    PA8.read();
    if ( vp == pdPASS )
    {

        //printf( "------------------------------------\r\n" );

        if( PA8.read() == true )

        {

            for( int k = 0; k < 20; k++ )
            {

                MAX111x::Sample T_PA;

                (void)ADC3CH7.read( &T_PA );
                T_PA.value -= 273;

                //printf( "%d\r\n", T_PA );
                //printf("%d\r\n", PA8.read());
                /*delay( 1000 );
                }
                return;*/


                if( PA8.read() == false )
                {
                    _paPin.off();
                    _txPin.off();
                    LED2.off();
                    return;
                }

                for( int i = 1; i <= 8; i++ )
                {
                    /*if( T_PA == temp_PA14[i] )
                    {*/
                        //temp_PA14[i];

                        if( T_PA.value > T_PA_MAX )
                        {
                            _paPin.off();
                            _txPin.off();
                            LED2.off();

                            if( T_PA.value >= T_PA_MIN)
                            {
                                _paPin.off();
                                _txPin.off();
                                LED2.off();
                            }

                            return;
                        }
                    //}
                }


                for( int j = 1; j <= 6; j++ )
                {
                    /*if( T_PA == temp_PA15[j] )
                    {*/
                    //temp_PA15[j];

                    //}
                }

                LED2.on(); // XXX
                _txPin.on();
                _paPin.on();
                //delay(1000);
                xSemaphoreTake( _ctcssFall, WAIT_1S );

            }

            _paPin.off();
            _txPin.off();
            LED2.off();
        }
    }
}
