
#ifndef _QB50_ODB_PARAMETERS_H
#define _QB50_ODB_PARAMETERS_H

#include <cstdint>


#define _QB50_NPARAMS   64
#define _QB50_PVAL_MASK 0xffff


namespace qb50 {

   class Parameters
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

         static const pid_t bounds[ _QB50_NPARAMS ];
         static const definition defs[ _QB50_NPARAMS ];

         Parameters();
         virtual ~Parameters();

         pid_t  check ( long p, long v );

         pval_t set   ( pid_t pid, pval_t pval );
         pval_t get   ( pid_t pid );


      private:

         pval_t pv[ _QB50_NPARAMS ];

   };

} /* qb50 */


#endif /*_QB50_ODB_PARAMETERS_H*/

/*EoF*/
