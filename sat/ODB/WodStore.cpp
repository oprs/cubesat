
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


WodStore& WodStore::enable( bool silent )
{
   (void)lock();
   _mem.enable( silent );
   (void)unlock();

kprintf( "wHead: 0x%08x\r\n", CONF.wHead() );
kprintf( "wTail: 0x%08x\r\n", CONF.wTail() );

   return *this;
}


WodStore& WodStore::disable( bool silent )
{
   (void)lock();
   _mem.disable( silent );
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
   WEnt prev;

   RTC::Time tm;

   RTC0.getTime( tm );
   wod->time  = RTC::conv( tm );
   wod->ticks = ticks();
   wod->xxx   = 0;

   uint32_t wHead = CONF.wHead();
   uint32_t wTail = CONF.wTail();

kprintf( "WodStore::_write(), wHead: 0x%08x\r\n", wHead );
hexdump( x, wod->len );
b64dump( x, wod->len );

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

      wod->prev = wHead;
      wHead += sizeof( WEnt ) + prev.len;

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
