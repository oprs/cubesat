
#include "Parameters.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Parameters::Parameters()
{
   pv[  0 ] = 4;
   pv[  1 ] = 1;
   pv[  2 ] = 1;
   pv[  3 ] = 3;
   pv[  4 ] = 1;
   pv[  5 ] = 2;
   pv[  6 ] = 7;
   pv[  7 ] = 0;
   pv[  8 ] = 2;
   pv[  9 ] = 0;
   pv[ 10 ] = 16;
   pv[ 11 ] = 1;
   pv[ 12 ] = 0; /* not used */
   pv[ 13 ] = 1;
   pv[ 14 ] = 4;
}


Parameters::~Parameters()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void Parameters::set( int pnum, long pval )
{
   if(( pnum < 1 ) || ( pnum > _QB50_NPARAMS ))
      throw( "Parameters::get()" );

   pv[ pnum - 1 ] = pval;
}

long Parameters::get( int pnum )
{
   if(( pnum < 1 ) || ( pnum > _QB50_NPARAMS ))
      throw( "Parameters::get()" );

   return pv[ pnum - 1 ];
}

/*EoF*/
