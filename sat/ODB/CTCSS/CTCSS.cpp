
#include "CTCSS.h"
#include "DECTONEHandler.h"

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


CTCSS::CTCSS( GPIOPin& txPin, GPIOPin& paPin ): _txPin(txPin), _paPin(paPin)
{
    temp_PA14[0] = 73; //valeur initiale commande PA14
    temp_PA15[0] = 60; //valeur initiale commande PA15

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

    _ctcssLock = xSemaphoreCreateMutex();

    _handle = new DECTONEHandler(_ctcssLock);
    EXTI1.registerHandler( PA8, _handle );

}


CTCSS::~CTCSS()
{
    disable();
}


CTCSS& CTCSS::enable( void )
{
    _txPin.enable().in().off();
    _paPin.enable().in().off();

    return *this;
}


CTCSS& CTCSS::disable( void )
{
    return *this;
}


void CTCSS::modeRelaisFM()
{
    PB12.on();

    //TickType_t ms = 10000 / portTICK_RATE_MS;

    int rv = xSemaphoreTake( _ctcssLock, portMAX_DELAY );

    _txPin.on();
    _paPin.on();
     LED2.toggle();
return;
    int T_PA = 0;


        for( int k = 0; k < 20; k++ )
         {
             for( int i = 1; i <= 8; i++ )
             {
                if( T_PA == temp_PA14[i] )
                {
                    if( T_PA > T_PA_MAX )
                    {
                        do {
                            _txPin.off();

                        } while ( T_PA > T_PA_MIN );

                        return;
                    }
                }
             }


            for( int j = 1; j <= 6; j++ )
            {
                if( T_PA == temp_PA15[j] )
                {
                    if( T_PA < T_PA_MIN )
                        return;
                }
            }

            delay( 1000 );

         }

}
