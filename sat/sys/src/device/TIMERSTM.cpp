#include "device/TIMERSTM.h"

using namespace qb50;

TIMER::TIMER(Bus& bus,
             const uint32_t iobase,
             const uint32_t periph,
             GPIOPin& pin,
             GPIOPin::Alt alt)
             :BusDevice( bus, iobase, periph),
             _pin( pin ),
             _alt( alt ) {}

TIMER::~TIMER()
{
    disable();
}

//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //


TIMER& TIMER::enable( void )
{
    _pin.enable()
        .pullUp()
        .alt(_alt);

    bus.enable(this);

    return *this;
}

TIMER& TIMER::disable( void )
{
    bus.disable( this );

    _pin.disable();

    return *this;
}
