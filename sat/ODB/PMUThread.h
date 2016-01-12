
#ifndef _QB50_ODB_PMU_THREAD_H
#define _QB50_ODB_PMU_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class PMUThread : public Thread
   {

      public:

         PMUThread();
         ~PMUThread();

         void run( void );

      private:

         enum Mode { LOW = 0, HIGH = 1 };

         Mode _mode;

   };

} /* qb50 */


#endif /*_QB50_ODB_PMU_THREAD_H*/

/*EoF*/