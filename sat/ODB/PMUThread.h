
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

   };

} /* qb50 */


#endif /*_QB50_ODB_PMU_THREAD_H*/

/*EoF*/
