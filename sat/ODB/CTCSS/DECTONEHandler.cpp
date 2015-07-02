
#include "DECTONEHandler.h"

using namespace qb50;


DECTONEHandler::DECTONEHandler(xSemaphoreHandle &ctcssLock) : _ctcssLock(ctcssLock)
{
    _ctcssLock = xSemaphoreCreateMutex();
}


DECTONEHandler::~DECTONEHandler()
{
    vSemaphoreDelete( _ctcssLock );
}


 void DECTONEHandler::handle( EXTI::EXTIn )
{
    //xSemaphoreTake( _dectoneLock, WAIT1MN ); //xxx ctcss class

    //EXTI1.registerHandler( PA8, this );
    portBASE_TYPE ph = pdFALSE;

    xSemaphoreGiveFromISR( _ctcssLock, &ph);

    if ( ph == pdTRUE )
    {
        portEND_SWITCHING_ISR( ph );
    }
}
