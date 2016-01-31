
#include "config.h"
#include <safe_stm32f4xx.h>


namespace qb50 {

//  - - - - - - - - - - - - -  //
//  S Y S T E M   L O G G E R  //
//  - - - - - - - - - - - - -  //

   Syslog SYSLOG( "SYSLOG", UART6 );

//  - - - - - - - - - -  //
//  C O R E   B U S E S  //
//  - - - - - - - - - -  //

   /*        id         name */
   Bus AHB1( Bus::AHB1, "AHB1" );
   Bus AHB2( Bus::AHB2, "AHB2" );
   Bus AHB3( Bus::AHB3, "AHB3" );

   /*        id         name */
   Bus APB1( Bus::APB1, "APB1" );
   Bus APB2( Bus::APB2, "APB2" );

//  - - - - - - - - - - - - - - - - - - - - - -  //
//  R E S E T / C L O C K   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - - - -  //

   STM32_RCC RCC( RCC_BASE, "RCC" );

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   STM32_NVIC NVIC;
   STM32_EXTI EXTI;

//  - - - - - - - - - - - - - - - -  //
//  P O W E R   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - -  //

   STM32_PWR PWR( APB1, PWR_BASE, STM32_RCC::APB1Periph_PWR, "PWR" );

//  - - - - - - - - - - -  //
//  B A C K U P   S R A M  //
//  - - - - - - - - - - -  //

   STM32_BKP BKP( AHB1, BKPSRAM_BASE, STM32_RCC::AHB1Periph_BKP, "BKP" );

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*              bus   iobase     periph                      name */
   STM32_DMA DMA1( AHB1, DMA1_BASE, STM32_RCC::AHB1Periph_DMA1, "DMA1" );

//  - - - - - - - - - - -  //
//  D M A   S T R E A M S  //
//  - - - - - - - - - - -  //

   STM32_DMA::Stream DMA1ST2( DMA1, DMA1_Stream2_BASE, DMA1_Stream2_IRQn, "DMA1ST2", 0x10 );
   STM32_DMA::Stream DMA1ST5( DMA1, DMA1_Stream5_BASE, DMA1_Stream5_IRQn, "DMA1ST5", 0x26 );

//  - - - - - - - - -  //
//  G P I O   P I N S  //
//  - - - - - - - - -  //

   static STM32_GPIO::Pin GPIOA_Pins[ 16 ] = {
      STM32_GPIO::Pin( GPIOA,  0, "PA0",  0x0001 ),  STM32_GPIO::Pin( GPIOA,  1, "PA1",  0x0002 ),
      STM32_GPIO::Pin( GPIOA,  2, "PA2",  0x0004 ),  STM32_GPIO::Pin( GPIOA,  3, "PA3",  0x0008 ),
      STM32_GPIO::Pin( GPIOA,  4, "PA4",  0x0010 ),  STM32_GPIO::Pin( GPIOA,  5, "PA5",  0x0020 ),
      STM32_GPIO::Pin( GPIOA,  6, "PA6",  0x0040 ),  STM32_GPIO::Pin( GPIOA,  7, "PA7",  0x0080 ),
      STM32_GPIO::Pin( GPIOA,  8, "PA8",  0x0100 ),  STM32_GPIO::Pin( GPIOA,  9, "PA9",  0x0200 ),
      STM32_GPIO::Pin( GPIOA, 10, "PA10", 0x0400 ),  STM32_GPIO::Pin( GPIOA, 11, "PA11", 0x0800 ),
      STM32_GPIO::Pin( GPIOA, 12, "PA12", 0x1000 ),  STM32_GPIO::Pin( GPIOA, 13, "PA13", 0x2000 ),
      STM32_GPIO::Pin( GPIOA, 14, "PA14", 0x4000 ),  STM32_GPIO::Pin( GPIOA, 15, "PA15", 0x8000 )
   };

