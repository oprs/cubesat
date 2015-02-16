
#include "stm32f4xx_rcc.h"
#include "device/GPIOPin.h"
#include "device/GPIO.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIOPin::GPIOPin( GPIO& gpio, const unsigned id, const uint16_t mask )
   : _gpio( gpio ), _id( id ), _mask( mask )
{
   reset();
}


GPIOPin::~GPIOPin()
{ reset(); }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void GPIOPin::reset( void )
{
   _mode  = GPIO_Mode_IN;
   _speed = GPIO_Speed_2MHz;
   _oType = GPIO_OType_PP;
   _PuPd  = GPIO_PuPd_NOPULL;
   _alt   = 0;
}


void GPIOPin::enable( void )
{ /* parent.enable( this ); */ }


void GPIOPin::disable( void )
{ /* parent.disable( this ); */ }


void GPIOPin::mode( GPIOMode_TypeDef mode )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   if( mode != _mode ) {
      _mode  = mode;

      tmp32  = GPIOx->MODER;
      tmp32 &= ~( GPIO_MODER_MODER0 << ( _id * 2 ));
      tmp32 |=  ( _mode             << ( _id * 2 ));

      GPIOx->MODER = tmp32;
   }
}


void GPIOPin::speed( GPIOSpeed_TypeDef speed )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   if(( speed != _speed ) && (( _mode == GPIO_Mode_OUT ) || ( _mode == GPIO_Mode_AF ))) {
      _speed = speed;

      tmp32  = GPIOx->OSPEEDR;
      tmp32 &= ~( GPIO_OSPEEDER_OSPEEDR0 << ( _id * 2 ));
      tmp32 |=  ( _speed                 << ( _id * 2 ));

      GPIOx->OSPEEDR = tmp32;
   }
}


void GPIOPin::oType( GPIOOType_TypeDef oType )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   if(( oType != _oType ) && (( _mode == GPIO_Mode_OUT ) || ( _mode == GPIO_Mode_AF ))) {
      _oType = oType;

      tmp32  = GPIOx->OTYPER;
      tmp32 &= ~( GPIO_OTYPER_OT_0 << _id );
      tmp32 |=  ( _oType           << _id );

      GPIOx->OTYPER = tmp32;
   }
}


void GPIOPin::PuPd( GPIOPuPd_TypeDef PuPd )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   if( PuPd != _PuPd ) {
      _PuPd = PuPd;

      tmp32  = GPIOx->PUPDR;
      tmp32 &= ~( GPIO_PUPDR_PUPDR0 << ( _id * 2 ));
      tmp32 |=  ( _PuPd             << ( _id * 2 ));

      GPIOx->PUPDR = tmp32;
   }
}


void GPIOPin::alt( unsigned alt )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   if( alt != _alt ) {
      _alt = alt;

      tmp32  = GPIOx->AFR[ _id >> 3 ];
      tmp32 &= ~( 0x07 << ( _id * 4 ));
      tmp32 |=  ( _alt << ( _id * 4 ));

      GPIOx->AFR[ _id >> 3 ] = tmp32;
   }
}


void GPIOPin::on( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRL = (uint16_t)( _mask & 0xffff );
}


void GPIOPin::off( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRH = (uint16_t)( _mask & 0xffff );
}


void GPIOPin::toggle( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->ODR ^= (uint16_t)( _mask & 0xffff );
}


/*EoF*/
