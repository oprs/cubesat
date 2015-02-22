
#include "device/EXTMEM.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

EXTMEM::EXTMEM( unsigned id )
   : id( id )
{
   reset();
}


EXTMEM::~EXTMEM()
{
   reset();
   disable();
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

EXTMEM& EXTMEM::reset( void )
{
   return *this;
}


EXTMEM& EXTMEM::enable( void )
{
   return *this;
}


EXTMEM& EXTMEM::disable( void )
{
   return *this;
}

/*EoF*/
