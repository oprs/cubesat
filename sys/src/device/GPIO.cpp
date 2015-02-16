
#include "stm32f4xx_rcc.h"
#include "device/GPIO.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIO::GPIO( Bus& bus, const uint32_t periph, const uint32_t iobase, GPIOPin *pin )
   : CoreDevice( bus, periph, iobase ), pin( pin )
{
   reset();
}


GPIO::~GPIO()
{ reset(); }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void GPIO::reset( void )
{ ; }


void GPIO::enable( void )
{ bus.enable( this ); }


void GPIO::disable( void )
{ bus.disable( this ); }


/*EoF*/
