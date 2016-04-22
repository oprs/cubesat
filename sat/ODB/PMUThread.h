
#ifndef _QB50_ODB_PMU_THREAD_H
#define _QB50_ODB_PMU_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class PMUThread : public Thread
   {

      public:

         PMUThread();
         ~PMUThread();

         void run       ( void );
         void onSuspend ( void );
         void onResume  ( void );

         enum {
            SAMPLE_V4,
            SAMPLE_I4,
            SAMPLE_T4,
            SAMPLE_V1,
            SAMPLE_T1,
            SAMPLE_I1,
            SAMPLE_T_Bat,
            SAMPLE_V_Bat,

            SAMPLE_V2,
            SAMPLE_T2,
            SAMPLE_I2,
            SAMPLE_V3,
            SAMPLE_T3,
            SAMPLE_I3,
            SAMPLE_I_Surt,
            SAMPLE_X0,

            SAMPLE_I_ADCS,
            SAMPLE_T_ARM,
            SAMPLE_I_RX,
            SAMPLE_RSSI,
            SAMPLE_I_TX,
            SAMPLE_P_TX,
            SAMPLE_P_PA,
            SAMPLE_T_PA,

            SAMPLE_X1,
            SAMPLE_I_GPS,
            SAMPLE_X2,
            SAMPLE_I_3V3_FIPEX,
            SAMPLE_V_3V3_FIPEX,
            SAMPLE_I_5V_FIPEX,
            SAMPLE_V_5V_FIPEX,
            SAMPLE_SU_TH_G0,
         };

      private:

         enum Mode { LOW = 0, HIGH = 1 };

         MAX111x::Sample *_raw;
         uint8_t         *_raw8;

         unsigned  _cur;
         bool      _rdy;

         Mode      _modeBat;
         Mode      _modePA;

   };

} /* qb50 */


#endif /*_QB50_ODB_PMU_THREAD_H*/

/*EoF*/
