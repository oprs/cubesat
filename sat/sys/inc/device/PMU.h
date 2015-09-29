
#ifndef _QB50_SYS_DEVICE_PMU_H
#define _QB50_SYS_DEVICE_PMU_H

#include "Device.h"
#include <cstdint>


namespace qb50 {

   class PMU : public Device
   {

      public:

         enum PMUSample {
            ADC1CH0 =  0,          V4 = 0,  /* solar panel #4 - voltage     */
            ADC1CH1 =  1,          I4 = 1,  /* solar panel #4 - current     */
            ADC1CH2 =  2,          T4 = 2,  /* solar panel #4 - temperature */
            ADC1CH3 =  3,          V1 = 3,  /* solar panel #1 - voltage     */
            ADC1CH4 =  4,          T1 = 4,  /* solar panel #1 - temperature */
            ADC1CH5 =  5,          I1 = 5,  /* solar panel #1 - current     */
            ADC1CH6 =  6,       T_BAT = 6,  /* barrery temperature          */
            ADC1CH7 =  7,       V_BAT = 7,  /* battery voltage              */

            ADC2CH0 =  8,          V2 = 8,  /* solar panel #2 - voltage     */
            ADC2CH1 =  9,          T2 = 9,  /* solar panel #2 - temperature */
            ADC2CH2 = 10,          I2 = 10, /* solar panel #2 - current     */
            ADC2CH3 = 11,          V3 = 11, /* solar panel #3 - voltage     */
            ADC2CH4 = 12,          T3 = 12, /* solar panel #3 - temperature */
            ADC2CH5 = 13,          I3 = 13, /* solar panel #3 - current     */
            ADC2CH6 = 14,      I_SURT = 14, /* overcurrent                  */
            ADC2CH7 = 15,                   /* --------- NOT USED --------- */

            ADC3CH0 = 16,      I_ADCS = 16, /* ADCS - current               */
            ADC3CH1 = 17,   T_ARM_ODB = 17,
            ADC3CH2 = 18,        I_RX = 18, /* RX - current                 */
            ADC3CH3 = 19,        RSSI = 19,
            ADC3CH4 = 20,        I_TX = 20, /* TX - current                 */
            ADC3CH5 = 21,        P_TX = 21,
            ADC3CH6 = 22,        P_PA = 22,
            ADC3CH7 = 23,        T_PA = 23, /* PA - temperature             */

            ADC4CH0 = 24,   /* I_ADCS */    /* --------- NOT USED --------- */
            ADC4CH1 = 25,       I_GPS = 25, /* GPS - current                */
            ADC4CH2 = 26,                   /* --------- NOT USED --------- */
            ADC4CH3 = 27, I_3V3_FIPEX = 27, /* 3.3V FIPEX rail - current    */
            ADC4CH4 = 28, V_3V3_FIPEX = 28, /* 3.3V FIPEX rail - voltage    */
            ADC4CH5 = 29,  I_5V_FIPEX = 29, /*   5V FIPEX rail - current    */
            ADC4CH6 = 30,  V_5V_FIPEX = 30, /*   5V FIPEX rail - voltage    */
            ADC4CH7 = 31,    SU_TH_G0 = 31
         };

         PMU( const char *name );
         virtual ~PMU();

         PMU& init    ( void );
         PMU& enable  ( bool silent = false );
         PMU& disable ( bool silent = false );

         PMU& update  ( int ns );

         unsigned get ( PMUSample n ) const
         { return _samples[ n ]; }

      protected:

         unsigned _samples[ 32 ];

   };

   extern qb50::PMU PMU0;

} /*qb50*/

#endif /*_QB50_SYS_DEVICE_PMU_H*/

/*EoF*/
