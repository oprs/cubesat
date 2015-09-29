
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
   : Device( name ),
     _adc( adc ),
     _chan( chan ),
     _mul( mul )
{ ; }


ADCChannel::~ADCChannel()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ADCChannel& ADCChannel::init( void )
{ return *this; }


ADCChannel& ADCChannel::enable( bool silent )
{
   (void)silent;
   return *this;
}


ADCChannel& ADCChannel::disable( bool silent )
{
   (void)silent;
   return *this;
}


float ADCChannel::read( void )
{
   int raw = _adc.readChannel( _chan );

   return _mul * raw;
}

/*EoF*/
