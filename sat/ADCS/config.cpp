
#include "config.h"
#include <safe_stm32f4xx.h>


namespace qb50 {

//  - - - - - - - - - - - - -  //
//  S Y S T E M   L O G G E R  //
//  - - - - - - - - - - - - -  //

   Syslog SYSLOG( "SYSLOG", UART1 );

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

   RstClk RCC( RCC_BASE, "RCC" );

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   NVIC IRQ;

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph                   name */
   DMA DMA1( AHB1, DMA1_BASE, RstClk::AHB1Periph_DMA1, "DMA1" );
   DMA DMA2( AHB1, DMA1_BASE, RstClk::AHB1Periph_DMA2, "DAM2" );

//  - - - - - - - - - - -  //
//  D M A   S T R E A M S  //
//  - - - - - - - - - - -  //

   DMAStream DMA1ST0( DMA1, DMA1_Stream0_BASE, DMA1_Stream0_IRQn, "DMA1ST0", 0x00 );
   DMAStream DMA1ST1( DMA1, DMA1_Stream1_BASE, DMA1_Stream1_IRQn, "DMA1ST1", 0x06 );
   DMAStream DMA1ST2( DMA1, DMA1_Stream2_BASE, DMA1_Stream2_IRQn, "DMA1ST2", 0x10 );
   DMAStream DMA1ST3( DMA1, DMA1_Stream3_BASE, DMA1_Stream3_IRQn, "DMA1ST3", 0x16 );
   DMAStream DMA1ST4( DMA1, DMA1_Stream4_BASE, DMA1_Stream4_IRQn, "DMA1ST4", 0x20 );
   DMAStream DMA1ST5( DMA1, DMA1_Stream5_BASE, DMA1_Stream5_IRQn, "DMA1ST5", 0x26 );
   DMAStream DMA1ST6( DMA1, DMA1_Stream6_BASE, DMA1_Stream6_IRQn, "DMA1ST6", 0x30 );
   DMAStream DMA1ST7( DMA1, DMA1_Stream7_BASE, DMA1_Stream7_IRQn, "DMA1ST7", 0x36 );

   DMAStream DMA2ST0( DMA2, DMA2_Stream0_BASE, DMA2_Stream0_IRQn, "DMA2ST0", 0x00 );
   DMAStream DMA2ST1( DMA2, DMA2_Stream1_BASE, DMA2_Stream1_IRQn, "DMA2ST1", 0x06 );
   DMAStream DMA2ST2( DMA2, DMA2_Stream2_BASE, DMA2_Stream2_IRQn, "DMA2ST2", 0x10 );
   DMAStream DMA2ST3( DMA2, DMA2_Stream3_BASE, DMA2_Stream3_IRQn, "DMA2ST3", 0x16 );
   DMAStream DMA2ST4( DMA2, DMA2_Stream4_BASE, DMA2_Stream4_IRQn, "DMA2ST4", 0x20 );
   DMAStream DMA2ST5( DMA2, DMA2_Stream5_BASE, DMA2_Stream5_IRQn, "DMA2ST5", 0x26 );
   DMAStream DMA2ST6( DMA2, DMA2_Stream6_BASE, DMA2_Stream6_IRQn, "DMA2ST6", 0x30 );
   DMAStream DMA2ST7( DMA2, DMA2_Stream7_BASE, DMA2_Stream7_IRQn, "DMA2ST7", 0x36 );

//  - - - - - - - - -  //
//  G P I O   P I N S  //
//  - - - - - - - - -  //

   static GPIOPin GPIOA_Pins[ 16 ] = {
      GPIOPin( GPIOA,  0, "PA0",  0x0001 ),  GPIOPin( GPIOA,  1, "PA1",  0x0002 ),
      GPIOPin( GPIOA,  2, "PA2",  0x0004 ),  GPIOPin( GPIOA,  3, "PA3",  0x0008 ),
      GPIOPin( GPIOA,  4, "PA4",  0x0010 ),  GPIOPin( GPIOA,  5, "PA5",  0x0020 ),
      GPIOPin( GPIOA,  6, "PA6",  0x0040 ),  GPIOPin( GPIOA,  7, "PA7",  0x0080 ),
      GPIOPin( GPIOA,  8, "PA8",  0x0100 ),  GPIOPin( GPIOA,  9, "PA9",  0x0200 ),
      GPIOPin( GPIOA, 10, "PA10", 0x0400 ),  GPIOPin( GPIOA, 11, "PA11", 0x0800 ),
      GPIOPin( GPIOA, 12, "PA12", 0x1000 ),  GPIOPin( GPIOA, 13, "PA13", 0x2000 ),
      GPIOPin( GPIOA, 14, "PA14", 0x4000 ),  GPIOPin( GPIOA, 15, "PA15", 0x8000 )
   };

