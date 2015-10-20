
#ifndef _QB50_ODB_CONFIG_H
#define _QB50_ODB_CONFIG_H

#include "system/qb50.h"
#include "CMD/Parameters.h"
#include "ODB.h"


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

//  - - - - - - - - - - -  //
//  B A C K U P   S R A M  //
//  - - - - - - - - - - -  //

   extern qb50::Backup BPK;

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

   extern qb50::UART UART1;
   extern qb50::UART UART2;
   extern qb50::UART UART3;
   extern qb50::UART UART6;

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::SPI SPI3;

//  - - - - - - - - - - - - - - -  //
//  A D C   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   extern qb50::MAX111x ADC1;
   extern qb50::MAX111x ADC2;
   extern qb50::MAX111x ADC3;
   extern qb50::MAX111x ADC4;

//  - - - - - - - - - - - -  //
//  A D C   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   extern qb50::MAX111x::Channel& ADC1CH0;  extern qb50::MAX111x::Channel& ADC1CH1;
   extern qb50::MAX111x::Channel& ADC1CH2;  extern qb50::MAX111x::Channel& ADC1CH3;
   extern qb50::MAX111x::Channel& ADC1CH4;  extern qb50::MAX111x::Channel& ADC1CH5;
   extern qb50::MAX111x::Channel& ADC1CH6;  extern qb50::MAX111x::Channel& ADC1CH7;

   extern qb50::MAX111x::Channel& ADC2CH0;  extern qb50::MAX111x::Channel& ADC2CH1;
   extern qb50::MAX111x::Channel& ADC2CH2;  extern qb50::MAX111x::Channel& ADC2CH3;
   extern qb50::MAX111x::Channel& ADC2CH4;  extern qb50::MAX111x::Channel& ADC2CH5;
   extern qb50::MAX111x::Channel& ADC2CH6;  extern qb50::MAX111x::Channel& ADC2CH7;

   extern qb50::MAX111x::Channel& ADC3CH0;  extern qb50::MAX111x::Channel& ADC3CH1;
   extern qb50::MAX111x::Channel& ADC3CH2;  extern qb50::MAX111x::Channel& ADC3CH3;
   extern qb50::MAX111x::Channel& ADC3CH4;  extern qb50::MAX111x::Channel& ADC3CH5;
   extern qb50::MAX111x::Channel& ADC3CH6;  extern qb50::MAX111x::Channel& ADC3CH7;

   extern qb50::MAX111x::Channel& ADC4CH0;  extern qb50::MAX111x::Channel& ADC4CH1;
   extern qb50::MAX111x::Channel& ADC4CH2;  extern qb50::MAX111x::Channel& ADC4CH3;
   extern qb50::MAX111x::Channel& ADC4CH4;  extern qb50::MAX111x::Channel& ADC4CH5;
   extern qb50::MAX111x::Channel& ADC4CH6;  extern qb50::MAX111x::Channel& ADC4CH7;

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   extern qb50::A25Lxxx FLASH0;
   extern qb50::A25Lxxx FLASH1;

   extern qb50::FlashArray VFLASH;

   extern qb50::ConfSlice CONF;

//  - - - - - - - - - - - - -  //
//  P O W E R   M A N A G E R  //
//  - - - - - - - - - - - - -  //

   extern qb50::PMU PMU0;

//  - - - - - - - - - - -  //
//  T R A N S C E I V E R  //
//  - - - - - - - - - - -  //

   extern qb50::Transceiver RFTX;

//  - - - - - - - - - -  //
//  P A R A M E T E R S  //
//  - - - - - - - - - -  //

   extern qb50::Parameters PARAMS;

//  - - -  //
//  O D B  //
//  - - -  //

   extern qb50::ODB SAT;

} /* qb50 */


#endif /*_QB50_ODB_CONFIG_H*/

/*EoF*/
