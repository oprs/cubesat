
#ifndef _QB50_FIPEX_THREAD_H
#define _QB50_FIPEX_THREAD_H

#include "system/qb50.h"
#include "Fipex.h"


namespace qb50 {

   class FipexThread : public Thread
   {

      public:

         FipexThread();
         ~FipexThread();

         enum State {
            START_WAIT  = 0,
            REPEAT_WAIT = 1,
            RUNNING     = 2
         };

         void run       ( void );
         void test      ( void );
         void cmd       ( const uint8_t *x, size_t len );

         void dump      ( uint8_t *x, size_t len );
         void dump_sdp  ( uint8_t *x, size_t len );

         void onSuspend ( void );
         void onResume  ( void );

      private:

         void _runScript( const uint8_t *x, bool debug = false );

         State    _st;  // current state
         uint8_t *_rx;  // receive buffer

   };

} /* qb50 */


#endif /*_QB50_FIPEX_THREAD_H*/

/*EoF*/