   static GPIOPin GPIOB_Pins[ 16 ] = {
      GPIOPin( GPIOB,  0, "PB0",  0x0001 ),  GPIOPin( GPIOB,  1, "PB1",  0x0002 ),
      GPIOPin( GPIOB,  2, "PB2",  0x0004 ),  GPIOPin( GPIOB,  3, "PB3",  0x0008 ),
      GPIOPin( GPIOB,  4, "PB4",  0x0010 ),  GPIOPin( GPIOB,  5, "PB5",  0x0020 ),
      GPIOPin( GPIOB,  6, "PB6",  0x0040 ),  GPIOPin( GPIOB,  7, "PB7",  0x0080 ),
      GPIOPin( GPIOB,  8, "PB8",  0x0100 ),  GPIOPin( GPIOB,  9, "PB9",  0x0200 ),
      GPIOPin( GPIOB, 10, "PB10", 0x0400 ),  GPIOPin( GPIOB, 11, "PB11", 0x0800 ),
      GPIOPin( GPIOB, 12, "PB12", 0x1000 ),  GPIOPin( GPIOB, 13, "PB13", 0x2000 ),
      GPIOPin( GPIOB, 14, "PB14", 0x4000 ),  GPIOPin( GPIOB, 15, "PB15", 0x8000 )
   };

   static GPIOPin GPIOC_Pins[ 16 ] = {
      GPIOPin( GPIOC,  0, "PC0",  0x0001 ),  GPIOPin( GPIOC,  1, "PC1",  0x0002 ),
      GPIOPin( GPIOC,  2, "PC2",  0x0004 ),  GPIOPin( GPIOC,  3, "PC3",  0x0008 ),
      GPIOPin( GPIOC,  4, "PC4",  0x0010 ),  GPIOPin( GPIOC,  5, "PC5",  0x0020 ),
      GPIOPin( GPIOC,  6, "PC6",  0x0040 ),  GPIOPin( GPIOC,  7, "PC7",  0x0080 ),
      GPIOPin( GPIOC,  8, "PC8",  0x0100 ),  GPIOPin( GPIOC,  9, "PC9",  0x0200 ),
      GPIOPin( GPIOC, 10, "PC10", 0x0400 ),  GPIOPin( GPIOC, 11, "PC11", 0x0800 ),
      GPIOPin( GPIOC, 12, "PC12", 0x1000 ),  GPIOPin( GPIOC, 13, "PC13", 0x2000 ),
      GPIOPin( GPIOC, 14, "PC14", 0x4000 ),  GPIOPin( GPIOC, 15, "PC15", 0x8000 )
   };

   /* aliases */

   GPIOPin& PA0  = GPIOA_Pins[  0 ];  GPIOPin& PA1  = GPIOA_Pins[  1 ];
   GPIOPin& PA2  = GPIOA_Pins[  2 ];  GPIOPin& PA3  = GPIOA_Pins[  3 ];
   GPIOPin& PA4  = GPIOA_Pins[  4 ];  GPIOPin& PA5  = GPIOA_Pins[  5 ];
   GPIOPin& PA6  = GPIOA_Pins[  6 ];  GPIOPin& PA7  = GPIOA_Pins[  7 ];
   GPIOPin& PA8  = GPIOA_Pins[  8 ];  GPIOPin& PA9  = GPIOA_Pins[  9 ];
   GPIOPin& PA10 = GPIOA_Pins[ 10 ];  GPIOPin& PA11 = GPIOA_Pins[ 11 ];
   GPIOPin& PA12 = GPIOA_Pins[ 12 ];  GPIOPin& PA13 = GPIOA_Pins[ 13 ];
   GPIOPin& PA14 = GPIOA_Pins[ 14 ];  GPIOPin& PA15 = GPIOA_Pins[ 15 ];

