
#ifndef _QB50_SYSTEM_THREAD_H
#define _QB50_SYSTEM_THREAD_H

#include <cstddef>


namespace qb50 {

   class Thread
   {

      public:

         enum State {
            SUSPENDED = 0,
            RUNNING   = 1
         };

         Thread( const char *name, int prio, State state = RUNNING, unsigned stackDepth = 256 );
         ~Thread();

                 void suspend   ( void );
                 void resume    ( void );

         virtual void run       ( void ) = 0;

         virtual void onInit    ( void );
         virtual void onExit    ( void );
         virtual void onSuspend ( void );
         virtual void onResume  ( void );

#if 0
         static  void *operator new    ( size_t size );
         static  void  operator delete ( void   *p   );
#endif

         const char *name;
         void       *handle;
         unsigned    priority;
         unsigned    stackDepth;

      protected:

         bool _state;

         void     _wait     ( void );
         unsigned _stackHWM ( void );

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_THREAD_H*/

/*EoF*/
