
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

   RstClk RCC( RCC_BASE, "RCC" );

//  - - - - - - - - - - - - - - - - - - - -  //
//  I N T E R R U P T   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - - - - - -  //

   NVIC IRQ;
   EXTI EXTI1;

//  - - - - - - - - - - - - - - - -  //
//  P O W E R   C O N T R O L L E R  //
//  - - - - - - - - - - - - - - - -  //

   Power PWR( APB1, PWR_BASE, RstClk::APB1Periph_PWR, "PWR" );

//  - - - - - - - - - - -  //
//  B A C K U P   S R A M  //
//  - - - - - - - - - - -  //

   Backup BKP( AHB1, BKPSRAM_BASE, RstClk::AHB1Periph_BKPSRAM, "BKP" );

//  - - - - - - - - - - - - - - -  //
//  D M A   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph                name */
   DMA DMA1( AHB1, DMA1_BASE, RstClk::AHB1Periph_DMA1, "DMA1" );

//  - - - - - - - - - - -  //
//  D M A   S T R E A M S  //
//  - - - - - - - - - - -  //

   DMAStream DMA1ST2( DMA1, DMA1_Stream2_BASE, DMA1_Stream2_IRQn, "DMA1ST2", 0x10 );
   DMAStream DMA1ST5( DMA1, DMA1_Stream5_BASE, DMA1_Stream5_IRQn, "DMA1ST5", 0x26 );

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

   /*          bus   iobase      periph                id  name     pins */
   GPIO GPIOA( AHB1, GPIOA_BASE, RstClk::AHB1Periph_GPIOA, 0, "GPIOA", GPIOA_Pins );
   GPIO GPIOB( AHB1, GPIOB_BASE, RstClk::AHB1Periph_GPIOB, 1, "GPIOB", GPIOB_Pins );
   GPIO GPIOC( AHB1, GPIOC_BASE, RstClk::AHB1Periph_GPIOC, 2, "GPIOC", GPIOC_Pins );

//  - - - - - - - - - - - - - - - -  //
//  U A R T   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - - -  //

   /*          bus   iobase       periph                  name    rxPin txPin  IRQ number   alt. function */
   UART UART1( APB2, USART1_BASE, RstClk::APB2Periph_USART1, "UART1", PB7,  PB6,  USART1_IRQn, GPIOPin::UART1 );
   UART UART2( APB1, USART2_BASE, RstClk::APB1Periph_USART2, "UART2", PA3,  PA2,  USART2_IRQn, GPIOPin::UART2 );
   UART UART3( APB1, USART3_BASE, RstClk::APB1Periph_USART3, "UART3", PB11, PB10, USART3_IRQn, GPIOPin::UART3 );
   UART UART6( APB2, USART6_BASE, RstClk::APB2Periph_USART6, "UART6", PC7,  PC6,  USART6_IRQn, GPIOPin::UART6 );