   GPIOPin& PB0  = GPIOB_Pins[  0 ];  GPIOPin& PB1  = GPIOB_Pins[  1 ];
   GPIOPin& PB2  = GPIOB_Pins[  2 ];  GPIOPin& PB3  = GPIOB_Pins[  3 ];
   GPIOPin& PB4  = GPIOB_Pins[  4 ];  GPIOPin& PB5  = GPIOB_Pins[  5 ];
   GPIOPin& PB6  = GPIOB_Pins[  6 ];  GPIOPin& PB7  = GPIOB_Pins[  7 ];
   GPIOPin& PB8  = GPIOB_Pins[  8 ];  GPIOPin& PB9  = GPIOB_Pins[  9 ];
   GPIOPin& PB10 = GPIOB_Pins[ 10 ];  GPIOPin& PB11 = GPIOB_Pins[ 11 ];
   GPIOPin& PB12 = GPIOB_Pins[ 12 ];  GPIOPin& PB13 = GPIOB_Pins[ 13 ];
   GPIOPin& PB14 = GPIOB_Pins[ 14 ];  GPIOPin& PB15 = GPIOB_Pins[ 15 ];

   GPIOPin& PC0  = GPIOC_Pins[  0 ];  GPIOPin& PC1  = GPIOC_Pins[  1 ];
   GPIOPin& PC2  = GPIOC_Pins[  2 ];  GPIOPin& PC3  = GPIOC_Pins[  3 ];
   GPIOPin& PC4  = GPIOC_Pins[  4 ];  GPIOPin& PC5  = GPIOC_Pins[  5 ];
   GPIOPin& PC6  = GPIOC_Pins[  6 ];  GPIOPin& PC7  = GPIOC_Pins[  7 ];
   GPIOPin& PC8  = GPIOC_Pins[  8 ];  GPIOPin& PC9  = GPIOC_Pins[  9 ];
   GPIOPin& PC10 = GPIOC_Pins[ 10 ];  GPIOPin& PC11 = GPIOC_Pins[ 11 ];
   GPIOPin& PC12 = GPIOC_Pins[ 12 ];  GPIOPin& PC13 = GPIOC_Pins[ 13 ];
   GPIOPin& PC14 = GPIOC_Pins[ 14 ];  GPIOPin& PC15 = GPIOC_Pins[ 15 ];

//  - - - - - - - - - - - - - - - -  //
//  G P I O   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   iobase      periph                   id  name     pins */
   GPIO GPIOA( AHB1, GPIOA_BASE, RstClk::AHB1Periph_GPIOA, 0, "GPIOA", GPIOA_Pins );
   GPIO GPIOB( AHB1, GPIOB_BASE, RstClk::AHB1Periph_GPIOB, 1, "GPIOB", GPIOB_Pins );
   GPIO GPIOC( AHB1, GPIOC_BASE, RstClk::AHB1Periph_GPIOC, 2, "GPIOC", GPIOC_Pins );

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   iobase       periph                     name    rxPin txPin  IRQ number   alt. function */
   UART UART1( APB2, USART1_BASE, RstClk::APB2Periph_USART1, "UART1", PA10, PA9,  USART1_IRQn, GPIOPin::UART1 );
   UART UART2( APB1, USART2_BASE, RstClk::APB1Periph_USART2, "UART2", PA3,  PA2,  USART2_IRQn, GPIOPin::UART2 );
   UART UART3( APB1, USART3_BASE, RstClk::APB1Periph_USART3, "UART3", PB11, PB10, USART3_IRQn, GPIOPin::UART3 );
   UART UART4( APB1, UART4_BASE,  RstClk::APB1Periph_UART4,  "UART4", PA1,  PA0,  UART4_IRQn,  GPIOPin::UART4 );
 //UART UART5( APB1, UART5_BASE,  RstClk::APB1Periph_UART5,  "UART5", PD2,  PC12, UART5_IRQn,  GPIOPin::UART5 );
   UART UART6( APB2, USART6_BASE, RstClk::APB2Periph_USART6, "UART6", PC7,  PC6,  USART6_IRQn, GPIOPin::UART6 );

//  - - - - - - - - - - -  //
//  S P I   S T R E A M S  //
//  - - - - - - - - - - -  //

   /*
    *  See the STM32F4 reference manual for DMA stream/channel mappings,
    *  sec. 10.3.3 "Channel Selection", pp. 306-307
    */

