
#include "system/qb50.h"

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>

/* CMSIS is polluting the whole namespace with these macros... */

#undef DMA1
#undef DMA2

#undef SPI1
#undef SPI2
#undef SPI3

#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef GPIOD
#undef GPIOE

#undef UART4
#undef UART5

#undef NVIC


namespace qb50 {

//  - - - - - - - - - -  //
//  C O R E   B U S E S  //
//  - - - - - - - - - -  //

   /*       id */
   AHB AHB1( 1 );
   AHB AHB2( 2 );
   AHB AHB3( 3 );

   /*       id */
   APB APB1( 1 );
   APB APB2( 2 );

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   NVIC IRQ;

//  - - - - - - - - - - - -  //
//  D M A   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   static DMAStream DMA1_Streams[ 8 ] = {
      DMAStream( DMA1, DMA1_Stream0_BASE, DMA1_Stream0_IRQn, 0x00 ),
      DMAStream( DMA1, DMA1_Stream1_BASE, DMA1_Stream1_IRQn, 0x06 ),
      DMAStream( DMA1, DMA1_Stream2_BASE, DMA1_Stream2_IRQn, 0x10 ),
      DMAStream( DMA1, DMA1_Stream3_BASE, DMA1_Stream3_IRQn, 0x16 ),
      DMAStream( DMA1, DMA1_Stream4_BASE, DMA1_Stream4_IRQn, 0x20 ),
      DMAStream( DMA1, DMA1_Stream5_BASE, DMA1_Stream5_IRQn, 0x26 ),
      DMAStream( DMA1, DMA1_Stream6_BASE, DMA1_Stream6_IRQn, 0x30 ),
      DMAStream( DMA1, DMA1_Stream7_BASE, DMA1_Stream7_IRQn, 0x36 )
   };

   static DMAStream DMA2_Streams[ 8 ] = {
      DMAStream( DMA2, DMA2_Stream0_BASE, DMA2_Stream0_IRQn, 0x00 ),
      DMAStream( DMA2, DMA2_Stream1_BASE, DMA2_Stream1_IRQn, 0x06 ),
      DMAStream( DMA2, DMA2_Stream2_BASE, DMA2_Stream2_IRQn, 0x10 ),
      DMAStream( DMA2, DMA2_Stream3_BASE, DMA2_Stream3_IRQn, 0x16 ),
      DMAStream( DMA2, DMA2_Stream4_BASE, DMA2_Stream4_IRQn, 0x20 ),
      DMAStream( DMA2, DMA2_Stream5_BASE, DMA2_Stream5_IRQn, 0x26 ),
      DMAStream( DMA2, DMA2_Stream6_BASE, DMA2_Stream6_IRQn, 0x30 ),
      DMAStream( DMA2, DMA2_Stream7_BASE, DMA2_Stream7_IRQn, 0x36 )
   };

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph               streams */
   DMA DMA1( AHB1, DMA1_BASE, RCC_AHB1Periph_DMA1, DMA1_Streams );
   DMA DMA2( AHB1, DMA1_BASE, RCC_AHB1Periph_DMA2, DMA2_Streams );

