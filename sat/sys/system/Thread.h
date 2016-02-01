
#ifndef _QB50_SYSTEM_THREAD_H
#define _QB50_SYSTEM_THREAD_H


namespace qb50 {

   class Thread
   {

      public:

         Thread( const char *name, int prio, bool suspended = false, unsigned stackDepth = 256 );
         ~Thread();

                 void suspend   ( void );
                 void resume    ( void );

         virtual void run       ( void ) = 0;

         virtual void onInit    ( void );
         virtual void onExit    ( void );
         virtual void onSuspend ( void );
         virtual void onResume  ( void );

         const char *name;
         void       *handle;
         unsigned    priority;
         unsigned    stackDepth;

      protected:

         bool _suspended;

         void _wait( void );

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_THREAD_H*/

/*EoF*/
