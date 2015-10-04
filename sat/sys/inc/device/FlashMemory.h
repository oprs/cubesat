
#ifndef _QB50_SYS_DEVICE_FLASH_MEMORY_H
#define _QB50_SYS_DEVICE_FLASH_MEMORY_H

#include "Device.h"
#include <cstdint>


namespace qb50 {

   class FlashMemory : public Device
   {

      public:

         FlashMemory( const char *name );
         virtual ~FlashMemory();

         struct Geometry {
            uint16_t bpc;  /* blocks per chip */
            uint16_t ppb;  /* pages per block */
            uint16_t bpp;  /* bytes per page  */

            Geometry() : bpc( 0 ), ppb( 0 ), bpp( 0 )
            { ; }

            virtual ~Geometry()
            { ; }
         };

         virtual FlashMemory& init        ( void ) = 0;
         virtual FlashMemory& enable      ( bool silent = false ) = 0;
         virtual FlashMemory& disable     ( bool silent = false ) = 0;

         virtual FlashMemory& pageRead    ( uint32_t addr, void *x       ) = 0;
         virtual FlashMemory& pageWrite   ( uint32_t addr, const void *x ) = 0;
         virtual FlashMemory& sectorErase ( uint32_t addr                ) = 0;
         virtual FlashMemory& blockErase  ( uint32_t addr                ) = 0;

         FlashMemory& geometry ( Geometry *geo );
         uint32_t size( void );

      protected:

         FlashMemory::Geometry _geo;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_FLASH_MEMORY_H*/

/*EoF*/
