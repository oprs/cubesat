
#ifndef _QB50_ODB_ADCS_THREAD_H
#define _QB50_ODB_ADCS_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class ADCSThread : public Thread
   {

      public:

         ADCSThread();
         ~ADCSThread();

         void run( void );

         void onSuspend ( void );
         void onResume  ( void );

      private:

         enum Mode { LOW = 0, HIGH = 1 };

         Mode _mode;

   };

} /* qb50 */


#endif /*_QB50_ODB_ADCS_THREAD_H*/

/*EoF*/
