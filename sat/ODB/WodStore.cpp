
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


WodStore& WodStore::read( WEH *hdr, void *x )
{
   (void)lock();
   _read( hdr, x );
   (void)unlock();

   return *this;
}


WodStore& WodStore::peek( WEH *hdr, void *x )
{
   (void)lock();
   _peek( hdr, x );
   (void)unlock();

   return *this;
}


WodStore& WodStore::write( EntryType type, const void *x, unsigned len, WEH *hdr )
{
   WEH _hdr;

   if( hdr == (WEH*)0 )
      hdr = &_hdr;

   (void)lock();
   _write( type, x, len, hdr );
   (void)unlock();

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void WodStore::_write( EntryType type, const void *x, unsigned len, WEH *hdr )
{
   RTC::Time tm;

   uint32_t wHead = CONF.wHead();
 //uint32_t wTail = CONF.wTail();
   uint32_t wNext;

kprintf( "WodStore::_write(), wHead: 0x%08x\r\n", wHead );
hexdump( x, len );
b64dump( x, len );

   if( wHead == NIL ) {
      wNext = 0;
   } else {
      (void)_mem.read( wHead, hdr, sizeof( WEH ));
      wNext = wHead + hdr->len;
   }

   /* WOD header */

   RTC0.getTime( tm );

   hdr->type  = type;
   hdr->len   = len + sizeof( WEH );
   hdr->ticks = ticks();
   hdr->prev  = wHead;
   hdr->time  = RTC::conv( tm );

   (void)_mem.write( wNext, hdr, sizeof( WEH ));
   (void)_mem.write( wNext + sizeof( WEH ), x, len );

   if( wHead == NIL ) {
      (void)CONF.wTail( 0 );
   }

   (void)CONF.wHead( wNext );
}


void WodStore::_read( WEH *hdr, void *x )
{
   _peek( hdr, x );

   if( hdr->prev != NIL ) {
      (void)CONF.wHead( hdr->prev );
   }
}


void WodStore::_peek( WEH *hdr, void *x )
{
   uint32_t wHead = CONF.wHead();

   if( wHead == NIL ) {

      hdr->type  = NONE;
      hdr->len   = 0;
      hdr->ticks = 0;
      hdr->prev  = NIL;
      hdr->len   = 0;

   } else {

      (void)_mem.read( wHead, hdr, sizeof( WEH ));
      (void)_mem.read( wHead + sizeof( WEH ), x, hdr->len - sizeof( WEH ));

   }
}

/*EoF*/