//  - - - - - - - - - - -  //
//  S P I   S T R E A M S  //
//  - - - - - - - - - - -  //

   /*
    *  See the STM32F4 reference manual for DMA stream/channel mappings,
    *  sec. 10.3.3 "Channel Selection", pp. 306-307
    */

   SPIStream SPI3_MISO( DMA1ST2, DMAStream::CH0, "SPI3MISO", PB4,  GPIOPin::SPI3 );
   SPIStream SPI3_MOSI( DMA1ST5, DMAStream::CH0, "SPI3MOSI", PB5,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - - -  //
//  S P I   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*        bus   iobase     periph                name    rx stream  tx stream  clk   alt. function */
   SPI SPI3( APB1, SPI3_BASE, RstClk::APB1Periph_SPI3, "SPI3", SPI3_MISO, SPI3_MOSI, PB3,  GPIOPin::SPI3 );

//  - - - - - - - - - - - - - -  //
//  O N B O A R D   M E M O R Y  //
//  - - - - - - - - - - - - - -  //

   /*              SPI    name    csPin */
   A25Lxxx FLASH0( SPI3, "FLASH0", PA0 /*CS6*/ );  /* U9 - "mémoire soft"    */
   A25Lxxx FLASH1( SPI3, "FLASH1", PA7 /*CS4*/ );  /* U5 - "mémoire données" */

   static FlashMemory *VFLASH_Memories[ 2 ] = { &FLASH0, &FLASH1 };

   FlashArray VFLASH( "VFLASH", 2, VFLASH_Memories );

   ConfSlice  CONF( "CONF",  VFLASH, 0,    1 );
 //Slice     WODEX( "WODEX", VFLASH, 1, 2047 );

//  - - - - - - - - - - - - - - -  //
//  A D C   C O N T R O L L E R S  //
//  - - - - - - - - - - - - - - -  //

   /*            SPI    name  csPin */
   MAX111x ADC1( SPI3, "ADC1", PA4 /*CS1*/ ); /* ADC carte energie (U5@PMU)   */
   MAX111x ADC2( SPI3, "ADC2", PA5 /*CS2*/ ); /* ADC carte energie (U6@PMU)   */
   MAX111x ADC3( SPI3, "ADC3", PA6 /*CS3*/ ); /* ADC carte ODB     (U7@ODB)   */
   MAX111x ADC4( SPI3, "ADC4", PC4 /*CS4*/ ); /* ADC carte FiPEX   (U2@FiPEX) */

//  - - - - - - - - - - - -  //
//  A D C   C H A N N E L S  //
//  - - - - - - - - - - - -  //

   static ADCChannel ADC1_Channels[ 8 ] = {
      ADCChannel( ADC1, MAX111x::CH0, "ADC1CH0", 4.404494 ), /* V4 */
      ADCChannel( ADC1, MAX111x::CH1, "ADC1CH1", 0.266667 ), /* I4 */
      ADCChannel( ADC1, MAX111x::CH2, "ADC1CH2", 2.0      ), /* T4 */
      ADCChannel( ADC1, MAX111x::CH3, "ADC1CH3", 4.404494 ), /* V1 */
      ADCChannel( ADC1, MAX111x::CH4, "ADC1CH4", 2.0      ), /* T1 */
      ADCChannel( ADC1, MAX111x::CH5, "ADC1CH5", 0.266667 ), /* I1 */
      ADCChannel( ADC1, MAX111x::CH6, "ADC1CH6", 0.2      ), /* T_Bat */
      ADCChannel( ADC1, MAX111x::CH7, "ADC1CH7", 4.404494 )  /* V_Bat */
   };

   static ADCChannel ADC2_Channels[ 8 ] = {
      ADCChannel( ADC2, MAX111x::CH0, "ADC2CH0", 4.404494 ), /* V2 */
      ADCChannel( ADC2, MAX111x::CH1, "ADC2CH1", 2.0      ), /* T2 */
      ADCChannel( ADC2, MAX111x::CH2, "ADC2CH2", 0.266667 ), /* I2 */
      ADCChannel( ADC2, MAX111x::CH3, "ADC2CH3", 4.404494 ), /* V3 */
      ADCChannel( ADC2, MAX111x::CH4, "ADC2CH4", 2.0      ), /* T3 */
      ADCChannel( ADC2, MAX111x::CH5, "ADC2CH5", 0.266667 ), /* I3 */
      ADCChannel( ADC2, MAX111x::CH6, "ADC2CH6", 0.2      ), /* I_surt */
      ADCChannel( ADC2, MAX111x::CH7, "ADC2CH7", 0.0      )  /* not used */
   };

   static ADCChannel ADC3_Channels[ 8 ] = {
      ADCChannel( ADC3, MAX111x::CH0, "ADC3CH0", 0.17     ), /* I_ADCS */
      ADCChannel( ADC3, MAX111x::CH1, "ADC3CH1", 1.0      ), /* T_ARM_ODB */
      ADCChannel( ADC3, MAX111x::CH2, "ADC3CH2", 0.053333 ), /* I_RX */
      ADCChannel( ADC3, MAX111x::CH3, "ADC3CH3", 1.0      ), /* RSSI */
      ADCChannel( ADC3, MAX111x::CH4, "ADC3CH4", 0.4      ), /* I_TX */
      ADCChannel( ADC3, MAX111x::CH5, "ADC3CH5", 1.0      ), /* P_TX (mW) */
      ADCChannel( ADC3, MAX111x::CH6, "ADC3CH6", 1.0      ), /* P_PA (mW) */
      ADCChannel( ADC3, MAX111x::CH7, "ADC3CH7", 0.2      )  /* T_PA */
   };

   static ADCChannel ADC4_Channels[ 8 ] = {
      ADCChannel( ADC4, MAX111x::CH0, "ADC4CH0", 0.0      ), /* not used (I_ADCS) */
      ADCChannel( ADC4, MAX111x::CH1, "ADC4CH1", 0.24     ), /* I_GPS */
      ADCChannel( ADC4, MAX111x::CH2, "ADC4CH2", 0.0      ), /* not used */
      ADCChannel( ADC4, MAX111x::CH3, "ADC4CH3", 0.026667 ), /* I_3V3_FIPEX */
      ADCChannel( ADC4, MAX111x::CH4, "ADC4CH4", 2.0      ), /* V_3V3_FIPEX */
      ADCChannel( ADC4, MAX111x::CH5, "ADC4CH5", 0.2424   ), /* I_5V_FIPEX */
      ADCChannel( ADC4, MAX111x::CH6, "ADC4CH6", 4.404494 ), /* V_5V_FIPEX */
      ADCChannel( ADC4, MAX111x::CH7, "ADC4CH7", 1.0      )  /* SU_TH_G0 */
   };

   /* aliases */

   ADCChannel& ADC1CH0 = ADC1_Channels[ 0 ];  ADCChannel& ADC1CH1 = ADC1_Channels[ 1 ];
   ADCChannel& ADC1CH2 = ADC1_Channels[ 2 ];  ADCChannel& ADC1CH3 = ADC1_Channels[ 3 ];
   ADCChannel& ADC1CH4 = ADC1_Channels[ 4 ];  ADCChannel& ADC1CH5 = ADC1_Channels[ 5 ];
   ADCChannel& ADC1CH6 = ADC1_Channels[ 6 ];  ADCChannel& ADC1CH7 = ADC1_Channels[ 7 ];

   ADCChannel& ADC2CH0 = ADC2_Channels[ 0 ];  ADCChannel& ADC2CH1 = ADC2_Channels[ 1 ];
   ADCChannel& ADC2CH2 = ADC2_Channels[ 2 ];  ADCChannel& ADC2CH3 = ADC2_Channels[ 3 ];
   ADCChannel& ADC2CH4 = ADC2_Channels[ 4 ];  ADCChannel& ADC2CH5 = ADC2_Channels[ 5 ];
   ADCChannel& ADC2CH6 = ADC2_Channels[ 6 ];  ADCChannel& ADC2CH7 = ADC2_Channels[ 7 ];

   ADCChannel& ADC3CH0 = ADC3_Channels[ 0 ];  ADCChannel& ADC3CH1 = ADC3_Channels[ 1 ];
   ADCChannel& ADC3CH2 = ADC3_Channels[ 2 ];  ADCChannel& ADC3CH3 = ADC3_Channels[ 3 ];
   ADCChannel& ADC3CH4 = ADC3_Channels[ 4 ];  ADCChannel& ADC3CH5 = ADC3_Channels[ 5 ];
   ADCChannel& ADC3CH6 = ADC3_Channels[ 6 ];  ADCChannel& ADC3CH7 = ADC3_Channels[ 7 ];

   ADCChannel& ADC4CH0 = ADC4_Channels[ 0 ];  ADCChannel& ADC4CH1 = ADC4_Channels[ 1 ];
   ADCChannel& ADC4CH2 = ADC4_Channels[ 2 ];  ADCChannel& ADC4CH3 = ADC4_Channels[ 3 ];
   ADCChannel& ADC4CH4 = ADC4_Channels[ 4 ];  ADCChannel& ADC4CH5 = ADC4_Channels[ 5 ];
   ADCChannel& ADC4CH6 = ADC4_Channels[ 6 ];  ADCChannel& ADC4CH7 = ADC4_Channels[ 7 ];

//  - - - - - - - - - - - - -  //
//  P O W E R   M A N A G E R  //
//  - - - - - - - - - - - - -  //

   PMU PMU0( "PMU0" ); /* XXX thread */

//  - - - - - - - - - - -  //
//  T R A N S C E I V E R  //
//  - - - - - - - - - - -  //

   Transceiver RFTX( "RFTX", PB15, PB13 );

//  - - - - -  //
//  A X . 2 5  //
//  - - - - -  //

   //AX25Out ax25( PC9, PC8 );

//  - - - - - - - - - -  //
//  P A R A M E T E R S  //
//  - - - - - - - - - -  //

   Parameters PARAMS;

//  - - -  //
//  O D B  //
//  - - -  //

   ODB SAT( "QB50", PC11, PA11, PA15 );

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
