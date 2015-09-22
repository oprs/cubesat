
#ifndef _QB50_SYSTEM_APPLICATION_H
#define _QB50_SYSTEM_APPLICATION_H

#include "SimpleThread.h"


namespace qb50 {

	extern Thread  *createThread( const char *name, ThreadWorker worker, int prio = 1 );
	extern void     registerThread( Thread *t );
	extern void     run( void );
	extern void     delay( unsigned ms );
	extern unsigned ticks( void );
	extern void     hexdump( const void *addr, unsigned len );

} /* qb50 */


#endif /*_QB50_SYSTEM_APPLICATION_H*/

/*EoF*/
