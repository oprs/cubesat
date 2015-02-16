
#include "system/qb50.h"


namespace qb50 {

//  - - - - - - - - - -  //
//  C O R E   B U S E S  //
//  - - - - - - - - - -  //

   /*       id */
   AHB AHB1( 0 );
   AHB AHB2( 1 );
   AHB AHB3( 2 );

   /*       id */
   APB APB1( 0 );
   APB APB2( 1 );

//  - - - - - - - - - - - -  //
//  D M A   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   static DMAChannel DMA1_Channels[ 8 ] = {
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream0_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream1_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream2_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream3_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream4_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream5_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream6_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA1, DMA1_Stream7_BASE )
   };

   static DMAChannel DMA2_Channels[ 8 ] = {
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream0_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream1_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream2_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream3_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream4_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream5_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream6_BASE ),
      DMAChannel( AHB1, RCC_AHB1Periph_DMA2, DMA2_Stream7_BASE )
   };

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   periph               iobase     channels */
   DMA DMA1( AHB1, RCC_AHB1Periph_DMA1, DMA1_BASE, DMA1_Channels );
   DMA DMA2( AHB1, RCC_AHB1Periph_DMA2, DMA2_BASE, DMA2_Channels );

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

   GPIOPin& PA0  = GPIOA_Pins[  0 ];
   GPIOPin& PA1  = GPIOA_Pins[  1 ];
   GPIOPin& PA2  = GPIOA_Pins[  2 ];
   GPIOPin& PA3  = GPIOA_Pins[  3 ];
   GPIOPin& PA4  = GPIOA_Pins[  4 ];
   GPIOPin& PA5  = GPIOA_Pins[  5 ];
   GPIOPin& PA6  = GPIOA_Pins[  6 ];
   GPIOPin& PA7  = GPIOA_Pins[  7 ];
   GPIOPin& PA8  = GPIOA_Pins[  8 ];
   GPIOPin& PA9  = GPIOA_Pins[  9 ];
   GPIOPin& PA10 = GPIOA_Pins[ 10 ];
   GPIOPin& PA11 = GPIOA_Pins[ 11 ];
   GPIOPin& PA12 = GPIOA_Pins[ 12 ];
   GPIOPin& PA13 = GPIOA_Pins[ 13 ];
   GPIOPin& PA14 = GPIOA_Pins[ 14 ];
   GPIOPin& PA15 = GPIOA_Pins[ 15 ];

   GPIOPin& PB0  = GPIOB_Pins[  0 ];
   GPIOPin& PB1  = GPIOB_Pins[  1 ];
   GPIOPin& PB2  = GPIOB_Pins[  2 ];
   GPIOPin& PB3  = GPIOB_Pins[  3 ];
   GPIOPin& PB4  = GPIOB_Pins[  4 ];
   GPIOPin& PB5  = GPIOB_Pins[  5 ];
   GPIOPin& PB6  = GPIOB_Pins[  6 ];
   GPIOPin& PB7  = GPIOB_Pins[  7 ];
   GPIOPin& PB8  = GPIOB_Pins[  8 ];
   GPIOPin& PB9  = GPIOB_Pins[  9 ];
   GPIOPin& PB10 = GPIOB_Pins[ 10 ];
   GPIOPin& PB11 = GPIOB_Pins[ 11 ];
   GPIOPin& PB12 = GPIOB_Pins[ 12 ];
   GPIOPin& PB13 = GPIOB_Pins[ 13 ];
   GPIOPin& PB14 = GPIOB_Pins[ 14 ];
   GPIOPin& PB15 = GPIOB_Pins[ 15 ];

   GPIOPin& PC0  = GPIOC_Pins[  0 ];
   GPIOPin& PC1  = GPIOC_Pins[  1 ];
   GPIOPin& PC2  = GPIOC_Pins[  2 ];
   GPIOPin& PC3  = GPIOC_Pins[  3 ];
   GPIOPin& PC4  = GPIOC_Pins[  4 ];
   GPIOPin& PC5  = GPIOC_Pins[  5 ];
   GPIOPin& PC6  = GPIOC_Pins[  6 ];
   GPIOPin& PC7  = GPIOC_Pins[  7 ];
   GPIOPin& PC8  = GPIOC_Pins[  8 ];
   GPIOPin& PC9  = GPIOC_Pins[  9 ];
   GPIOPin& PC10 = GPIOC_Pins[ 10 ];
   GPIOPin& PC11 = GPIOC_Pins[ 11 ];
   GPIOPin& PC12 = GPIOC_Pins[ 12 ];
   GPIOPin& PC13 = GPIOC_Pins[ 13 ];
   GPIOPin& PC14 = GPIOC_Pins[ 14 ];
   GPIOPin& PC15 = GPIOC_Pins[ 15 ];

   GPIOPin& PD0  = GPIOD_Pins[  0 ];
   GPIOPin& PD1  = GPIOD_Pins[  1 ];
   GPIOPin& PD2  = GPIOD_Pins[  2 ];
   GPIOPin& PD3  = GPIOD_Pins[  3 ];
   GPIOPin& PD4  = GPIOD_Pins[  4 ];
   GPIOPin& PD5  = GPIOD_Pins[  5 ];
   GPIOPin& PD6  = GPIOD_Pins[  6 ];
   GPIOPin& PD7  = GPIOD_Pins[  7 ];
   GPIOPin& PD8  = GPIOD_Pins[  8 ];
   GPIOPin& PD9  = GPIOD_Pins[  9 ];
   GPIOPin& PD10 = GPIOD_Pins[ 10 ];
   GPIOPin& PD11 = GPIOD_Pins[ 11 ];
   GPIOPin& PD12 = GPIOD_Pins[ 12 ];
   GPIOPin& PD13 = GPIOD_Pins[ 13 ];
   GPIOPin& PD14 = GPIOD_Pins[ 14 ];
   GPIOPin& PD15 = GPIOD_Pins[ 15 ];

   GPIOPin& PE0  = GPIOE_Pins[  0 ];
   GPIOPin& PE1  = GPIOE_Pins[  1 ];
   GPIOPin& PE2  = GPIOE_Pins[  2 ];
   GPIOPin& PE3  = GPIOE_Pins[  3 ];
   GPIOPin& PE4  = GPIOE_Pins[  4 ];
   GPIOPin& PE5  = GPIOE_Pins[  5 ];
   GPIOPin& PE6  = GPIOE_Pins[  6 ];
   GPIOPin& PE7  = GPIOE_Pins[  7 ];
   GPIOPin& PE8  = GPIOE_Pins[  8 ];
   GPIOPin& PE9  = GPIOE_Pins[  9 ];
   GPIOPin& PE10 = GPIOE_Pins[ 10 ];
   GPIOPin& PE11 = GPIOE_Pins[ 11 ];
   GPIOPin& PE12 = GPIOE_Pins[ 12 ];
   GPIOPin& PE13 = GPIOE_Pins[ 13 ];
   GPIOPin& PE14 = GPIOE_Pins[ 14 ];
   GPIOPin& PE15 = GPIOE_Pins[ 15 ];

