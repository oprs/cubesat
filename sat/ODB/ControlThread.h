
#ifndef _QB50_ODB_CONTROL_THREAD_H
#define _QB50_ODB_CONTROL_THREAD_H

#include "system/qb50.h"


#define _QB50_NMODES  13
#define _QB50_NTHREADS 6


namespace qb50 {

   class ControlThread : public Thread
   {

      public:

         ControlThread();
         ~ControlThread();

         void run( void );


      private:

         enum Mode {
            INIT      = 0,
            CW        = 1,
            WODEX     = 2,
            FiPEX     = 3,
            PowerSave = 4,
            FM        = 5,
            StandBy   = 6
         };

         Thread  *_tv[ _QB50_NTHREADS ];

         static uint32_t _mt[ _QB50_NMODES ];

   };

} /* qb50 */


#endif /*_QB50_ODB_CONTROL_THREAD_H*/

/*EoF*/
