
#include "Parameters.h"

using namespace qb50;


const Parameters::definition Parameters::defs[ _QB50_NPARAMS ] = {

   /* params[ 0 .. 15 ]       min max def                               min max def */
   { PARAM_NONE,               0,  0,  0 },  { PARAM_CW_CYCLE_TX,        0, 10,  4 },
   { PARAM_WODEX_CYCLE_TX,     1,  3,  1 },  { PARAM_FIPEX_SCRIPT_N,     1,  7,  1 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_ADCS_CYCLE_MEAS,    1,  4,  1 },
   { PARAM_GPS_CYCLE_ON,       1,  5,  2 },  { PARAM_BAT_V_LOW,          1,  7,  7 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_FM_WODEX_CYCLE_TX,  1,  4,  2 },
   { PARAM_ADCS_CYCLE_CTRL,    0, 24,  0 },  { PARAM_FM_CYCLE_ON,        1, 96, 16 },
   { PARAM_BAT_V_HIGH,         1,  5,  1 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_PA_TEMP_HIGH,       0,  7,  1 },  { PARAM_PA_TEMP_LOW,        0,  5,  4 },

   /* params[ 16 .. 31 ]      min max def                               min max def */
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },

   /* params[ 32 .. 47 ]      min max def                               min max def */
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },

   /* params[ 48 .. 63 ]      min max def                               min max def */
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 },
   { PARAM_NONE,               0,  0,  0 },  { PARAM_NONE,               0,  0,  0 }

};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Parameters::Parameters()
{ ; }


Parameters::~Parameters()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Parameters::pid_t Parameters::check( long p, long v )
{
   const Parameters::definition *def;

   if(( p < 0 ) || ( p >= _QB50_NPARAMS ))
      return PARAM_NONE;

   def = &defs[ p ];

   if(( def->pid == PARAM_NONE ) || ( v < def->min ) || ( v > def->max ))
      return PARAM_NONE;

   return def->pid;
}


Parameters::pval_t Parameters::set( Parameters::pid_t pid, Parameters::pval_t pval )
{
   Parameters::pval_t old = pv[ pid ];
   pv[ pid ] = pval;

   return old;
}


Parameters::pval_t Parameters::get( Parameters::pid_t pid )
{
   return pv[ pid ];
}

/*EoF*/
