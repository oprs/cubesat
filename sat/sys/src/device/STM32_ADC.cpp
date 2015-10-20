
#include "device/RstClk.h"
#include "device/STM32_ADC.h"
#include "system/Logger.h"

#include <stm32f4xx_adc.h>

#undef ADC
#undef RCC

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_ADC::STM32_ADC( Bus& bus,
                      const uint32_t iobase,
                      const uint32_t periph,
                      const char    *name )
   : ADC( name ), BusSlave( bus, iobase, periph )
{
   _numConv = 5;
}


STM32_ADC::~STM32_ADC()
{ ; }


//  - - - - - - - - - - - - - - -  //
//  C H A N N E L   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

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

   _pin.enable( silent ).pullUp()
       .mode( GPIO::Pin::ANALOG );

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

   _pin.disable( silent );

   return *this;
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_ADC& STM32_ADC::init( void )
{
   ADC::init();
   LOG << _name << ": STM32 ADC at " << bus.name;

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void STM32_ADC::_enable( IOReq_enable *req )
{
   if( _incRef() > 0 )
      return;

   (void)req;

   RCC.enable( this, req->_silent );

   ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;

   ADCx->CR1 = 0; //Set resolution for the ADC
   uint32_t tmpreg = 0;
   tmpreg = ADCx->CR2;
   tmpreg &= ((uint32_t)0xC0FFF7FD);  //CR2_CLEAR_MASK
   tmpreg |= 0 << 1;
   ADCx->CR2 = tmpreg; //Sets the continuous conversion mode

   tmpreg = ADCx->SQR1;

   tmpreg &= ((uint32_t)0xFF0FFFFF); //SQR1_L_RESET

   //This sets the number of conversions to perform
   //Corresponds to the number of sun sensors on board
   //
   tmpreg |= (uint32_t)(_numConv-1) << 20;

   ADCx->SQR1 = tmpreg;
   ADCx->CR2 |= ADC_CR2_ADON;

   if( !req->_silent )
      LOG << _name << ": enabled";
}


void STM32_ADC::_disable( IOReq_disable *req )
{
   if( _decRef() > 0 )
      return;

   (void)req;

   ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;
   ADCx->CR2 &= ~ADC_CR2_ADON;

   RCC.disable( this, req->_silent );

   if( !req->_silent )
      LOG << _name << ": disabled";
}

#if 0
//Rather than modifying individual registers we just use the code written for the ADC using the stm32f4 peripheral library
adcval_t STM32_ADC::getValue_adc()
{
   adcval_t adc_val = 0;
   ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;
   ADC_RegularChannelConfig(ADCx, 0, 1, ADC_SampleTime_15Cycles);
   ADC_SoftwareStartConv(ADCx);
   //(void)ADC_ClearFlag(ADCx, ADC_FLAG_EOC);

   while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET){;}
   adc_val = ADC_GetConversionValue(ADCx);
   return adc_val;
}
#endif

void STM32_ADC::_read( IOReq_read *req )
{
   STM32_ADC::Channel& ch = static_cast<STM32_ADC::Channel&>( req->_ch );

   ADC_TypeDef *ADCx = (ADC_TypeDef*)iobase;
   ADC_RegularChannelConfig(ADCx, ch._id, 1, ADC_SampleTime_15Cycles);
   ADC_SoftwareStartConv(ADCx);
   //(void)ADC_ClearFlag(ADCx, ADC_FLAG_EOC);

   while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET){;}
   req->_rv = ADC_GetConversionValue(ADCx);
}

/*EoF*/