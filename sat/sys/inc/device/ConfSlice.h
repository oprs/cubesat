
#ifndef _QB50_SYS_DEVICE_CONF_SLICE_H
#define _QB50_SYS_DEVICE_CONF_SLICE_H

#include "device/Slice.h"


namespace qb50 {

   class ConfSlice : public Slice
   {

      public:

         ConfSlice( const char *name, FlashMemory& mem, const unsigned off, const unsigned len );
         virtual ~ConfSlice();

         ConfSlice& init    ( void );
         ConfSlice& enable  ( bool silent = false );
         ConfSlice& disable ( bool silent = false );

         uint8_t *addr( void )
         { return _x; }

         virtual ConfSlice& sync( void );

      protected:

         uint8_t *_x;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_CONF_SLICE_H*/

/*EoF*/
