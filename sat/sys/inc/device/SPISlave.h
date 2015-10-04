
#ifndef _QB50_SYS_SLAVE_SPI_SLAVE_H
#define _QB50_SYS_SLAVE_SPI_SLAVE_H

#include "device/SPI.h"
#include "device/GPIOPin.h"


namespace qb50 {

   class SPISlave
   {

      public:

         enum SelectMode {
            ActiveLow  = 0,
            ActiveHigh = 1
         };

         SPISlave( SPI& spi, GPIOPin& csPin, SelectMode csMode );
         virtual ~SPISlave();

         SPISlave& init( void );

      protected:

         SPI&       _spi;
         GPIOPin&   _csPin;
         SelectMode _csMode;

         void _select   ( void );
         void _deselect ( void );

   };

} /* qb50 */


#endif /*_QB50_SYS_SLAVE_SPI_SLAVE_H*/

/*EoF*/

