
#include "device/GPIO.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIO::GPIO( Bus& bus, const uint32_t iobase, const uint32_t periph, const unsigned id, GPIOPin *pins )
	: BusDevice( bus, iobase, periph ), _id( id ), _pins( pins )
{ ; }


GPIO::~GPIO()
{ disable(); }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

GPIO& GPIO::enable( void )
{
	bus.enable( this );
	return *this;
}


GPIO& GPIO::disable( void )
{
	//bus.disable( this );
	return *this;
}

/*EoF*/
