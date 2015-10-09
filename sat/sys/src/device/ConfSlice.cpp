
#include "device/ConfSlice.h"
#include "system/Logger.h"
#include "ODBConfig.h"

#include <stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ConfSlice::ConfSlice( const char *name, FlashMemory& mem, const unsigned off, const unsigned len )
   : Slice( name, mem, off, len )
{ ; }


ConfSlice::~ConfSlice()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ConfSlice& ConfSlice::init( void )
{
   Slice::init();

/*
   unsigned size = _mem.sectorSize();
   _x = new uint8_t[ size ];
*/
   _x = (uint8_t*)BKPSRAM_BASE;

   return *this;
}


ConfSlice& ConfSlice::enable( bool silent )
{
   ODBConfig *conf = (ODBConfig*)_x;
   Slice::enable( silent );

 //uint32_t addr = _off * _mem.sectorSize();
 //_mem.sectorRead( addr, _x );

   LOG << "System configuration loaded";
   LOG << "Reset count: " << conf->nReset;

   ++conf->nReset;
//   sync();

   return *this;
}


ConfSlice& ConfSlice::disable( bool silent )
{
   (void)sync();
   Slice::disable( silent );
   return *this;
}


ConfSlice& ConfSlice::sync( void )
{
   uint32_t addr = _off * _mem.pageSize();

   // XXX check if dirty

   _mem.sectorErase( addr );
   _mem.sectorWrite( addr, _x );

   return *this;
}


/*EoF*/
