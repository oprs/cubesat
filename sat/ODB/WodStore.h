
#ifndef _QB50_ODB_WOD_STORE_H
#define _QB50_ODB_WOD_STORE_H

#include "device/FlashMemory.h"


namespace qb50 {


   class WodStore : public Device
   {

      public:

         enum EntryType {
            NIL   = 0,
            PLAIN = 1,
            FIPEX = 2
         };

         struct Entry
         {
            uint32_t _type:4;
            uint32_t _prev:28;
            uint32_t _time;

            Entry( EntryType type, uint32_t prev, uint32_t time )
            : _type( type ), _prev( prev ), _time( time )
            { ; }

            ~Entry()
            { ; }
         };

         struct PlainEntry : public Entry
         {
            uint16_t _flags;
            uint8_t  _adc[32];

            PlainEntry( uint32_t prev, uint32_t time ) : Entry( PLAIN, prev, time )
            { ; }

            ~PlainEntry()
            { ; }
         };

         struct FipexEntry : public Entry
         {
            FipexEntry( uint32_t prev, uint32_t time ) : Entry( FIPEX, prev, time )
            { ; }

            ~FipexEntry()
            { ; }
         };

         WodStore( const char *name, FlashMemory& mem );
         ~WodStore();

         WodStore& init    ( void );
         WodStore& enable  ( bool silent = false );
         WodStore& disable ( bool silent = false );

         WodStore& clear   ( void );
         WodStore& write   ( Entry *e );
         Entry    *last    ( void );
         uint32_t  size    ( Entry *e );

      protected:

         struct Sector {
            // XXX dirty: isDirty() / setDirty()
            uint8_t *x;     // cached data
            uint32_t addr;  // address in flash
            uint32_t size;  // sector size
         };

         FlashMemory& _mem;

         Sector _sec; /* current sector */

   };

   extern qb50::WodStore WDB;

} /*qb50*/

#endif /*_QB50_ODB_WOD_STORE_H*/

/*EoF*/