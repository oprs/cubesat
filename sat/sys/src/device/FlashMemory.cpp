
#include "device/FlashMemory.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

FlashMemory::FlashMemory( const char *name )
   : Device( name )
{ ; }


FlashMemory::~FlashMemory()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

FlashMemory& FlashMemory::geometry( FlashMemory::Geometry *geo )
{
   geo->bpc = _geo.bpc;
   geo->ppb = _geo.ppb;
   geo->bpp = _geo.bpp;

   return *this;
}


uint32_t FlashMemory::size( void )
{
   return (uint32_t)_geo.bpc * _geo.ppb * _geo.bpp;
}

/*EoF*/
