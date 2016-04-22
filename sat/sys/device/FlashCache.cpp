
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
   _drty = false;
   _base = (uint32_t)-1;
   _ssiz = 0;
   _x    = 0;
}


FlashCache::~FlashCache()
{
   if( _x != 0 )
      delete[] _x;
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

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
   uint32_t off = addr & ( _ssiz - 1 );
   uint32_t nb  = _ssiz - off;

   if( nb > len ) nb = len;

if( len > 1024 ) {
   kprintf( "FlashCache::read( %u, %p, %u )\r\n", addr, x, len );
   for( ;; );
}

   (void)lock();

   /* read the first sector */

   _load( addr );
   (void)memcpy( dst, _x + off, nb );

   len  -= nb;
   dst  += nb;
   addr += _ssiz;
   nb    = ( len > _ssiz ) ? _ssiz : len;

   /* read subsequent sectors */

   while( nb > 0 ) {

      _load( addr );
      (void)memcpy( dst, _x, nb );

      len  -= nb;
      dst  += nb;
      addr += _ssiz;
      nb    = ( len > _ssiz ) ? _ssiz : len;

   }

   (void)unlock();

 //kprintf( "%s: hits: %u, misses: %u\r\n", _name, _nhit, _nmis );

   return *this;
}


FlashCache& FlashCache::write( uint32_t addr, const void *x, size_t len, bool sync )
{
   if( len == 0 ) {
      kprintf( "%s: FlashCache::write(): nothing to write\r\n", _name );
      if( sync ) {
         /* let the user a chance to flush the cache */
         (void)lock();
         _flush();
         (void)unlock();
      }
      return *this;
   }

   const uint8_t* src = (const uint8_t*)x;
 //uint32_t       cur = addr & ~( _ssiz - 1 );
   uint32_t       off = addr &  ( _ssiz - 1 );
   uint32_t       nb  = _ssiz - off;

   if( nb > len ) nb = len;

 //kprintf( "FlashCache::write( %u, %p, %u )\r\n", addr, x, len );

   /* lock the device */

   (void)lock();

   /* write the first sector */

   _load( addr );
   (void)memcpy( _x + off, src, nb );
   _drty = true;

   len  -= nb;
   src  += nb;
   addr += _ssiz;
   nb    = ( len > _ssiz ) ? _ssiz : len;

   /* write subsequent sectors */

   while( nb > 0 ) {

      _load( addr );
      (void)memcpy( _x, src, nb );
      _drty = true;

      len  -= nb;
      src  += nb;
      addr += _ssiz;
      nb    = ( len > _ssiz ) ? _ssiz : len;

   }

   /**/

   if( sync ) {
      /* synchronous operation requested: force a sector flush */
      _flush();
   }

   (void)unlock();

 //kprintf( "%s: hits: %u, misses: %u\r\n", _name, _nhit, _nmis );

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void FlashCache::_load( uint32_t addr )
{
   addr &= ~( _ssiz - 1 );

 //kprintf( "FlashCache::_load( %u )\r\n", addr );

   if( addr == _base ) {
      /* sector is already in cache: this is a hit */
      ++_nhit;
      return;
   }

   /* sector not in cache */

   ++_nmis;

   if( _drty ) {
      /* flush the sector if cache is dirty */
      _flush();
      /* cache is now clean */
   }

   /* load the requested sector */

   _mem.sectorRead( addr, _x );
   _base = addr;
}


void FlashCache::_flush( void )
{
 //kprintf( "FlashCache::_flush(), _base: %u\r\n", _base );
   _mem.sectorErase( _base );
   _mem.sectorWrite( _base, _x );
   _drty = false;
}


/*EoF*/
