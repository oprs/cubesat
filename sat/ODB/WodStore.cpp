
#include "WodStore.h"
#include "system/Logger.h"
#include "Config.h"
#include "devices.h"

#include <cstring>
#include <ctime>

using namespace qb50;


WodStore qb50::WOD( "WOD", FCACHE ); // global WOD database


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

WodStore::WodStore( const char *name, FlashCache& mem )
   : Device( name ), _mem( mem )
{ ; }


WodStore::~WodStore()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

WodStore& WodStore::init( void )
{
   return *this;
}


WodStore& WodStore::enable( bool debug )
{
   (void)lock();
   _mem.enable( debug );
   (void)unlock();

kprintf( "wHead: 0x%08x\r\n", CONF.wHead() );
kprintf( "wTail: 0x%08x\r\n", CONF.wTail() );

   return *this;
}


WodStore& WodStore::disable( bool debug )
{
   (void)lock();
   _mem.disable( debug );
   (void)unlock();

   return *this;
}


WodStore& WodStore::clear( void )
{
   (void)lock();

   (void)CONF.wHead( NIL );
   (void)CONF.wTail( NIL );

   (void)unlock();

   return *this;
}


WodStore& WodStore::read( WEnt *wod, void *x )
{
   (void)lock();
   _read( wod, x );
   (void)unlock();

   return *this;
}


WodStore& WodStore::write( WEnt *wod, const void *x )
{
   (void)lock();
   _write( wod, x );
   (void)unlock();

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void WodStore::_write( WEnt *wod, const void *x )
{
   E64 e64;
   WEnt prev;

   RTC::Time tm;

   RTC0.getTime( tm );
   wod->time  = RTC::conv( tm );
   wod->ticks = ticks();
   wod->xxx   = 0;

   uint32_t wHead = CONF.wHead();
   uint32_t wTail = CONF.wTail();

kprintf( "WodStore::_write(), wHead: 0x%08x, len: %u\r\n", wHead, wod->len );
hexdump( wod, sizeof( WEnt ));
hexdump( x, wod->len );
   e64.push( (const uint8_t*)wod + 4, sizeof( WEnt ) - 4 );
   e64.push( x, wod->len );
   e64.dump();

   if(( wHead == NIL ) || ( wTail == NIL )) {

      /* store is empty */

      wod->prev = NIL;

      (void)_mem.write( 0,                  wod, sizeof( WEnt ));
      (void)_mem.write( 0 + sizeof( WEnt ), x,   wod->len      );

      (void)CONF.wHead( 0 );
      (void)CONF.wTail( 0 );

   } else {

      /* XXX check for overwriting */

      (void)_mem.read( wHead, &prev, sizeof( WEnt ));
hexdump( &prev, sizeof( WEnt ));

      wod->prev = wHead;
      wHead += sizeof( WEnt ) + prev.len;
kprintf( "WodStore::_write(), wHead: 0x%08x (after)\r\n", wHead );
kprintf( "WodStore::_write(), prev.len: %u\r\n", prev.len );

      (void)_mem.write( wHead,                  wod, sizeof( WEnt ));
      (void)_mem.write( wHead + sizeof( WEnt ), x,   wod->len      );

      (void)CONF.wHead( wHead );

   }
}


void WodStore::_read( WEnt *wod, void *x )
{
   uint32_t wHead = CONF.wHead();
   uint32_t wTail = CONF.wTail();

   if( wHead == NIL ) {

      wod->prev  = NIL;
      wod->type  = NONE;
      wod->xxx   = 0;
      wod->len   = 0;
      wod->ticks = 0;
      wod->time  = 0;

   } else {

      (void)_mem.read( wHead,                  wod, sizeof( WEnt ));
      (void)_mem.read( wHead + sizeof( WEnt ), x,   wod->len      );

      if( wHead == wTail ) {

         (void)CONF.wHead( NIL );
         (void)CONF.wTail( NIL );

      } else {

         (void)CONF.wHead( wod->prev );

      }

   }
}

/*EoF*/
