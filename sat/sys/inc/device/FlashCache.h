
#ifndef _QB50_SYS_DEVICE_FLASH_CACHE_H
#define _QB50_SYS_DEVICE_FLASH_CACHE_H

#include "device/FlashMemory.h"


namespace qb50 {

   class FlashCache : public FlashMemory
   {

      public:

         FlashCache( const char *name, FlashMemory& mem, const int nEntries );
         virtual ~FlashCache();

         virtual FlashCache& init        ( void );
         virtual FlashCache& enable      ( bool silent = false );
         virtual FlashCache& disable     ( bool silent = false );

         virtual FlashCache& pageRead    ( uint32_t addr, void *x       );
         virtual FlashCache& pageWrite   ( uint32_t addr, const void *x );
         virtual FlashCache& sectorErase ( uint32_t addr                );
         virtual FlashCache& sectorRead  ( uint32_t addr, void *x       );
         virtual FlashCache& sectorWrite ( uint32_t addr, const void *x );
         virtual FlashCache& blockErase  ( uint32_t addr                );

      protected:

         FlashMemory& _mem;
         const int    _nEntries;

   };

   extern qb50::FlashCache FCACHE;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_FLASH_CACHE_H*/

/*EoF*/