//  - - - - - - - - -  //
//  G P I O   P I N S  //
//  - - - - - - - - -  //

   static GPIOPin GPIOA_Pins[ 16 ] = {
      GPIOPin( GPIOA,  0, 0x0001 ),  GPIOPin( GPIOA,  1, 0x0002 ),
      GPIOPin( GPIOA,  2, 0x0004 ),  GPIOPin( GPIOA,  3, 0x0008 ),
      GPIOPin( GPIOA,  4, 0x0010 ),  GPIOPin( GPIOA,  5, 0x0020 ),
      GPIOPin( GPIOA,  6, 0x0040 ),  GPIOPin( GPIOA,  7, 0x0080 ),
      GPIOPin( GPIOA,  8, 0x0100 ),  GPIOPin( GPIOA,  9, 0x0200 ),
      GPIOPin( GPIOA, 10, 0x0400 ),  GPIOPin( GPIOA, 11, 0x0800 ),
      GPIOPin( GPIOA, 12, 0x1000 ),  GPIOPin( GPIOA, 13, 0x2000 ),
      GPIOPin( GPIOA, 14, 0x4000 ),  GPIOPin( GPIOA, 15, 0x8000 )
   };

   static GPIOPin GPIOB_Pins[ 16 ] = {
      GPIOPin( GPIOB,  0, 0x0001 ),  GPIOPin( GPIOB,  1, 0x0002 ),
      GPIOPin( GPIOB,  2, 0x0004 ),  GPIOPin( GPIOB,  3, 0x0008 ),
      GPIOPin( GPIOB,  4, 0x0010 ),  GPIOPin( GPIOB,  5, 0x0020 ),
      GPIOPin( GPIOB,  6, 0x0040 ),  GPIOPin( GPIOB,  7, 0x0080 ),
      GPIOPin( GPIOB,  8, 0x0100 ),  GPIOPin( GPIOB,  9, 0x0200 ),
      GPIOPin( GPIOB, 10, 0x0400 ),  GPIOPin( GPIOB, 11, 0x0800 ),
      GPIOPin( GPIOB, 12, 0x1000 ),  GPIOPin( GPIOB, 13, 0x2000 ),
      GPIOPin( GPIOB, 14, 0x4000 ),  GPIOPin( GPIOB, 15, 0x8000 )
   };

   static GPIOPin GPIOC_Pins[ 16 ] = {
      GPIOPin( GPIOC,  0, 0x0001 ),  GPIOPin( GPIOC,  1, 0x0002 ),
      GPIOPin( GPIOC,  2, 0x0004 ),  GPIOPin( GPIOC,  3, 0x0008 ),
      GPIOPin( GPIOC,  4, 0x0010 ),  GPIOPin( GPIOC,  5, 0x0020 ),
      GPIOPin( GPIOC,  6, 0x0040 ),  GPIOPin( GPIOC,  7, 0x0080 ),
      GPIOPin( GPIOC,  8, 0x0100 ),  GPIOPin( GPIOC,  9, 0x0200 ),
      GPIOPin( GPIOC, 10, 0x0400 ),  GPIOPin( GPIOC, 11, 0x0800 ),
      GPIOPin( GPIOC, 12, 0x1000 ),  GPIOPin( GPIOC, 13, 0x2000 ),
      GPIOPin( GPIOC, 14, 0x4000 ),  GPIOPin( GPIOC, 15, 0x8000 )
   };

   static GPIOPin GPIOD_Pins[ 16 ] = {
      GPIOPin( GPIOD,  0, 0x0001 ),  GPIOPin( GPIOD,  1, 0x0002 ),
      GPIOPin( GPIOD,  2, 0x0004 ),  GPIOPin( GPIOD,  3, 0x0008 ),
      GPIOPin( GPIOD,  4, 0x0010 ),  GPIOPin( GPIOD,  5, 0x0020 ),
      GPIOPin( GPIOD,  6, 0x0040 ),  GPIOPin( GPIOD,  7, 0x0080 ),
      GPIOPin( GPIOD,  8, 0x0100 ),  GPIOPin( GPIOD,  9, 0x0200 ),
      GPIOPin( GPIOD, 10, 0x0400 ),  GPIOPin( GPIOD, 11, 0x0800 ),
      GPIOPin( GPIOD, 12, 0x1000 ),  GPIOPin( GPIOD, 13, 0x2000 ),
      GPIOPin( GPIOD, 14, 0x4000 ),  GPIOPin( GPIOD, 15, 0x8000 )
   };

   static GPIOPin GPIOE_Pins[ 16 ] = {
      GPIOPin( GPIOE,  0, 0x0001 ),  GPIOPin( GPIOE,  1, 0x0002 ),
      GPIOPin( GPIOE,  2, 0x0004 ),  GPIOPin( GPIOE,  3, 0x0008 ),
      GPIOPin( GPIOE,  4, 0x0010 ),  GPIOPin( GPIOE,  5, 0x0020 ),
      GPIOPin( GPIOE,  6, 0x0040 ),  GPIOPin( GPIOE,  7, 0x0080 ),
      GPIOPin( GPIOE,  8, 0x0100 ),  GPIOPin( GPIOE,  9, 0x0200 ),
      GPIOPin( GPIOE, 10, 0x0400 ),  GPIOPin( GPIOE, 11, 0x0800 ),
      GPIOPin( GPIOE, 12, 0x1000 ),  GPIOPin( GPIOE, 13, 0x2000 ),
      GPIOPin( GPIOE, 14, 0x4000 ),  GPIOPin( GPIOE, 15, 0x8000 )
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

   GPIOPin& PD0  = GPIOD_Pins[  0 ];  GPIOPin& PD1  = GPIOD_Pins[  1 ];
   GPIOPin& PD2  = GPIOD_Pins[  2 ];  GPIOPin& PD3  = GPIOD_Pins[  3 ];
   GPIOPin& PD4  = GPIOD_Pins[  4 ];  GPIOPin& PD5  = GPIOD_Pins[  5 ];
   GPIOPin& PD6  = GPIOD_Pins[  6 ];  GPIOPin& PD7  = GPIOD_Pins[  7 ];
   GPIOPin& PD8  = GPIOD_Pins[  8 ];  GPIOPin& PD9  = GPIOD_Pins[  9 ];
   GPIOPin& PD10 = GPIOD_Pins[ 10 ];  GPIOPin& PD11 = GPIOD_Pins[ 11 ];
   GPIOPin& PD12 = GPIOD_Pins[ 12 ];  GPIOPin& PD13 = GPIOD_Pins[ 13 ];
   GPIOPin& PD14 = GPIOD_Pins[ 14 ];  GPIOPin& PD15 = GPIOD_Pins[ 15 ];

   GPIOPin& PE0  = GPIOE_Pins[  0 ];  GPIOPin& PE1  = GPIOE_Pins[  1 ];
   GPIOPin& PE2  = GPIOE_Pins[  2 ];  GPIOPin& PE3  = GPIOE_Pins[  3 ];
   GPIOPin& PE4  = GPIOE_Pins[  4 ];  GPIOPin& PE5  = GPIOE_Pins[  5 ];
   GPIOPin& PE6  = GPIOE_Pins[  6 ];  GPIOPin& PE7  = GPIOE_Pins[  7 ];
   GPIOPin& PE8  = GPIOE_Pins[  8 ];  GPIOPin& PE9  = GPIOE_Pins[  9 ];
   GPIOPin& PE10 = GPIOE_Pins[ 10 ];  GPIOPin& PE11 = GPIOE_Pins[ 11 ];
   GPIOPin& PE12 = GPIOE_Pins[ 12 ];  GPIOPin& PE13 = GPIOE_Pins[ 13 ];
   GPIOPin& PE14 = GPIOE_Pins[ 14 ];  GPIOPin& PE15 = GPIOE_Pins[ 15 ];

//  - - - - - - - - - - - - - - - -  //
//  G P I O   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   iobase      periph                pins */
   GPIO GPIOA( AHB1, GPIOA_BASE, RCC_AHB1Periph_GPIOA, GPIOA_Pins );
   GPIO GPIOB( AHB1, GPIOB_BASE, RCC_AHB1Periph_GPIOB, GPIOB_Pins );
   GPIO GPIOC( AHB1, GPIOC_BASE, RCC_AHB1Periph_GPIOC, GPIOC_Pins );
   GPIO GPIOD( AHB1, GPIOD_BASE, RCC_AHB1Periph_GPIOD, GPIOD_Pins );
   GPIO GPIOE( AHB1, GPIOE_BASE, RCC_AHB1Periph_GPIOE, GPIOE_Pins );

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   iobase       periph                rxPin txPin  IRQ number   alt. function */
   UART UART1( APB2, USART1_BASE, RCC_APB2Periph_USART1, PB7,  PB6,  USART1_IRQn, GPIOPin::UART1 );
   UART UART2( APB1, USART2_BASE, RCC_APB1Periph_USART2, PA3,  PA2,  USART2_IRQn, GPIOPin::UART2 );
   UART UART3( APB1, USART3_BASE, RCC_APB1Periph_USART3, PB11, PB10, USART3_IRQn, GPIOPin::UART3 );
   UART UART4( APB1, UART4_BASE,  RCC_APB1Periph_UART4,  PA1,  PA0,  UART4_IRQn,  GPIOPin::UART4 );
   UART UART5( APB1, UART5_BASE,  RCC_APB1Periph_UART5,  PD2,  PC12, UART5_IRQn,  GPIOPin::UART5 );
   UART UART6( APB2, USART6_BASE, RCC_APB2Periph_USART6, PC7,  PC6,  USART6_IRQn, GPIOPin::UART6 );

//  - - - - - - - - - - -  //
//  S P I   S T R E A M S  //
//  - - - - - - - - - - -  //

   /*
    *  See the STM32F4 reference manual for DMA stream/channel mappings,
    *  sec. 10.3.3 "Channel Selection", pp. 306-307
    */

   SPIStream SPI1_MISO( DMA2.streams[ 0 ], DMAStream::CH3, PA6,  GPIOPin::SPI1 );
   SPIStream SPI1_MOSI( DMA2.streams[ 3 ], DMAStream::CH3, PA7,  GPIOPin::SPI1 );

   SPIStream SPI2_MISO( DMA1.streams[ 3 ], DMAStream::CH0, PB14, GPIOPin::SPI2 );
   SPIStream SPI2_MOSI( DMA1.streams[ 4 ], DMAStream::CH0, PB15, GPIOPin::SPI2 );

   SPIStream SPI3_MISO( DMA1.streams[ 2 ], DMAStream::CH0, PB4,  GPIOPin::SPI3 );
   SPIStream SPI3_MOSI( DMA1.streams[ 5 ], DMAStream::CH0, PB5,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph               rx stream  tx stream  clk   alt. function */
   SPI SPI1( APB2, SPI1_BASE, RCC_APB2Periph_SPI1, SPI1_MISO, SPI1_MOSI, PA5,  GPIOPin::SPI1 );
   SPI SPI2( APB1, SPI2_BASE, RCC_APB1Periph_SPI2, SPI2_MISO, SPI2_MOSI, PB13, GPIOPin::SPI2 );
   SPI SPI3( APB1, SPI3_BASE, RCC_APB1Periph_SPI3, SPI3_MISO, SPI3_MOSI, PB3,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   /*               SPI  csPin */
   A25Lxxx softMem( SPI3, PA0 );  /* mémoire soft    */
   A25Lxxx dataMem( SPI3, PA7 );  /* mémoire données */

//  - - - - - - - - - - -  //
//  O N B O A R D   A D C  //
//  - - - - - - - - - - -  //

   /*              SPI  csPin */
   MAX111x maxADC( SPI3, PA6 );

} /* qb50 */

/*EoF*/
