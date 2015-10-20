
#include "device/GPIO.h"
#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIO::Pin::Pin( GPIO& gpio, const unsigned id, const char* name, const uint16_t mask )
   : Device( name ), _gpio( gpio ), _id( id ), _mask( mask )
{ ; }


GPIO::Pin::~Pin()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

GPIO::Pin& GPIO::Pin::init( void )
{
   return *this;
}


GPIO::Pin& GPIO::Pin::enable( bool silent )
{
   if( _incRef() == 0 )
      _gpio.enable( silent );

   return *this;
}


GPIO::Pin& GPIO::Pin::disable( bool silent )
{
   if( _decRef() == 0 )
      _gpio.disable( silent );

   return *this;
}


GPIO::Pin& GPIO::Pin::on( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRL = (uint16_t)( _mask & 0xffff );

   return *this;
}


GPIO::Pin& GPIO::Pin::off( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRH = (uint16_t)( _mask & 0xffff );

   return *this;
}


GPIO::Pin& GPIO::Pin::toggle( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->ODR ^= (uint16_t)( _mask & 0xffff );

   return *this;
}


bool GPIO::Pin::read( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   return ( GPIOx->IDR & _mask ) != 0;
}


GPIO::Pin& GPIO::Pin::mode( Mode mode )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->MODER;
   tmp32 &= ~( 0x03 << ( _id * 2 ));
   tmp32 |=  ( mode << ( _id * 2 ));

   GPIOx->MODER = tmp32;

   return *this;
}


GPIO::Pin& GPIO::Pin::alt( Alt alt )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   mode( ALTERNATE );

   tmp32  = GPIOx->AFR[ _id >> 3 ];
   tmp32 &= ~( 0x0f << (( _id & 0x07 ) * 4 ));
   tmp32 |=  ( alt  << (( _id & 0x07 ) * 4 ));

   GPIOx->AFR[ _id >> 3 ] = tmp32;

   return *this;
}


GPIO::Pin& GPIO::Pin::oSpeed( OSpeed speed )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OSPEEDR;
   tmp32 &= ~( 0x03  << ( _id * 2 ));
   tmp32 |=  ( speed << ( _id * 2 ));

   GPIOx->OSPEEDR = tmp32;

   return *this;
}


GPIO::Pin& GPIO::Pin::oType( OType type )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OTYPER;
   tmp32 &= ~( 0x01 << _id );
   tmp32 |=  ( type << _id );

   GPIOx->OTYPER = tmp32;

   return *this;
}


GPIO::Pin& GPIO::Pin::PuPd( PullUpDn pud )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->PUPDR;
   tmp32 &= ~( 0x03 << ( _id * 2 ));
   tmp32 |=  ( pud  << ( _id * 2 ));

   GPIOx->PUPDR = tmp32;

   return *this;
}

/*EoF*/
