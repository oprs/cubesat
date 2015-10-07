
#ifndef _QB50_SYS_DEVICE_SLICE_H
#define _QB50_SYS_DEVICE_SLICE_H

#include "Device.h"
#include "device/FlashMemory.h"


namespace qb50 {

   class Slice : public Device
   {

      public:

         Slice( const char *name, FlashMemory& mem, const unsigned off, const unsigned len );
         virtual ~Slice();

         Slice& init    ( void );
         Slice& enable  ( bool silent = false );
         Slice& disable ( bool silent = false );

         virtual Slice& sync( void ) = 0;

      protected:

         FlashMemory&   _mem;
         const unsigned _off;
         const unsigned _len;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SLICE_H*/

/*EoF*/
