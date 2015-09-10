
#include "system/qb50.h"

#include "DECTONEHandler.h"
#include "CTCSS.h"

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
    portBASE_TYPE ph = pdFAIL;

    xSemaphoreGiveFromISR( _ctcssLock, &ph);

    if ( ph == pdPASS )
    {
        portEND_SWITCHING_ISR( ph );
    }

}
