
#include "device/SPI.h"
#include "device/GPIO.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

SPI::SPI( Bus&           bus,
          const uint32_t periph,
          const uint32_t iobase,
          DMAChannel&    ch1,
          DMAChannel&    ch2 )
   : CoreDevice( bus, periph, iobase ),
     _ch1( ch1 ),
     _ch2( ch2 )
{
   _lock    = xSemaphoreCreateMutex();
   _isrRXNE = xSemaphoreCreateBinary();
   _isrTXE  = xSemaphoreCreateBinary();

   reset();
}


SPI::~SPI()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

void SPI::reset( void )
{ ; }


void SPI::enable( void )
{
   bus.enable( this );

   setupGPIO();
   setupNVIC();

   SPI_I2S_DeInit(( SPI_TypeDef* )iobase );
   SPI_StructInit( &SPIis );

   SPIis.SPI_Mode              = SPI_Mode_Master;
   SPIis.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
   SPIis.SPI_CPOL              = SPI_CPOL_Low;
   SPIis.SPI_CPHA              = SPI_CPHA_1Edge;
   SPIis.SPI_DataSize          = SPI_DataSize_8b;
   SPIis.SPI_NSS               = SPI_NSS_Soft;
   SPIis.SPI_FirstBit          = SPI_FirstBit_MSB;
   SPIis.SPI_CRCPolynomial     = 7;
 //SPIis.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
   SPIis.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;

   switch( periph ) {

      case RCC_APB2Periph_SPI1:
         GPIOA.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOA_BASE, &GPIOis );

         PA5.alt( GPIO_AF_SPI1 );
         PA6.alt( GPIO_AF_SPI1 );
         PA7.alt( GPIO_AF_SPI1 );

         break;

      case RCC_APB1Periph_SPI2:
         GPIOB.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOB_BASE, &GPIOis );

         PB13.alt( GPIO_AF_SPI2 );
         PB14.alt( GPIO_AF_SPI2 );
         PB15.alt( GPIO_AF_SPI2 );

         break;

      case RCC_APB1Periph_SPI3:
         GPIOB.enable();
         GPIO_Init(( GPIO_TypeDef* )GPIOB_BASE, &GPIOis );

         PB3.alt( GPIO_AF_SPI3 );
         PB4.alt( GPIO_AF_SPI3 );
         PB5.alt( GPIO_AF_SPI3 );

         break;

      default:
         throw( 42 );  /* XXX */
   }

   SPI_Init(( SPI_TypeDef* )iobase, &SPIis );

   // SPI_ITConfig(( SPI_TypeDef* )iobase, SPI_IT_TXE, ENABLE );
   // SPI_ITConfig(( SPI_TypeDef* )iobase, SPI_IT_RXNE, ENABLE );
   // NVIC_Init( &NVICis );

   SPI_Cmd(( SPI_TypeDef* )iobase, ENABLE );
}


void SPI::disable( void )
{ bus.disable( this ); }


size_t SPI::xfer( const void *src, void *dst, size_t len, bool useDMA )
{
   size_t n;

   // acquire the lock

   xSemaphoreTake( _lock, portMAX_DELAY );

   // perform the write

   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;

   for( n = 0 ; n < len ; ++n ) {
      while(( SPIx->SR & SPI_I2S_FLAG_TXE ) == RESET );
      if( src == NULL ) {
         SPIx->DR = 0xffff;
      } else {
         SPIx->DR = ((uint8_t*)src)[ n ];
      }

      while(( SPIx->SR & SPI_I2S_FLAG_RXNE ) == RESET );
      if( dst != NULL ) {
         ((uint8_t*)dst)[ n ] = SPIx->DR;
      }
   }

   // release the lock

   xSemaphoreGive( _lock );

   return n;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void SPI::setupGPIO( void )
{
   GPIOis.GPIO_Mode  = GPIO_Mode_AF;
   GPIOis.GPIO_Speed = GPIO_Speed_50MHz;
   GPIOis.GPIO_OType = GPIO_OType_PP;
   GPIOis.GPIO_PuPd  = GPIO_PuPd_NOPULL;

   switch( periph ) {

      case RCC_APB2Periph_SPI1:

         GPIOis.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
         break;

      case RCC_APB1Periph_SPI2:

         GPIOis.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
         break;

      case RCC_APB1Periph_SPI3:

         GPIOis.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
         break;

      default:
         ;
   }
}


void SPI::setupNVIC( void )
{
   NVICis.NVIC_IRQChannelPreemptionPriority = 0x0f;
   NVICis.NVIC_IRQChannelSubPriority        = 0x00;
   NVICis.NVIC_IRQChannelCmd                = ENABLE;

   switch( periph ) {

      case RCC_APB2Periph_SPI1:

         NVICis.NVIC_IRQChannel = SPI1_IRQn;
         break;

      case RCC_APB1Periph_SPI2:

         NVICis.NVIC_IRQChannel = SPI2_IRQn;
         break;

      case RCC_APB1Periph_SPI3:

         NVICis.NVIC_IRQChannel = SPI3_IRQn;
         break;

      default:
         ;
   }
}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void SPI::isr( void )
{
#if 0
   SPI_TypeDef *SPIx = (SPI_TypeDef*)iobase;
   portBASE_TYPE hpTask  = pdFALSE;
   uint16_t SR = SPIx->SR;

   if( SR & SPI_FLAG_RXNE ) {
      SPIx->SR &= ~SPI_FLAG_RXNE;
      xSemaphoreGiveFromISR( _isrRXNE, &hpTask );
   }

   if( SR & SPI_FLAG_TXE ) {
      SPIx->SR &= ~SPI_FLAG_TXE;
      xSemaphoreGiveFromISR( _isrTXE, &hpTask );
      SPIx->CR1 &= ~SPI_FLAG_TXE;
   }

   if( hpTask == pdTRUE )
      portEND_SWITCHING_ISR( hpTask );
#endif
}


void SPI1_IRQHandler( void )
{ qb50::SPI1.isr(); }


/* trampolines */

void SPI2_IRQHandler( void )
{ qb50::SPI2.isr(); }

void SPI3_IRQHandler( void )
{ qb50::SPI3.isr(); }


/*EoF*/
