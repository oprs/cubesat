
#include "device/GPIOPin.h"
#include "device/GPIO.h"

#include <stm32f4xx.h>

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


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

GPIOPin& GPIOPin::reset( void )
{
/*
   _gpio.enable();

   mode   (    INPUT );
   oSpeed (     SLOW );
   oType  ( PUSHPULL );
   PuPd   (   NOPULL );

   _gpio.disable();
*/
   return *this;
}


GPIOPin& GPIOPin::enable( void )
{
   _gpio.enable();
   return *this;
}


GPIOPin& GPIOPin::disable( void )
{
   _gpio.disable();
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


GPIOPin& GPIOPin::mode( Mode mode )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->MODER;
   tmp32 &= ~( GPIO_MODER_MODER0 << ( _id * 2 ));
   tmp32 |=  ( mode              << ( _id * 2 ));

   GPIOx->MODER = tmp32;

   return *this;
}


GPIOPin& GPIOPin::alt( Alt alt )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->AFR[ _id >> 3 ];
   tmp32 &= ~( 0x07 << ( _id * 4 ));
   tmp32 |=  ( alt  << ( _id * 4 ));

   GPIOx->AFR[ _id >> 3 ] = tmp32;
   mode( ALTERNATE );

   return *this;
}


GPIOPin& GPIOPin::oSpeed( OSpeed speed )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OSPEEDR;
   tmp32 &= ~( GPIO_OSPEEDER_OSPEEDR0 << ( _id * 2 ));
   tmp32 |=  ( speed                  << ( _id * 2 ));

   GPIOx->OSPEEDR = tmp32;

   return *this;
}


GPIOPin& GPIOPin::oType( OType type )
{
   GPIO_TypeDef *GPIOx = (GPIO_TypeDef*)_gpio.iobase;
   register uint32_t tmp32;

   tmp32  = GPIOx->OTYPER;
   tmp32 &= ~( GPIO_OTYPER_OT_0 << _id );
   tmp32 |=  ( type             << _id );

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
