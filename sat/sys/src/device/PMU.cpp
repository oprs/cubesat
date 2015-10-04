
#include "device/PMU.h"
#include "system/qb50.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMU::PMU( const char *name )
   : Device( name )
{ ; }


PMU::~PMU()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

PMU& PMU::init( void )
{
   LOG << _name << ": Power & Temperature Management Unit";

   return *this;
}


PMU& PMU::enable( bool silent )
{
   if( _incRef() == 0 ) {
      ADC1.enable( silent );
      ADC2.enable( silent );
      ADC3.enable( silent );
      ADC4.enable( silent );
   }

   return *this;
}


PMU& PMU::disable( bool silent )
{
   if( _decRef() == 0 ) {
      ADC4.enable( silent );
      ADC3.enable( silent );
      ADC2.enable( silent );
      ADC1.enable( silent );
   }

   return *this;
}


PMU& PMU::update( int ns )
{
   unsigned v[ 32 ];
   int i, n;

   for( n = 0 ; n < 32 ; ++n )
      v[ n ] = 0;

   for( i = 0 ; i < ns ; ++i ) {
      for( n = 0 ; n < 8 ; ++n ) {
         v[ n      ] += ADC1.readChannel( n );
         v[ n + 8  ] += ADC2.readChannel( n );
         v[ n + 16 ] += ADC3.readChannel( n );
         v[ n + 24 ] += ADC4.readChannel( n );
      }
   }

   for( n = 0 ; n < 32 ; ++n )
      _samples[ n ] = v[ n ];

   return *this;
}


/*EoF*/