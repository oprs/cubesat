
#ifndef _QB50_SYS_GPIO_PIN_H
#define _QB50_SYS_GPIO_PIN_H

#include "stm32f4xx_gpio.h"
#include "Device.h"


namespace qb50 {

   class GPIO;

   class GPIOPin : public Device
   {
      public:

         GPIOPin( GPIO& gpio, const unsigned id, const uint16_t mask );
         ~GPIOPin();

         void reset     ( void );
         void enable    ( void );
         void disable   ( void );

         void mode      ( GPIOMode_TypeDef  mode  );
         void in        ( void ) { mode( GPIO_Mode_IN  ); };
         void out       ( void ) { mode( GPIO_Mode_OUT ); };

         void speed     ( GPIOSpeed_TypeDef speed );
         void oType     ( GPIOOType_TypeDef oType );
         void PuPd      ( GPIOPuPd_TypeDef  PuPd  );
         void alt       ( unsigned alt );

         void on        ( void );
         void off       ( void );
         void toggle    ( void );

      private:

         GPIO&             _gpio;
         const unsigned    _id;
         const uint16_t    _mask;

         GPIOMode_TypeDef  _mode;
         GPIOSpeed_TypeDef _speed;
         GPIOOType_TypeDef _oType;
         GPIOPuPd_TypeDef  _PuPd;
         unsigned          _alt;
   };

   extern qb50::GPIOPin& PA0;
   extern qb50::GPIOPin& PA1;
   extern qb50::GPIOPin& PA2;
   extern qb50::GPIOPin& PA3;
   extern qb50::GPIOPin& PA4;
   extern qb50::GPIOPin& PA5;
   extern qb50::GPIOPin& PA6;
   extern qb50::GPIOPin& PA7;
   extern qb50::GPIOPin& PA8;
   extern qb50::GPIOPin& PA9;
   extern qb50::GPIOPin& PA10;
   extern qb50::GPIOPin& PA11;
   extern qb50::GPIOPin& PA12;
   extern qb50::GPIOPin& PA13;
   extern qb50::GPIOPin& PA14;
   extern qb50::GPIOPin& PA15;

   extern qb50::GPIOPin& PB0;
   extern qb50::GPIOPin& PB1;
   extern qb50::GPIOPin& PB2;
   extern qb50::GPIOPin& PB3;
   extern qb50::GPIOPin& PB4;
   extern qb50::GPIOPin& PB5;
   extern qb50::GPIOPin& PB6;
   extern qb50::GPIOPin& PB7;
   extern qb50::GPIOPin& PB8;
   extern qb50::GPIOPin& PB9;
   extern qb50::GPIOPin& PB10;
   extern qb50::GPIOPin& PB11;
   extern qb50::GPIOPin& PB12;
   extern qb50::GPIOPin& PB13;
   extern qb50::GPIOPin& PB14;
   extern qb50::GPIOPin& PB15;

   extern qb50::GPIOPin& PC0;
   extern qb50::GPIOPin& PC1;
   extern qb50::GPIOPin& PC2;
   extern qb50::GPIOPin& PC3;
   extern qb50::GPIOPin& PC4;
   extern qb50::GPIOPin& PC5;
   extern qb50::GPIOPin& PC6;
   extern qb50::GPIOPin& PC7;
   extern qb50::GPIOPin& PC8;
   extern qb50::GPIOPin& PC9;
   extern qb50::GPIOPin& PC10;
   extern qb50::GPIOPin& PC11;
   extern qb50::GPIOPin& PC12;
   extern qb50::GPIOPin& PC13;
   extern qb50::GPIOPin& PC14;
   extern qb50::GPIOPin& PC15;

   extern qb50::GPIOPin& PD0;
   extern qb50::GPIOPin& PD1;
   extern qb50::GPIOPin& PD2;
   extern qb50::GPIOPin& PD3;
   extern qb50::GPIOPin& PD4;
   extern qb50::GPIOPin& PD5;
   extern qb50::GPIOPin& PD6;
   extern qb50::GPIOPin& PD7;
   extern qb50::GPIOPin& PD8;
   extern qb50::GPIOPin& PD9;
   extern qb50::GPIOPin& PD10;
   extern qb50::GPIOPin& PD11;
   extern qb50::GPIOPin& PD12;
   extern qb50::GPIOPin& PD13;
   extern qb50::GPIOPin& PD14;
   extern qb50::GPIOPin& PD15;

   extern qb50::GPIOPin& PE0;
   extern qb50::GPIOPin& PE1;
   extern qb50::GPIOPin& PE2;
   extern qb50::GPIOPin& PE3;
   extern qb50::GPIOPin& PE4;
   extern qb50::GPIOPin& PE5;
   extern qb50::GPIOPin& PE6;
   extern qb50::GPIOPin& PE7;
   extern qb50::GPIOPin& PE8;
   extern qb50::GPIOPin& PE9;
   extern qb50::GPIOPin& PE10;
   extern qb50::GPIOPin& PE11;
   extern qb50::GPIOPin& PE12;
   extern qb50::GPIOPin& PE13;
   extern qb50::GPIOPin& PE14;
   extern qb50::GPIOPin& PE15;

} /* qb50 */


#endif /* _QB50_SYS_GPIO_PIN_H */

/*EoF*/
