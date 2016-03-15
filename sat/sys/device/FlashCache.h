
#ifndef _QB50_SYS_DEVICE_FLASH_CACHE_H
#define _QB50_SYS_DEVICE_FLASH_CACHE_H

#include "Device.h"
#include "FlashMemory.h"


namespace qb50 {

   class FlashCache : public Device
   {

      public:

         FlashCache( const char *name, FlashMemory& mem );
         ~FlashCache();

         FlashCache& init    ( void );
         FlashCache& enable  ( bool silent = false );
         FlashCache& disable ( bool silent = false );

         FlashCache& read    ( uint32_t addr,       void *x, size_t len );
         FlashCache& write   ( uint32_t addr, const void *x, size_t len, bool sync = false );


      protected:

         FlashMemory& _mem;   // slave FlashMemory

         uint32_t     _nhit;  // number of cache hits
         uint32_t     _nmis;  // number of cache misses
         bool         _drty;  // cache is dirty

         uint32_t     _base;  // address (slave) of the sector currently in cache
         uint32_t     _ssiz;  // sector size
         uint8_t     *_x;     // buffer

         void _load  ( uint32_t addr );
         void _flush ( void );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_FLASH_CACHE_H*/

/*EoF*/
