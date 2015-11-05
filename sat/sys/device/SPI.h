
#ifndef _QB50_SYS_DEVICE_SPI_H
#define _QB50_SYS_DEVICE_SPI_H

#include "Device.h"


namespace qb50 {

   class SPI : public Device
   {

      public:

         #include "SPI_Stream.h"

         SPI( const char* name )
            : Device( name )
         { ; }

         virtual ~SPI()
         { ; }

         virtual SPI& init     ( void                ) = 0;
         virtual SPI& enable   ( bool silent = false ) = 0;
         virtual SPI& disable  ( bool silent = false ) = 0;

         /* synchronous transfer */

         virtual SPI& xfer     ( const void *src, void *dst, size_t len ) = 0;
         virtual SPI& pollXfer ( const void *src, void *dst, size_t len ) = 0;
         virtual SPI& write    ( const void *src,            size_t len ) = 0;
         virtual SPI& read     (                  void *dst, size_t len ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_H*/

/*EoF*/
