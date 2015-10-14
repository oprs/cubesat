
#include "config.h"
#include "CTCSS.h"
#include "DECTONEHandler.h"
#include <stdio.h>


using namespace std;
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



void CTCSSThread( Thread *self )
{
    (void)self;

    LED1.enable().out().off();
    LED2.enable().out().off();
    LED3.enable().out().off();
    LED4.enable().out().off();

    PB12.enable().out().on();   // CTCSS_ON
    PB13.enable().out().off(); // ON/OFF_PA
    PB15.enable().out().off(); // ON/OFF_TX

    CTCSS ctcss( PB15, PB13 );

    for( ;; )
    {
        ctcss.enable();
        ctcss.modeRelaisFM();
        ctcss.disable();

        //LED3.toggle();
        //LED1.on();
        delay( 100 );
    }

}
