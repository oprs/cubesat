
#ifndef _QB50_ADCS_CONFIG_H
#define _QB50_ADCS_CONFIG_H

#include "system/qb50.h"

/*
#include "Bus.h"
#include "device/Syslog.h"
#include "device/NVIC.h"
#include "device/EXTI.h"
#include "device/RstClk.h"
#include "device/Power.h"
#include "device/Backup.h"
#include "device/PMU.h"
#include "device/DMA.h"
#include "device/DMAStream.h"
#include "device/SPI.h"
#include "device/GPIO.h"
#include "device/UART.h"
#include "device/A25Lxxx.h"
#include "device/FlashArray.h"
#include "device/ConfSlice.h"
#include "device/ADC.h"
#include "device/MAX111x.h"
#include "device/AX25Out.h"
#include "device/NRZI.h"
#include "device/FIFO.hpp"
#include "device/Transceiver.h"
#include "device/Satellite.h"

#include "commun/State.h"
#include "commun/Raw.h"

#include "system/Application.h"
#include "system/UserLock.h"
#include "system/Logger.h"
#include "system/Event.h"
*/

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

   extern qb50::GPIOPin& PA0;   extern qb50::GPIOPin& PA1;
   extern qb50::GPIOPin& PA2;   extern qb50::GPIOPin& PA3;
   extern qb50::GPIOPin& PA4;   extern qb50::GPIOPin& PA5;
   extern qb50::GPIOPin& PA6;   extern qb50::GPIOPin& PA7;
   extern qb50::GPIOPin& PA8;   extern qb50::GPIOPin& PA9;
   extern qb50::GPIOPin& PA10;  extern qb50::GPIOPin& PA11;
   extern qb50::GPIOPin& PA12;  extern qb50::GPIOPin& PA13;
   extern qb50::GPIOPin& PA14;  extern qb50::GPIOPin& PA15;

   extern qb50::GPIOPin& PB0;   extern qb50::GPIOPin& PB1;
   extern qb50::GPIOPin& PB2;   extern qb50::GPIOPin& PB3;
   extern qb50::GPIOPin& PB4;   extern qb50::GPIOPin& PB5;
   extern qb50::GPIOPin& PB6;   extern qb50::GPIOPin& PB7;
   extern qb50::GPIOPin& PB8;   extern qb50::GPIOPin& PB9;
   extern qb50::GPIOPin& PB10;  extern qb50::GPIOPin& PB11;
   extern qb50::GPIOPin& PB12;  extern qb50::GPIOPin& PB13;
   extern qb50::GPIOPin& PB14;  extern qb50::GPIOPin& PB15;

   extern qb50::GPIOPin& PC0;   extern qb50::GPIOPin& PC1;
   extern qb50::GPIOPin& PC2;   extern qb50::GPIOPin& PC3;
   extern qb50::GPIOPin& PC4;   extern qb50::GPIOPin& PC5;
   extern qb50::GPIOPin& PC6;   extern qb50::GPIOPin& PC7;
   extern qb50::GPIOPin& PC8;   extern qb50::GPIOPin& PC9;
   extern qb50::GPIOPin& PC10;  extern qb50::GPIOPin& PC11;
   extern qb50::GPIOPin& PC12;  extern qb50::GPIOPin& PC13;
   extern qb50::GPIOPin& PC14;  extern qb50::GPIOPin& PC15;

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
