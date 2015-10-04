
#ifndef _QB50_SYSTEM_DEVICE_H
#define _QB50_SYSTEM_DEVICE_H

#include <FreeRTOS.h>
#include <semphr.h>


namespace qb50 {

   class Device
   {

      public:

         Device( const char *name );
         virtual ~Device();

         inline const char *name ( void ) const
         { return _name; }

         virtual Device& init    ( void )                = 0;
         virtual Device& enable  ( bool silent = false ) = 0;
         virtual Device& disable ( bool silent = false ) = 0;

      protected:

         const char      *_name;     /**< device name               */
         unsigned         _refCount; /**< reference counter         */
         xSemaphoreHandle _devLock;  /**< global lock on the device */

         Device&  _lock   ( void );
         Device&  _unlock ( void );
         unsigned _incRef ( void );
         unsigned _decRef ( void );

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_DEVICE_H*/

/*EoF*/
