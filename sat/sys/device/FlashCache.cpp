
#include "FlashCache.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FlashCache::FlashCache( const char *name, FlashMemory& mem )
   : Device( name ), _mem( mem )
{
   _base = (uint32_t)-1;
   _ssiz = 0;
   _x    = 0;
}


FlashCache::~FlashCache()
{
   if( _x != 0 )
      delete[] x;
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
   unsigned sectors = len / _ssiz;

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
