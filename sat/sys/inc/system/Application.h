
#ifndef _QB50_SYSTEM_APPLICATION_H
#define _QB50_SYSTEM_APPLICATION_H

#include "Thread.h"


namespace qb50 {

   extern Thread *createThread( const char *name, ThreadWorker worker );
   extern void    registerThread( Thread *t );
   extern void    run( void );
   extern void    delay( unsigned ms );
   extern void    hexdump( const void *addr, unsigned len );
   extern void    print( const char *x, unsigned len );

} /* qb50 */

#ifdef DEBUG
 #define QB50DBG( msg ) print( msg, sizeof( msg ))
#else
 #define QB50DBG( msg )
#endif


#endif /*_QB50_SYSTEM_APPLICATION_H*/

/*EoF*/