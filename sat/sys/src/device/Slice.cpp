
#include "device/Slice.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Slice::Slice( const char *name, FlashMemory& mem, const unsigned off, const unsigned len )
   : Device( name ), _mem( mem ), _off( off ), _len( len )
{ ; }


Slice::~Slice()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

Slice& Slice::init()
{
   LOG << _name << ": Storage slice at " << _mem.name()
                << ", sectors [" << _off << ':' << ( _len + _off - 1 ) << ']';

   return *this;
}


Slice& Slice::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _mem.enable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


Slice& Slice::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _mem.disable( silent );

   if( !silent )
      LOG << _name << ": disabled";

   return *this;
}


/*EoF*/