   static STM32_GPIO::Pin GPIOB_Pins[ 16 ] = {
      STM32_GPIO::Pin( GPIOB,  0, "PB0",  0x0001 ),  STM32_GPIO::Pin( GPIOB,  1, "PB1",  0x0002 ),
      STM32_GPIO::Pin( GPIOB,  2, "PB2",  0x0004 ),  STM32_GPIO::Pin( GPIOB,  3, "PB3",  0x0008 ),
      STM32_GPIO::Pin( GPIOB,  4, "PB4",  0x0010 ),  STM32_GPIO::Pin( GPIOB,  5, "PB5",  0x0020 ),
      STM32_GPIO::Pin( GPIOB,  6, "PB6",  0x0040 ),  STM32_GPIO::Pin( GPIOB,  7, "PB7",  0x0080 ),
      STM32_GPIO::Pin( GPIOB,  8, "PB8",  0x0100 ),  STM32_GPIO::Pin( GPIOB,  9, "PB9",  0x0200 ),
      STM32_GPIO::Pin( GPIOB, 10, "PB10", 0x0400 ),  STM32_GPIO::Pin( GPIOB, 11, "PB11", 0x0800 ),
      STM32_GPIO::Pin( GPIOB, 12, "PB12", 0x1000 ),  STM32_GPIO::Pin( GPIOB, 13, "PB13", 0x2000 ),
      STM32_GPIO::Pin( GPIOB, 14, "PB14", 0x4000 ),  STM32_GPIO::Pin( GPIOB, 15, "PB15", 0x8000 )
   };

   static STM32_GPIO::Pin GPIOC_Pins[ 16 ] = {
      STM32_GPIO::Pin( GPIOC,  0, "PC0",  0x0001 ),  STM32_GPIO::Pin( GPIOC,  1, "PC1",  0x0002 ),
      STM32_GPIO::Pin( GPIOC,  2, "PC2",  0x0004 ),  STM32_GPIO::Pin( GPIOC,  3, "PC3",  0x0008 ),
      STM32_GPIO::Pin( GPIOC,  4, "PC4",  0x0010 ),  STM32_GPIO::Pin( GPIOC,  5, "PC5",  0x0020 ),
      STM32_GPIO::Pin( GPIOC,  6, "PC6",  0x0040 ),  STM32_GPIO::Pin( GPIOC,  7, "PC7",  0x0080 ),
      STM32_GPIO::Pin( GPIOC,  8, "PC8",  0x0100 ),  STM32_GPIO::Pin( GPIOC,  9, "PC9",  0x0200 ),
      STM32_GPIO::Pin( GPIOC, 10, "PC10", 0x0400 ),  STM32_GPIO::Pin( GPIOC, 11, "PC11", 0x0800 ),
      STM32_GPIO::Pin( GPIOC, 12, "PC12", 0x1000 ),  STM32_GPIO::Pin( GPIOC, 13, "PC13", 0x2000 ),
      STM32_GPIO::Pin( GPIOC, 14, "PC14", 0x4000 ),  STM32_GPIO::Pin( GPIOC, 15, "PC15", 0x8000 )
   };

   static STM32_GPIO::Pin GPIOD_Pins[ 16 ] = {
      STM32_GPIO::Pin( GPIOD,  0, "PD0",  0x0001 ),  STM32_GPIO::Pin( GPIOD,  1, "PD1",  0x0002 ),
      STM32_GPIO::Pin( GPIOD,  2, "PD2",  0x0004 ),  STM32_GPIO::Pin( GPIOD,  3, "PD3",  0x0008 ),
      STM32_GPIO::Pin( GPIOD,  4, "PD4",  0x0010 ),  STM32_GPIO::Pin( GPIOD,  5, "PD5",  0x0020 ),
      STM32_GPIO::Pin( GPIOD,  6, "PD6",  0x0040 ),  STM32_GPIO::Pin( GPIOD,  7, "PD7",  0x0080 ),
      STM32_GPIO::Pin( GPIOD,  8, "PD8",  0x0100 ),  STM32_GPIO::Pin( GPIOD,  9, "PD9",  0x0200 ),
      STM32_GPIO::Pin( GPIOD, 10, "PD10", 0x0400 ),  STM32_GPIO::Pin( GPIOD, 11, "PD11", 0x0800 ),
      STM32_GPIO::Pin( GPIOD, 12, "PD12", 0x1000 ),  STM32_GPIO::Pin( GPIOD, 13, "PD13", 0x2000 ),
      STM32_GPIO::Pin( GPIOD, 14, "PD14", 0x4000 ),  STM32_GPIO::Pin( GPIOD, 15, "PD15", 0x8000 )
   };

   /* aliases */

