
#ifndef _QB50_ADCS_CONFIG_H
#define _QB50_ADCS_CONFIG_H

#include "system/qb50.h"


namespace qb50 {

//  - - - - - - - - - - - - -  //
//  S Y S T E M   L O G G E R  //
//  - - - - - - - - - - - - -  //

   extern qb50::Syslog SYSLOG;

//  - - - - - - - - - - - - - - - - - - - - - -  //
//  R E S E T / C L O C K   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - - - -  //

   extern qb50::RstClk RCC;

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   extern qb50::NVIC IRQ;

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::DMA DMA1;
   extern qb50::DMA DMA2;

//  - - - - - - - - - - -  //
//  D M A   S T R E A M S  //
//  - - - - - - - - - - -  //

   extern qb50::DMAStream DMA1ST0;
   extern qb50::DMAStream DMA1ST1;
   extern qb50::DMAStream DMA1ST2;
   extern qb50::DMAStream DMA1ST3;
   extern qb50::DMAStream DMA1ST4;
   extern qb50::DMAStream DMA1ST5;
   extern qb50::DMAStream DMA1ST6;
   extern qb50::DMAStream DMA1ST7;

   extern qb50::DMAStream DMA2ST0;
   extern qb50::DMAStream DMA2ST1;
   extern qb50::DMAStream DMA2ST2;
   extern qb50::DMAStream DMA2ST3;
   extern qb50::DMAStream DMA2ST4;
   extern qb50::DMAStream DMA2ST5;
   extern qb50::DMAStream DMA2ST6;
   extern qb50::DMAStream DMA2ST7;

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

   extern qb50::UART UART1;
   extern qb50::UART UART2;
   extern qb50::UART UART3;
   extern qb50::UART UART4;
   extern qb50::UART UART5;
   extern qb50::UART UART6;

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::SPI SPI1;
   extern qb50::SPI SPI2;
   extern qb50::SPI SPI3;

//  - - - - - - - - - - - - - - -  //
//  A D C   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::STM32_ADC ADC1;

//  - - - - - - - - - - - -  //
//  A D C   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   extern qb50::STM32_ADC::Channel SUN1;
   extern qb50::STM32_ADC::Channel SUN2;
   extern qb50::STM32_ADC::Channel SUN3;
   extern qb50::STM32_ADC::Channel SUN4;
   extern qb50::STM32_ADC::Channel SUN5;
   extern qb50::STM32_ADC::Channel SUN6;
   extern qb50::STM32_ADC::Channel SUN7;
   extern qb50::STM32_ADC::Channel SUN8;
   extern qb50::STM32_ADC::Channel SUN9;

   /* aliases */

   extern qb50::STM32_ADC::Channel& GS1_1;
   extern qb50::STM32_ADC::Channel& GS1_2;
   extern qb50::STM32_ADC::Channel& GS2_1;
   extern qb50::STM32_ADC::Channel& GS2_2;
   extern qb50::STM32_ADC::Channel& GS3_1;
   extern qb50::STM32_ADC::Channel& GS3_2;
   extern qb50::STM32_ADC::Channel& GS4_1;
   extern qb50::STM32_ADC::Channel& GS4_2;
   extern qb50::STM32_ADC::Channel& GS5;

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   extern qb50::A25Lxxx FLASH0;

//  - - - - - - - - - - -  //
//        S T A T E        //
//  - - - - - - - - - - -  //

/*
   extern qb50::TIMER TIMER1;
   extern qb50::TIMER TIMER2;
   extern qb50::TIMER TIMER8;

   extern qb50::EXTI EXTI1;
*/

} /* qb50 */


#endif /*_QB50_ADCS_CONFIG_H*/

/*EoF*/
