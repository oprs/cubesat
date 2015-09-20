
#include "Device.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Device::Device( const char *name )
   : _name( name ), _refCount( 0 )
{ ; }


Device::~Device()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

unsigned Device::_incRef( void )
{ return _refCount++; }


unsigned Device::_decRef( void )
{
   if( _refCount > 0 ) _refCount--;
      return _refCount;
}


/*EoF*/
