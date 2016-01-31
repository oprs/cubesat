
#include "STM32/STM32_ADC.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_ADC::Channel::Channel( STM32_ADC& adc, const char *name, ChId id, STM32_GPIO::Pin& pin )
: Device( name ), ADC::Channel( adc ), _id( id ), _pin( pin )
{ ; }


STM32_ADC::Channel::~Channel()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

STM32_ADC::Channel&
STM32_ADC::Channel::init( void )
{
 //_adc.init();
   return *this;
}


STM32_ADC::Channel&
STM32_ADC::Channel::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _pin.pullUp()
       .mode( STM32_GPIO::ANALOG );

 //_adc.enable( silent )
   STM32_ADC& adc = static_cast<STM32_ADC&>( _adc );
   adc.enable( silent );

   return *this;
}


STM32_ADC::Channel&
STM32_ADC::Channel::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

 //_adc.disable( silent )
   STM32_ADC& adc = static_cast<STM32_ADC&>( _adc );
   adc.disable( silent );

   return *this;
}

/*EoF*/
