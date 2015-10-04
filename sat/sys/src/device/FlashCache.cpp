
#include "device/FlashCache.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FlashCache::FlashCache( const char *name, FlashMemory& mem, const int nEntries )
   : FlashMemory( name ), _mem( mem ), _nEntries( nEntries )
{ ; }


FlashCache::~FlashCache()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

FlashCache& FlashCache::init( void )
{
   (void)_mem.init();

   LOG << _name << ": Virtual flash memory cache for " << _mem.name()
                << " (" << ( _mem.chipSize() >> 17 ) << "Mbit)";

   return *this;
}


FlashCache& FlashCache::enable( bool silent )
{
   (void)_mem.enable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


FlashCache& FlashCache::disable( bool silent )
{
   (void)_mem.disable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


FlashCache& FlashCache::pageRead( uint32_t addr, void *x )
{
   (void)_mem.pageRead( addr, x );
   return *this;
}


FlashCache& FlashCache::pageWrite( uint32_t addr, const void *x )
{
   (void)_mem.pageWrite( addr, x );
   return *this;
}


FlashCache& FlashCache::sectorErase( uint32_t addr )
{
   (void)_mem.sectorErase( addr );
   return *this;
}


FlashCache& FlashCache::blockErase( uint32_t addr )
{
   (void)_mem.blockErase( addr );
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

/*EoF*/