//  - - - - - - - - - - - - - - - -  //
//  G P I O   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   periph                iobase      pins */
   GPIO GPIOA( AHB1, RCC_AHB1Periph_GPIOA, GPIOA_BASE, GPIOA_Pins );
   GPIO GPIOB( AHB1, RCC_AHB1Periph_GPIOB, GPIOB_BASE, GPIOB_Pins );
   GPIO GPIOC( AHB1, RCC_AHB1Periph_GPIOC, GPIOC_BASE, GPIOC_Pins );
   GPIO GPIOD( AHB1, RCC_AHB1Periph_GPIOD, GPIOD_BASE, GPIOD_Pins );
   GPIO GPIOE( AHB1, RCC_AHB1Periph_GPIOE, GPIOE_BASE, GPIOE_Pins );

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   periph                 iobase       rxPin txPin */
   UART UART1( APB2, RCC_APB2Periph_USART1, USART1_BASE, PB7,  PB6  );
   UART UART2( APB1, RCC_APB1Periph_USART2, USART2_BASE, PA3,  PA2  );
   UART UART3( APB1, RCC_APB1Periph_USART3, USART3_BASE, PB11, PB10 );
   UART UART4( APB1, RCC_APB1Periph_UART4,  UART4_BASE,  PA1,  PA0  );
 //UART UART5( APB1, RCC_APB1Periph_UART5,  UART5_BASE,  PD2,  PC12 );
   UART UART6( APB2, RCC_APB2Periph_USART6, USART6_BASE, PC7,  PC6  );

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   periph               iobase     MISO channel  MOSI channel */
   SPI SPI1( APB2, RCC_APB2Periph_SPI1, SPI1_BASE, DMA2.chan[0], DMA2.chan[1] );
   SPI SPI2( APB1, RCC_APB1Periph_SPI2, SPI2_BASE, DMA1.chan[0], DMA1.chan[1] );
   SPI SPI3( APB1, RCC_APB1Periph_SPI3, SPI3_BASE, DMA1.chan[0], DMA1.chan[1] );

//  - - - - - - - - - - - - - - -  //
//  E X T E R N A L   M E M O R Y  //
//  - - - - - - - - - - - - - - -  //

   /*             id */
   EXTMEM EXTMEM1( 0 );
   EXTMEM EXTMEM2( 1 );

} /* qb50 */

/*EoF*/