   STM32_GPIO::Pin& PA0  = GPIOA_Pins[  0 ];  STM32_GPIO::Pin& PA1  = GPIOA_Pins[  1 ];
   STM32_GPIO::Pin& PA2  = GPIOA_Pins[  2 ];  STM32_GPIO::Pin& PA3  = GPIOA_Pins[  3 ];
   STM32_GPIO::Pin& PA4  = GPIOA_Pins[  4 ];  STM32_GPIO::Pin& PA5  = GPIOA_Pins[  5 ];
   STM32_GPIO::Pin& PA6  = GPIOA_Pins[  6 ];  STM32_GPIO::Pin& PA7  = GPIOA_Pins[  7 ];
   STM32_GPIO::Pin& PA8  = GPIOA_Pins[  8 ];  STM32_GPIO::Pin& PA9  = GPIOA_Pins[  9 ];
   STM32_GPIO::Pin& PA10 = GPIOA_Pins[ 10 ];  STM32_GPIO::Pin& PA11 = GPIOA_Pins[ 11 ];
   STM32_GPIO::Pin& PA12 = GPIOA_Pins[ 12 ];  STM32_GPIO::Pin& PA13 = GPIOA_Pins[ 13 ];
   STM32_GPIO::Pin& PA14 = GPIOA_Pins[ 14 ];  STM32_GPIO::Pin& PA15 = GPIOA_Pins[ 15 ];

   STM32_GPIO::Pin& PB0  = GPIOB_Pins[  0 ];  STM32_GPIO::Pin& PB1  = GPIOB_Pins[  1 ];
   STM32_GPIO::Pin& PB2  = GPIOB_Pins[  2 ];  STM32_GPIO::Pin& PB3  = GPIOB_Pins[  3 ];
   STM32_GPIO::Pin& PB4  = GPIOB_Pins[  4 ];  STM32_GPIO::Pin& PB5  = GPIOB_Pins[  5 ];
   STM32_GPIO::Pin& PB6  = GPIOB_Pins[  6 ];  STM32_GPIO::Pin& PB7  = GPIOB_Pins[  7 ];
   STM32_GPIO::Pin& PB8  = GPIOB_Pins[  8 ];  STM32_GPIO::Pin& PB9  = GPIOB_Pins[  9 ];
   STM32_GPIO::Pin& PB10 = GPIOB_Pins[ 10 ];  STM32_GPIO::Pin& PB11 = GPIOB_Pins[ 11 ];
   STM32_GPIO::Pin& PB12 = GPIOB_Pins[ 12 ];  STM32_GPIO::Pin& PB13 = GPIOB_Pins[ 13 ];
   STM32_GPIO::Pin& PB14 = GPIOB_Pins[ 14 ];  STM32_GPIO::Pin& PB15 = GPIOB_Pins[ 15 ];

   STM32_GPIO::Pin& PC0  = GPIOC_Pins[  0 ];  STM32_GPIO::Pin& PC1  = GPIOC_Pins[  1 ];
   STM32_GPIO::Pin& PC2  = GPIOC_Pins[  2 ];  STM32_GPIO::Pin& PC3  = GPIOC_Pins[  3 ];
   STM32_GPIO::Pin& PC4  = GPIOC_Pins[  4 ];  STM32_GPIO::Pin& PC5  = GPIOC_Pins[  5 ];
   STM32_GPIO::Pin& PC6  = GPIOC_Pins[  6 ];  STM32_GPIO::Pin& PC7  = GPIOC_Pins[  7 ];
   STM32_GPIO::Pin& PC8  = GPIOC_Pins[  8 ];  STM32_GPIO::Pin& PC9  = GPIOC_Pins[  9 ];
   STM32_GPIO::Pin& PC10 = GPIOC_Pins[ 10 ];  STM32_GPIO::Pin& PC11 = GPIOC_Pins[ 11 ];
   STM32_GPIO::Pin& PC12 = GPIOC_Pins[ 12 ];  STM32_GPIO::Pin& PC13 = GPIOC_Pins[ 13 ];
   STM32_GPIO::Pin& PC14 = GPIOC_Pins[ 14 ];  STM32_GPIO::Pin& PC15 = GPIOC_Pins[ 15 ];

