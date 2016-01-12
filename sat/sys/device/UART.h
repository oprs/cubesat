
#ifndef _QB50_SYS_DEVICE_UART_H
#define _QB50_SYS_DEVICE_UART_H

#include "Device.h"


namespace qb50 {

   class UART : public Device
   {

      public:

         UART( const char *name ) : Device( name )
         { ; }

         virtual ~UART()
         { ; }

         virtual UART&  init     ( void )                      = 0;
         virtual UART&  enable   ( bool silent )               = 0;
         virtual UART&  disable  ( bool silent )               = 0;
         virtual size_t read     (       void *x, size_t len ) = 0;
         virtual size_t readLine (       void *x, size_t len ) = 0;
         virtual size_t write    ( const void *x, size_t len ) = 0;
         virtual UART&  baudRate ( unsigned rate )             = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_UART_H*/

/*EoF*/