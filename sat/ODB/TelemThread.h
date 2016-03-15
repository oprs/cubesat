
#ifndef _QB50_TELEM_THREAD_H
#define _QB50_TELEM_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class TelemThread : public Thread
   {

      public:

         TelemThread();
         ~TelemThread();

         void run       ( void );
         void onSuspend ( void );
         void onResume  ( void );

      private:

#if 0
         class AX25Handler : public GPIOHandler
         {

            public:

               AX25Handler( FIFO<bool>& fifo );
               ~AX25Handler();

               void handle( EXTI::EXTIn );

            private:

               FIFO<bool>& _fifo;
               NRZI        _nrzi;
               Scrambler   _sblr;

         };
#endif

         uint8_t *_x;

   };

} /* qb50 */


#endif /*_QB50_TELEM_THREAD_H*/

/*EoF*/