   STM32_GPIO::Pin& PD0  = GPIOD_Pins[  0 ];  STM32_GPIO::Pin& PD1  = GPIOD_Pins[  1 ];
   STM32_GPIO::Pin& PD2  = GPIOD_Pins[  2 ];  STM32_GPIO::Pin& PD3  = GPIOD_Pins[  3 ];
   STM32_GPIO::Pin& PD4  = GPIOD_Pins[  4 ];  STM32_GPIO::Pin& PD5  = GPIOD_Pins[  5 ];
   STM32_GPIO::Pin& PD6  = GPIOD_Pins[  6 ];  STM32_GPIO::Pin& PD7  = GPIOD_Pins[  7 ];
   STM32_GPIO::Pin& PD8  = GPIOD_Pins[  8 ];  STM32_GPIO::Pin& PD9  = GPIOD_Pins[  9 ];
   STM32_GPIO::Pin& PD10 = GPIOD_Pins[ 10 ];  STM32_GPIO::Pin& PD11 = GPIOD_Pins[ 11 ];
   STM32_GPIO::Pin& PD12 = GPIOD_Pins[ 12 ];  STM32_GPIO::Pin& PD13 = GPIOD_Pins[ 13 ];
   STM32_GPIO::Pin& PD14 = GPIOD_Pins[ 14 ];  STM32_GPIO::Pin& PD15 = GPIOD_Pins[ 15 ];

//  - - - - - - - - - - - - - - - -  //
//  G P I O   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*                bus   iobase      periph                      id  name     pins */
   STM32_GPIO GPIOA( AHB1, GPIOA_BASE, STM32_RCC::AHB1Periph_GPIOA, 0, "GPIOA", GPIOA_Pins );
   STM32_GPIO GPIOB( AHB1, GPIOB_BASE, STM32_RCC::AHB1Periph_GPIOB, 1, "GPIOB", GPIOB_Pins );
   STM32_GPIO GPIOC( AHB1, GPIOC_BASE, STM32_RCC::AHB1Periph_GPIOC, 2, "GPIOC", GPIOC_Pins );
   STM32_GPIO GPIOD( AHB1, GPIOD_BASE, STM32_RCC::AHB1Periph_GPIOD, 3, "GPIOD", GPIOD_Pins );

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*                bus   iobase       periph                        name    rxPin txPin  IRQ number   alt. function */
   STM32_UART UART1( APB2, USART1_BASE, STM32_RCC::APB2Periph_USART1, "UART1", PB7,  PB6,  USART1_IRQn, STM32_GPIO::UART1 );
   STM32_UART UART2( APB1, USART2_BASE, STM32_RCC::APB1Periph_USART2, "UART2", PA3,  PA2,  USART2_IRQn, STM32_GPIO::UART2 );
   STM32_UART UART3( APB1, USART3_BASE, STM32_RCC::APB1Periph_USART3, "UART3", PB11, PB10, USART3_IRQn, STM32_GPIO::UART3 );
   STM32_UART UART6( APB2, USART6_BASE, STM32_RCC::APB2Periph_USART6, "UART6", PC7,  PC6,  USART6_IRQn, STM32_GPIO::UART6 );

//  - - - - - - - - - - -  //
//  S P I   S T R E A M S  //
//  - - - - - - - - - - -  //

   /*
    *  See the STM32F4 reference manual for DMA stream/channel mappings,
    *  sec. 10.3.3 "Channel Selection", pp. 306-307
    */

   STM32_SPI::Stream SPI3_MISO( DMA1ST2, STM32_DMA::CH0, "SPI3MISO", PB4, STM32_GPIO::SPI3 );
   STM32_SPI::Stream SPI3_MOSI( DMA1ST5, STM32_DMA::CH0, "SPI3MOSI", PB5, STM32_GPIO::SPI3 );

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*              bus   iobase     periph                      name    rx stream  tx stream  clk  alt. func.  fPCLK. div */
   STM32_SPI SPI3( APB1, SPI3_BASE, STM32_RCC::APB1Periph_SPI3, "SPI3", SPI3_MISO, SPI3_MOSI, PB3, STM32_GPIO::SPI3, STM32_SPI::DIV16 );

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   /*              SPI    name    csPin */
   A25Lxxx FLASH0( SPI3, "FLASH0", PB6 );
   A25Lxxx FLASH1( SPI3, "FLASH1", PB7 );

//  - - - - - - - -  //
//  G Y R O / M A G  //
//  - - - - - - - -  //

   L3GD20 GYR0( SPI3, "GYR0", PC8,  L3GD20::R250DPS );
 //L3GD20 GYR1( SPI3, "GYR1", PC10, L3GD20::R250DPS );

} /* qb50 */


void DMA1_Stream2_IRQHandler( void )
{ qb50::DMA1ST2.isr(); }

void DMA1_Stream5_IRQHandler( void )
{ qb50::DMA1ST5.isr(); }

void SPI3_IRQHandler( void )
{ qb50::SPI3.isr(); }

void USART1_IRQHandler( void )
{ qb50::UART1.isr(); }

void USART2_IRQHandler( void )
{ qb50::UART2.isr(); }

void USART3_IRQHandler( void )
{ qb50::UART3.isr(); }

void USART6_IRQHandler( void )
{ qb50::UART6.isr(); }


/*EoF*/
