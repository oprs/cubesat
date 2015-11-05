
#include "MAX111x/MAX111x.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::Channel::Channel( MAX111x& adc, const char *name, ChId id )
: ADC::Channel( adc, name ), _id( id )
{ ; }


MAX111x::Channel::~Channel()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

MAX111x::Channel&
MAX111x::Channel::init( void )
{
 //_adc.init();
   return *this;
}


MAX111x::Channel&
MAX111x::Channel::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

 //_adc.enable( silent )
   MAX111x& adc = static_cast<MAX111x&>( _adc );
   adc.enable( silent );

   return *this;
}


MAX111x::Channel&
MAX111x::Channel::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

 //_adc.disable( silent )
   MAX111x& adc = static_cast<MAX111x&>( _adc );
   adc.disable( silent );

   return *this;
}

/*EoF*/
