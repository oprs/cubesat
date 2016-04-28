
#ifndef _QB50_ODB_WOD_STORE_H
#define _QB50_ODB_WOD_STORE_H

#include "Device.h"
#include "device/FlashCache.h"


namespace qb50 {


   class WodStore : public Device
   {

      public:

      /*
          +-------+-------+---------------+
          | type  |  len  |      seq      |
          +-------+-------+---------------+
          |             ticks             |
          +-------------------------------+
          |              prev             |
          +-------------------------------+
          |            VKI time           |
          +-------------------------------+
      */

         struct WEH /* WOD Entry Header */
         {
            uint8_t  type;  // application specific
            uint8_t  len;   // length in 32-bit words (incl. header)
            uint16_t seq;   // sequence number % (2^16)
            uint32_t ticks; // ticks since poweron
            uint32_t prev;  // address of previous entry
            uint32_t time;  // VKI time
         };

         enum : uint32_t { NIL = (uint32_t)-1 };

         enum EntryType {
            NONE  = 0,
            ADC   = 1,
            FIPEX = 2,
            GPS   = 3
         };

         WodStore( const char *name, FlashCache &mem );
         ~WodStore();

         WodStore& init    ( void );
         WodStore& enable  ( bool silent = false );
         WodStore& disable ( bool silent = false );

         WodStore& clear   ( void );
         WodStore& read    ( WEH *hdr, void *x );
         WodStore& write   ( EntryType type, const void *x, unsigned len );


      private:

         FlashCache&  _mem;
         const char  *_name;

         void _read  ( WEH *hdr, void *x );
         void _write ( EntryType type, const void *x, unsigned len );

   };

   extern qb50::WodStore WOD;

} /*qb50*/

#endif /*_QB50_ODB_WOD_STORE_H*/

/*EoF*/
