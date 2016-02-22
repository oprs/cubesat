
#ifndef _QB50_FIPEX_THREAD_H
#define _QB50_FIPEX_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class FipexThread : public Thread
   {

      public:

         FipexThread();
         ~FipexThread();

         void run  ( void );
         void test ( void );
         void cmd  ( uint8_t *x, size_t len );

         void dump      ( uint8_t *x, size_t len );
         void dump_sdp  ( uint8_t *x, size_t len );

         void onSuspend ( void );
         void onResume  ( void );

   };

} /* qb50 */


#endif /*_QB50_FIPEX_THREAD_H*/

/*EoF*/

