
#ifndef _QB50_SYS_DEVICE_FLASH_ARRAY_H
#define _QB50_SYS_DEVICE_FLASH_ARRAY_H

#include "device/FlashMemory.h"


namespace qb50 {

   class FlashArray : public FlashMemory
   {

      public:

         FlashArray();

         FlashArray( const char *name, int nSlaves, FlashMemory *slaves[] );
         ~FlashArray();

         /* FlashMemory interface */

         FlashArray& init        ( void );
         FlashArray& enable      ( bool silent = false );
         FlashArray& disable     ( bool silent = false );

         FlashArray& pageRead    ( uint32_t addr, void *x );
         FlashArray& pageWrite   ( uint32_t addr, const void *x );
         FlashArray& sectorErase ( uint32_t addr );
         FlashArray& blockErase  ( uint32_t addr );

      protected:

         int           _nSlaves;
         FlashMemory **_slaves;

   };

   extern qb50::FlashArray VFLASH;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_FLASH_ARRAY_H*/

/*EoF*/
