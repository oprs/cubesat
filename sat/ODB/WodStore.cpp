
#include "WodStore.h"
#include "system/Logger.h"
#include "Config.h"
#include "devices.h"

using namespace qb50;


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
   _sec.x    = new uint8_t[ _mem.sectorSize() ];
   _sec.addr = 0;
   _sec.size = _mem.sectorSize();

   LOG << _name << ": Whole Orbit Database at " << _mem.name();

   return *this;
}


WodStore& WodStore::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _mem.enable( silent );
   _mem.sectorRead( _sec.addr, _sec.x );

   return *this;
}


WodStore& WodStore::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _mem.disable( silent );

   return *this;
}


WodStore& WodStore::clear( void )
{
#if 0
   Config *conf = (Config*)CONF.addr();

   conf->wHead = 0;
   conf->wTail = 0;
#endif

   return *this;
}


#define INCACHE( x ) \
   (( (x) >= _sec.addr ) && ( (x) < ( _sec.addr + _sec.size )))


WodStore::Entry* WodStore::last( void )
{
#if 0
   Config *conf = (Config*)CONF.addr();

   uint32_t base = conf->wTail & ( _mem.sectorSize() - 1 );

   if( !INCACHE( base )) {
      // if( ISDIRTY( _sec )) { write( ... ); }
      _mem.sectorRead( base, _sec.x );
   }

   return (WodStore::Entry*)( _sec.x + conf->wTail - base );
#endif

   return (WodStore::Entry*)0;
}


WodStore& WodStore::write( WodStore::Entry *e )
{
#if 0
   Config *conf = (Config*)CONF.addr();

   if( !INCACHE( conf->wTail + size( e ))) {
      ;
   }

/*
   WodStore::Entry le;
   (void)read( &le );
   if( conf->wTail + size( e ))
*/
#endif

   return *this;
}


uint32_t WodStore::size( WodStore::Entry *e )
{
   uint32_t rv;

   switch( e->_type ) {
      case NIL:   rv = sizeof( WodStore::Entry      );
      case PLAIN: rv = sizeof( WodStore::PlainEntry );
      case FIPEX: rv = sizeof( WodStore::FipexEntry );
   }

   return rv;
}

/*EoF*/