   SPIStream SPI1_MISO( DMA2ST0, DMAStream::CH3, "SPI1MISO", PA6,  GPIOPin::SPI1 );
   SPIStream SPI1_MOSI( DMA2ST3, DMAStream::CH3, "SPI1MOSI", PA7,  GPIOPin::SPI1 );

   SPIStream SPI2_MISO( DMA1ST3, DMAStream::CH0, "SPI2MISO", PB14, GPIOPin::SPI2 );
   SPIStream SPI2_MOSI( DMA1ST4, DMAStream::CH0, "SPI2MOSI", PB15, GPIOPin::SPI2 );

   SPIStream SPI3_MISO( DMA1ST2, DMAStream::CH0, "SPI3MISO", PB4,  GPIOPin::SPI3 );
   SPIStream SPI3_MOSI( DMA1ST5, DMAStream::CH0, "SPI3MOSI", PB5,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph                   name    rx stream  tx stream  clk   alt. function */
   SPI SPI1( APB2, SPI1_BASE, RstClk::APB2Periph_SPI1, "SPI1", SPI1_MISO, SPI1_MOSI, PA5,  GPIOPin::SPI1 );
   SPI SPI2( APB1, SPI2_BASE, RstClk::APB1Periph_SPI2, "SPI2", SPI2_MISO, SPI2_MOSI, PB13, GPIOPin::SPI2 );
   SPI SPI3( APB1, SPI3_BASE, RstClk::APB1Periph_SPI3, "SPI3", SPI3_MISO, SPI3_MOSI, PB3,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - - -  //
//  A D C   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   STM32_ADC ADC1( APB2, ADC1_BASE, RstClk::APB2Periph_ADC1, "ADC1" );

//  - - - - - - - - - - - -  //
//  A D C   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   /*                       adc   name    channel#         pin */
   STM32_ADC::Channel SUN1( ADC1, "SUN1", STM32_ADC::CH9,  PB1 );
   STM32_ADC::Channel SUN2( ADC1, "SUN2", STM32_ADC::CH8,  PB0 );
   STM32_ADC::Channel SUN3( ADC1, "SUN3", STM32_ADC::CH15, PC5 );
   STM32_ADC::Channel SUN4( ADC1, "SUN4", STM32_ADC::CH14, PC4 );
   STM32_ADC::Channel SUN5( ADC1, "SUN5", STM32_ADC::CH4,  PA4 );
   STM32_ADC::Channel SUN6( ADC1, "SUN6", STM32_ADC::CH13, PC3 );
   STM32_ADC::Channel SUN7( ADC1, "SUN7", STM32_ADC::CH10, PC0 );
   STM32_ADC::Channel SUN8( ADC1, "SUN8", STM32_ADC::CH11, PC1 );
   STM32_ADC::Channel SUN9( ADC1, "SUN9", STM32_ADC::CH12, PC2 );

   /* aliases */

   STM32_ADC::Channel& GS1_1 = SUN1;
   STM32_ADC::Channel& GS1_2 = SUN2;
   STM32_ADC::Channel& GS2_1 = SUN3;
   STM32_ADC::Channel& GS2_2 = SUN4;
   STM32_ADC::Channel& GS3_1 = SUN5;
   STM32_ADC::Channel& GS3_2 = SUN6;
   STM32_ADC::Channel& GS4_1 = SUN7;
   STM32_ADC::Channel& GS4_2 = SUN8;
   STM32_ADC::Channel& GS5   = SUN9;

//  - - - - - - - - - - - - - - -  //
//  T I M   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*            bus   iobase     periph                   pin    Mode */
 //TIMER TIMER1( APB2, TIM1_BASE, RstClk::APB2Periph_TIM1, PB13,  GPIOPin::AF1);
 //TIMER TIMER2( APB1, TIM2_BASE, RstClk::APB1Periph_TIM2, PB11,  GPIOPin::AF1);

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   /*              SPI   name     csPin */
   A25Lxxx FLASH0( SPI3, "FLASH0", PA15 );

//  - - - - - - - - - - -  //
//        S T A T E        //
//  - - - - - - - - - - -  //

    Sat_state Current_state;
    Sat_raw   Current_raw;

} /* qb50 */


void USART1_IRQHandler( void )
{ qb50::UART1.isr(); }


/*EoF*/
