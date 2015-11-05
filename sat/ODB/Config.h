
#ifndef _QB50_ODB_CONFIG_H
#define _QB50_ODB_CONFIG_H

#include "TLE.h"
#include <cstdint>

#include <FreeRTOS.h>
#include <semphr.h>


#define _QB50_NMODES     8
#define _QB50_NPARAMS   64
#define _QB50_PVAL_MASK 0xffff


namespace qb50 {

   class Config
   {

      public:

         //  - - - - - - - - - -  //
         //  P A R A M E T E R S  //
         //  - - - - - - - - - -  //

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

         pid_t    chkParam ( long p, long v );
         pval_t   getParam ( pid_t pid );
         pval_t   setParam ( pid_t pid, pval_t pval );

         //  - - - - -  //
         //  M O D E S  //
         //  - - - - -  //

         enum Mode {
            INIT  = 0,
            CW    = 1,
            STDBY = 2,
            WODEX = 3,
            TELEM = 4,
            FIPEX = 5,
            FM    = 6,
            POWER = 7
         };

         static const char *modes[ _QB50_NMODES ];

         typedef uint32_t mode_t;

         mode_t mode ( void );
         mode_t mode ( mode_t mode );

         //  - - - - -  //
         //  W O D E X  //
         //  - - - - -  //

         uint32_t wHead    ( void );
         uint32_t wHead    ( uint32_t addr );

         uint32_t wTail    ( void );
         uint32_t wTail    ( uint32_t addr );

         //  - - - - - - -  //
         //  M E T H O D S  //
         //  - - - - - - -  //

         Config();
         virtual ~Config();

         Config&  lock     ( void );
         Config&  unlock   ( void );

         void     clear    ( void );
         uint16_t reset    ( void );


      private:

         xSemaphoreHandle _lock;

         struct _Store
         {
            pval_t   pv[ _QB50_NPARAMS ];  /* parameters                        */
            uint16_t nReset;               /* reset counter                     */
            mode_t   mode;                 /* current mode                      */
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
