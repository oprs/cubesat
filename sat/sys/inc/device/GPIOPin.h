
#ifndef _QB50_SYS_GPIO_PIN_H
#define _QB50_SYS_GPIO_PIN_H

#include "GPIO.h"


namespace qb50 {

   class GPIOPin : public Device
   {

      public:

         GPIOPin( GPIO& gpio, const unsigned id, const char *name, const uint16_t mask );
         ~GPIOPin();

         GPIOPin& init   ( void );
         GPIOPin& enable ( bool silent = false );
         GPIOPin& disable( bool silent = false );

         GPIOPin& on     ( void );
         GPIOPin& off    ( void );
         GPIOPin& toggle ( void );
         bool     read   ( void );

         /* mode */

         enum Mode {
            INPUT     = 0x00,
            OUTPUT    = 0x01,
            ALTERNATE = 0x02,
            ANALOG    = 0x03
         };

         unsigned      id ( void ) const { return _id; }
         unsigned  portId ( void ) const { return _gpio.id(); }

         GPIOPin& mode   ( Mode mode );

         GPIOPin& in     ( void ) { return mode( INPUT  ); }
         GPIOPin& out    ( void ) { return mode( OUTPUT ); }
         GPIOPin& analog ( void ) { return mode( ANALOG ); }

         /* alternate function mapping */

         enum Alt {
            AF0  = 0x00, RTC_50Hz = AF0,
                         MCO      = AF0,
                         TAMPER   = AF0,
                         SWJ      = AF0,
                         TRACE    = AF0,
            AF1  = 0x01, TIM1     = AF1,
                         TIM2     = AF1,
            AF2  = 0x02, TIM3     = AF2,
                         TIM4     = AF2,
                         TIM5     = AF2,
            AF3  = 0x03, TIM8     = AF3,
                         TIM9     = AF3,
                         TIM10    = AF3,
                         TIM11    = AF3,
            AF4  = 0x04, I2C1     = AF4,
                         I2C2     = AF4,
                         I2C3     = AF4,
            AF5  = 0x05, SPI1     = AF5,
                         SPI2     = AF5,
            AF6  = 0x06, SPI3     = AF6,
            AF7  = 0x07, UART1    = AF7,
                         UART2    = AF7,
                         UART3    = AF7,
            AF8  = 0x08, UART4    = AF8,
                         UART5    = AF8,
                         UART6    = AF8,
            AF9  = 0x09, CAN1     = AF9,
                         CAN2     = AF9,
                         TIM12    = AF9,
                         TIM13    = AF9,
                         TIM14    = AF9,
            AF10 = 0x0a, OTG_FS   = AF10,
                         OTG_HS   = AF10,
            AF11 = 0x0b, ETH      = AF11,
            AF12 = 0x0c, FSMC     = AF12,
                         OTG_HSFS = AF12,
                         OTG_SDIO = AF12,
            AF13 = 0x0d, DCMI     = AF13,
            AF14 = 0x0e,
            AF15 = 0x0f, EVENTOUT = AF15
         };

         GPIOPin& alt ( Alt alt );

         /* output speed */

         enum OSpeed {
            SLOW         = 0x00, /*   2MHz */
            MEDIUM       = 0x01, /*  25MHz */
            FAST         = 0x02, /*  50MHz */
            HIGH         = 0x03  /* 100MHz */
         };

         GPIOPin& oSpeed ( OSpeed speed );

         /* output type */

         enum OType {
            PUSHPULL     = 0x00,
            OPENDRAIN    = 0x01
         };

         GPIOPin& oType  ( OType type );

         /* pull-up / pull-down */

         enum PullUpDn {
            NOPULL       = 0x00,
            PULLUP       = 0x01,
            PULLDN       = 0x02
         };

         GPIOPin& PuPd   ( PullUpDn pud );

         GPIOPin& noPull ( void ) { return PuPd( NOPULL ); }
         GPIOPin& pullUp ( void ) { return PuPd( PULLUP ); }
         GPIOPin& pullDn ( void ) { return PuPd( PULLDN ); }

            /* Channel Definitions for ADC */

      enum Channel {
         CH0  = 0x00,
         CH1  = 0x01,
         CH2  = 0x02,
         CH3  = 0x03,
         CH4  = 0x04,
         CH5  = 0x05,
         CH6  = 0x06,
         CH7  = 0x07,
         CH8  = 0x08, PB0 = CH8,
         CH9  = 0x09, PB1 = CH9,
         CH10 = 0x0A, PC0 = CH10,
         CH11 = 0x0B, PC1 = CH11,
         CH12 = 0x0C,
         CH13 = 0x0D,
         CH14 = 0x0E,
         CH15 = 0x0F, PC5 = CH15,
         CH16 = 0x10,
         CH17 = 0x11,
         CH18 = 0x12,
      };


      private:

         GPIO&           _gpio;
         const unsigned  _id;
         const uint16_t  _mask;

   };

} /* qb50 */


#endif /* _QB50_SYS_GPIO_PIN_H */

/*EoF*/
