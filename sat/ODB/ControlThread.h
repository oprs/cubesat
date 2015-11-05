
#ifndef _QB50_ODB_CONTROL_THREAD_H
#define _QB50_ODB_CONTROL_THREAD_H

#include "system/qb50.h"
#include "Config.h"


#define _QB50_NTHREADS 6


namespace qb50 {

   class ControlThread : public Thread
   {

      public:

         ControlThread();
         ~ControlThread();

         void run( void );


      private:

         Thread         *_tv[ _QB50_NTHREADS ];
         static uint32_t _mt[ _QB50_NMODES   ];

         uint32_t _ctb; // current thread bitmask

         void _switchModes( Config::mode_t target );

   };

} /* qb50 */


#endif /*_QB50_ODB_CONTROL_THREAD_H*/

/*EoF*/
