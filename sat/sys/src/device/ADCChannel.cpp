
#include "device/ADCChannel.h"
#include "system/qb50.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADCChannel::ADCChannel( MAX111x& adc,
                        MAX111x::Channel chan,
                        const char *name,
                        float mul )
	: _adc( adc ),
	  _chan( chan ),
	  _name( name ),
	  _mul( mul )
{ enable(); }


ADCChannel::~ADCChannel()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ADCChannel& ADCChannel::enable( void )
{ return *this; }


ADCChannel& ADCChannel::disable( void )
{ return *this; }


float ADCChannel::read( void )
{
	int raw = _adc.readChannel( _chan );

	return _mul * raw;
}

/*EoF*/
