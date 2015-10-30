
#ifndef _QB50_DISC_CONFIG_H
#define _QB50_DISC_CONFIG_H

#include "system/qb50.h"


namespace qb50 {

//  - - - - - - - - - - - - -  //
//  S Y S T E M   L O G G E R  //
//  - - - - - - - - - - - - -  //

   extern qb50::Syslog SYSLOG;

//  - - - - - - - - - - - - - - - - - - - - - -  //
//  R E S E T / C L O C K   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - - - -  //

   extern qb50::STM32_RCC RCC;

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   extern qb50::NVIC IRQ;

//  - - - - - - - - - - -  //
//  B A C K U P   S R A M  //
//  - - - - - - - - - - -  //

   extern qb50::STM32_BKPSRAM BPK;

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::DMA DMA1;

//  - - - - - - - - - - -  //
//  D M A   S T R E A M S  //
//  - - - - - - - - - - -  //

   extern qb50::DMA::Stream DMA1ST2;
   extern qb50::DMA::Stream DMA1ST5;

//  - - - - - - - - -  //
//  G P I O   P I N S  //
//  - - - - - - - - -  //

   extern qb50::GPIO::Pin& PA0;   extern qb50::GPIO::Pin& PA1;
   extern qb50::GPIO::Pin& PA2;   extern qb50::GPIO::Pin& PA3;
   extern qb50::GPIO::Pin& PA4;   extern qb50::GPIO::Pin& PA5;
   extern qb50::GPIO::Pin& PA6;   extern qb50::GPIO::Pin& PA7;
   extern qb50::GPIO::Pin& PA8;   extern qb50::GPIO::Pin& PA9;
   extern qb50::GPIO::Pin& PA10;  extern qb50::GPIO::Pin& PA11;
   extern qb50::GPIO::Pin& PA12;  extern qb50::GPIO::Pin& PA13;
   extern qb50::GPIO::Pin& PA14;  extern qb50::GPIO::Pin& PA15;

   extern qb50::GPIO::Pin& PB0;   extern qb50::GPIO::Pin& PB1;
   extern qb50::GPIO::Pin& PB2;   extern qb50::GPIO::Pin& PB3;
   extern qb50::GPIO::Pin& PB4;   extern qb50::GPIO::Pin& PB5;
   extern qb50::GPIO::Pin& PB6;   extern qb50::GPIO::Pin& PB7;
   extern qb50::GPIO::Pin& PB8;   extern qb50::GPIO::Pin& PB9;
   extern qb50::GPIO::Pin& PB10;  extern qb50::GPIO::Pin& PB11;
   extern qb50::GPIO::Pin& PB12;  extern qb50::GPIO::Pin& PB13;
   extern qb50::GPIO::Pin& PB14;  extern qb50::GPIO::Pin& PB15;

   extern qb50::GPIO::Pin& PC0;   extern qb50::GPIO::Pin& PC1;
   extern qb50::GPIO::Pin& PC2;   extern qb50::GPIO::Pin& PC3;
   extern qb50::GPIO::Pin& PC4;   extern qb50::GPIO::Pin& PC5;
   extern qb50::GPIO::Pin& PC6;   extern qb50::GPIO::Pin& PC7;
   extern qb50::GPIO::Pin& PC8;   extern qb50::GPIO::Pin& PC9;
   extern qb50::GPIO::Pin& PC10;  extern qb50::GPIO::Pin& PC11;
   extern qb50::GPIO::Pin& PC12;  extern qb50::GPIO::Pin& PC13;
   extern qb50::GPIO::Pin& PC14;  extern qb50::GPIO::Pin& PC15;

//  - - - - - - - - - - - - - - - -  //
//  G P I O   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   extern qb50::GPIO GPIOA;
   extern qb50::GPIO GPIOB;
   extern qb50::GPIO GPIOC;

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   extern qb50::STM32_UART UART1;
   extern qb50::STM32_UART UART2;
   extern qb50::STM32_UART UART3;
   extern qb50::STM32_UART UART6;

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::SPI SPI3;

//  - - - - - - - - -  //
//  G Y R O S C O P E  //
//  - - - - - - - - -  //

   extern qb50::L3GD20 MEMS0;
   extern qb50::L3GD20 MEMS1;

} /* qb50 */


#endif /*_QB50_DISC_CONFIG_H*/

/*EoF*/
