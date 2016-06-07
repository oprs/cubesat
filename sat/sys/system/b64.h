
#ifndef _QB50_SYSTEM_B64_H
#define _QB50_SYSTEM_B64_H

#include <cstdlib>
#include <cstdint>


namespace qb50 {

   extern size_t e64( char *dst, const uint8_t *src, size_t len );
   extern size_t d64( uint8_t *dst, const char *src, size_t len );

} /* qb50 */


#endif /*_QB50_SYSTEM_B64_H*/

/*EoF*/
