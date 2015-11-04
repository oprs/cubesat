
#ifndef _QB50_ODB_CONFIG_H
#define _QB50_ODB_CONFIG_H

#include "TLE.h"
#include <cstdint>


#define _QB50_NPARAMS   64
#define _QB50_PVAL_MASK 0xffff


namespace qb50 {

   class Config
   {

      public:

         enum pid_t {
            PARAM_NONE              = 0,
            PARAM_CW_CYCLE_TX       = 1,
            PARAM_WODEX_CYCLE_TX    = 2,
            PARAM_FIPEX_SCRIPT_N    = 3,
          //UNUSED                  = 4,
            PARAM_ADCS_CYCLE_MEAS   = 5,
            PARAM_GPS_CYCLE_ON      = 6,
            PARAM_BAT_V_LOW         = 7,
          //UNUSED                  = 8,
            PARAM_FM_WODEX_CYCLE_TX = 9,
            PARAM_ADCS_CYCLE_CTRL   = 10,
            PARAM_FM_CYCLE_ON       = 11,
            PARAM_BAT_V_HIGH        = 12,
          //UNUSED                  = 13,
            PARAM_PA_TEMP_HIGH      = 14,
            PARAM_PA_TEMP_LOW       = 15
         };

         typedef int16_t pval_t;

         struct definition {
            const pid_t  pid;  /* parameter ID  */
            const pval_t min;  /* min value     */
            const pval_t max;  /* max value     */
            const pval_t def;  /* default value */
         };

         static const definition defs[ _QB50_NPARAMS ];

         Config();
         virtual ~Config();

         void     clear    ( void );
         uint16_t reset    ( void );
         pid_t    chkParam ( long p, long v );
         pval_t   getParam ( pid_t pid );
         pval_t   setParam ( pid_t pid, pval_t pval );


      private:

         struct _Store
         {
            pval_t   pv[ _QB50_NPARAMS ];  /* parameters                        */
            uint16_t nReset;               /* reset counter                     */
            TLE      tle;                  /* latest TLE known to the satellite */
          //MTT      mtt;                  /* mode-thread table                 */
          //STT      stt;                  /* state-transition table            */
            uint32_t wHead;                /* head of the WOD chain             */
            uint32_t wTail;                /* tail of the WOD chain             */
         };

   };

   extern qb50::Config CONF;

} /* qb50 */


#endif /*_QB50_ODB_CONFIG_H*/

/*EoF*/
