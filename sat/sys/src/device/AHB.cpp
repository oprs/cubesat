
#include <stm32f4xx.h>

#include "device/AHB.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

AHB::AHB( BusId id, const char *name ) : Bus( name ), _id( id )
{ ; }


AHB::~AHB()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

AHB& AHB::init( void )
{
   LOG << _name << ": Advanced High-Performance Bus (AMBA)";
   return *this;
}


AHB& AHB::enable( BusDevice *dev, bool silent )
{
   switch( _id ) {
      case BUS1: RCC->AHB1ENR |= dev->periph; break;
      case BUS2: RCC->AHB2ENR |= dev->periph; break;
      case BUS3: RCC->AHB3ENR |= dev->periph; break;
   }

   if( !silent )
      LOG << _name << ": " << dev->name() << " enabled";

   return *this;
}


AHB& AHB::disable( BusDevice *dev, bool silent )
{
   switch( _id ) {
      case BUS1: RCC->AHB1ENR &= ~dev->periph; break;
      case BUS2: RCC->AHB2ENR &= ~dev->periph; break;
      case BUS3: RCC->AHB3ENR &= ~dev->periph; break;
   }

   if( !silent )
      LOG << _name << ": " << dev->name() << " disabled";

   return *this;
}


uint32_t AHB::freq( void )
{
   return 0; /* XXX */
}

/*EoF*/
