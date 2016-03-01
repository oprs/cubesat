
#include "FlashCache.h"
#include "system/Logger.h"

#include <cstring>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FlashCache::FlashCache( const char *name, FlashMemory& mem )
   : Device( name ), _mem( mem )
{
   _nhit = 0;
   _nmis = 0;
   _base = (uint32_t)-1;
   _ssiz = 0;
   _x    = 0;
}


FlashCache::~FlashCache()
{
   if( _x != 0 )
      delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

FlashCache& FlashCache::init( void )
{
   (void)_mem.init();

   _ssiz = _mem.sectorSize();
   _x = new uint8_t[ _ssiz ];

   kprintf( "%s: Flash cache\r\n", _name );

   return *this;
}


FlashCache& FlashCache::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   (void)_mem.enable( silent );

   if( !silent )
      kprintf( "%s: enabled\r\n", _name );

   return *this;
}


FlashCache& FlashCache::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   (void)_mem.disable( silent );

   if( !silent )
      kprintf( "%s: disabled\r\n", _name );

   return *this;
}


FlashCache& FlashCache::read( uint32_t addr, void *x, size_t len )
{
   if( len == 0 ) {
      kprintf( "%s: FlashCache::read(): 0 bytes requested\r\n", _name );
      return *this;
   }

   uint8_t* dst = (uint8_t*)x;
   uint32_t cur = addr & ~( _ssiz - 1 );
   uint32_t off = addr &  ( _ssiz - 1 );
   uint32_t nb  = _ssiz - off;

   if( nb > len ) nb = len;

kprintf( "FlashCache::read( %u, %p, %u )\r\n", addr, x, len );
kprintf( "- base: %u, off: %u, nb: %u\r\n", cur, off, nb );

   /* lock the device */

   lock();

   /* read the first page */

   if( cur == _base ) {
      ++_nhit;
   } else {
      ++_nmis;
      _mem.pageRead( cur, _x );
      _base = cur;
   }

   (void)memcpy( dst, _x + off, nb );

   len -= nb;
   dst += nb;

   /* read subsequent pages */

   while( len > 0 ) {

      ++_nmis;

      _base += _ssiz;
      _mem.pageRead( _base, _x );

      nb = len & ( _ssiz - 1 );
kprintf( "- base: %u, nb: %u, len: %u\r\n", _base, nb, len );
      (void)memcpy( dst, _x, nb );

      len -= nb;
      dst += nb;
   }

   /* unlock the device and return */

   unlock();

kprintf( "%s: hits: %u, misses: %u\r\n", _name, _nhit, _nmis );

   return *this;
}


FlashCache& FlashCache::write( uint32_t addr, const void *x, size_t len )
{
   return *this;
}


FlashCache& FlashCache::flush( void )
{
   return *this;
}


/*EoF*/
