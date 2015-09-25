
#include "device/GPIOPin.h"
#include "system/Logger.h"

#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

GPIOPin::GPIOPin( GPIO& gpio, const unsigned id, const char* name, const uint16_t mask )
   : Device( name ), _gpio( gpio ), _id( id ), _mask( mask )
{ ; }


GPIOPin::~GPIOPin()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

GPIOPin& GPIOPin::init( void )
{
   //LOG << _name << ": GPIO pin at " << _gpio.name();
   return *this;
}


GPIOPin& GPIOPin::enable( void )
{
   if( _incRef() == 0 )
      _gpio.enable();

   //LOG << _name << ": enabled";

   return *this;
}


GPIOPin& GPIOPin::disable( void )
{
   if( _decRef() == 0 ) {
      //LOG << _name << ": disabled";
      _gpio.disable();
   }

   return *this;
}


GPIOPin& GPIOPin::on( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRL = (uint16_t)( _mask & 0xffff );

   return *this;
}


GPIOPin& GPIOPin::off( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->BSRRH = (uint16_t)( _mask & 0xffff );

   return *this;
}


GPIOPin& GPIOPin::toggle( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   GPIOx->ODR ^= (uint16_t)( _mask & 0xffff );

   return *this;
}


bool GPIOPin::read( void )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   return ( GPIOx->IDR & _mask ) != 0;
}


GPIOPin& GPIOPin::mode( Mode mode )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->MODER;
   tmp32 &= ~( 0x03 << ( _id * 2 ));
   tmp32 |=  ( mode << ( _id * 2 ));

   GPIOx->MODER = tmp32;

   return *this;
}


GPIOPin& GPIOPin::alt( Alt alt )
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


GPIOPin& GPIOPin::oSpeed( OSpeed speed )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OSPEEDR;
   tmp32 &= ~( 0x03  << ( _id * 2 ));
   tmp32 |=  ( speed << ( _id * 2 ));

   GPIOx->OSPEEDR = tmp32;

   return *this;
}


GPIOPin& GPIOPin::oType( OType type )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OTYPER;
   tmp32 &= ~( 0x01 << _id );
   tmp32 |=  ( type << _id );

   GPIOx->OTYPER = tmp32;

   return *this;
}


GPIOPin& GPIOPin::PuPd( PullUpDn pud )
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
