
#include "WodStore.h"
#include "system/Logger.h"
#include "Config.h"
#include "devices.h"

#include <cstring>

using namespace qb50;


WodStore qb50::WOD( "WOD", VFLASH ); // global WOD database


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

WodStore::WodStore( const char *name, FlashMemory& mem )
   : Device( name ), _mem( mem )
{ ; }


WodStore::~WodStore()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

WodStore& WodStore::init( void )
{
   _rCache.addr = (uint32_t)-1; /* see the NOTE in WodStore::read() */
   _rCache.size = _mem.sectorSize();
   _rCache.x    = new uint8_t[ _rCache.size ];

   _wCache.addr =  0;
   _wCache.size = _mem.sectorSize();
   _wCache.x    = new uint8_t[ _wCache.size ];

   return *this;
}


WodStore& WodStore::enable( bool silent )
{
   lock();
   _mem.enable( silent );
   unlock();

kprintf( "wHead: 0x%08x\r\n", CONF.wHead() );
kprintf( "wTail: 0x%08x\r\n", CONF.wTail() );

   return *this;
}


WodStore& WodStore::disable( bool silent )
{
   lock();
   _mem.disable( silent );
   unlock();

   return *this;
}


WodStore& WodStore::clear( void )
{
   lock();

   (void)CONF.wHead( 0 );
   (void)CONF.wTail( 0 );

   unlock();

   return *this;
}


#define INCACHE( S, X ) \
   (( (X) >= (S).addr ) && ( (X) < ( (S).addr + (S).size )))


WodStore::Entry* WodStore::read( uint32_t addr )
{
   lock();

   uint32_t base = addr & ~( _mem.sectorSize() - 1 );
   uint32_t off  = addr &  ( _mem.sectorSize() - 1 );

   /*
    * NOTE: _rCache.addr is set to -1 upon initialization in order
    * ----  to make sure that a cache miss occurs on the first read,
    *       no matter which address is requested.
    *       ('base' is a multiple of a sector size, it can't be -1).
    */

   if( base != _rCache.addr ) {

      /*
       * requested sector not in the read cache, see if it's currently being
       * held in the write cache, otherwise just read it from the flash.
       */

      if( base == _wCache.addr ) {
         /* get a copy from the write cache */
         (void)memcpy( _rCache.x, _wCache.x, _rCache.size );
      } else {
         /* or, load from the flash */
         (void)_mem.sectorRead( base, _rCache.x );
      }
   }

   unlock();

   return (WodStore::Entry*)( _rCache.x + off );
}


WodStore& WodStore::write( WodStore::Entry *e )
{
   lock();

   uint32_t wHead = CONF.wHead();
   uint32_t wTail = CONF.wTail();
   uint32_t wNext = wTail + size( (WodStore::Entry*)wTail );

/*
LOG << "WodStore::Write( 0x" << std::hex << (unsigned)e << " ), size: " << std::dec << size( e );
LOG << " - type: " << e->_type;
LOG << " - wHead: 0x" << std::hex << wHead;
LOG << " - wTail: 0x" << std::hex << wTail;
LOG << " - _wCache.addr: 0x" << std::hex << _wCache.addr;
LOG << " - wNext: 0x" << std::hex << wNext;
*/

   if( !INCACHE( _wCache, wNext + size( e ))) {

      /*
       * New entry doesn't fit in the cache ?
       * -> flush the current sector and go for the next one
       */

/*
LOG << " - doesn't fit in cache, reading next sector";
*/

      _mem.sectorErase( _wCache.addr );
      _mem.sectorWrite( _wCache.addr, _wCache.x );

      /* get the next sector */

      wNext = _nsaddr( _wCache.addr );

/*
LOG << " - wNext: 0x" << std::hex << wNext;
*/

      if( wNext == wHead ) {

         /*
          * Already some data there ?
          * -> move wHead one sector further so that it points to the next
          *    valid entry (entries are aligned on sector boundaries).
          *    The old data will be overwritten (need to make some room).
          */

/*
LOG << " - already some data there, moving wHead one sector further";
*/

         wHead = CONF.wHead( _nsaddr( wHead ));
/*
LOG << " - wHead: 0x" << std::hex << wHead;
*/
      }
   }

   /* we can safely write size(e) bytes in the cache at this point */

   e->_prev = wTail;

   uint32_t off = wNext & ( _mem.sectorSize() - 1 );
   (void)memcpy( _wCache.x + off, e, size( e ));

/*
LOG << " - off: 0x" << std::hex << off << std::dec;
*/

   /* point wTail to the new entry */

   (void)CONF.wTail( wNext );

   unlock();

   return *this;
}


uint32_t WodStore::size( WodStore::Entry *e )
{
   uint32_t rv;

   switch( e->_type ) {
      case NIL:   rv = sizeof( WodStore::Entry      ); break;
      case ADC:   rv = sizeof( WodStore::ADCEntry   ); break;
      case FIPEX: rv = sizeof( WodStore::FipexEntry ); break;
   }

   return rv;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

uint32_t WodStore::_nsaddr( uint32_t addr )
{
   addr &= ~( _mem.sectorSize() - 1 );
   addr +=    _mem.sectorSize();

   return
      ( addr >= _mem.chipSize() ) ? 0 : addr;
}

/*EoF*/
