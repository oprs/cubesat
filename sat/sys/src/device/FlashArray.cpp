
#include "device/FlashArray.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FlashArray::FlashArray( const char *name, int nSlaves, FlashMemory *slaves[] )
   : FlashMemory( name ), _nSlaves( nSlaves ), _slaves( slaves )
{ ; }


FlashArray::~FlashArray()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

/* Device interface */

FlashArray& FlashArray::init( void )
{
   FlashMemory::Geometry geo;

   _slaves[0]->init();
   _slaves[0]->geometry( &_geo );

   for( int i = 1 ; i < _nSlaves ; ++i ) {
      _slaves[i]->init();
      _slaves[i]->geometry( &geo );
      // XXX check that geo.ppb == _geo.ppb
      // XXX check that geo.bpp == _geo.bpp
      _geo.bpc += geo.bpc;
   }

   LOG << _name << ": Virtual flash memory device (" << ( size() >> 17 ) << "Mbit)";

   return *this;
}


FlashArray& FlashArray::enable( bool silent )
{
   for( int i = 0 ; i < _nSlaves ; ++i )
      _slaves[i]->enable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


FlashArray& FlashArray::disable( bool silent )
{
   if( !silent )
      LOG << _name << ": disabled";

   for( int i = 0 ; i < _nSlaves ; ++i )
      _slaves[i]->disable( silent );

   return *this;
}


/* FlashMemory interface */

FlashArray& FlashArray::pageRead( uint32_t addr, void *x )
{
   (void)addr;
   (void)x;

   return *this;
}


FlashArray& FlashArray::pageWrite( uint32_t addr, const void *x )
{
   (void)addr;
   (void)x;

   return *this;
}


FlashArray& FlashArray::sectorErase( uint32_t addr )
{
   (void)addr;

   return *this;
}


FlashArray& FlashArray::blockErase( uint32_t addr )
{
   (void)addr;

   return *this;
}

/*EoF*/
