
#include "Config.h"
#include <safe_stm32f4xx.h>

using namespace qb50;


Config qb50::CONF; // global config object


const Config::definition Config::defs[ _QB50_NPARAMS ] = {

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

Config::Config()
{ ; }


Config::~Config()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

uint16_t Config::reset( void )
{
   _Store *st = (_Store*)BKPSRAM_BASE;

   return ++st->nReset;
}


void Config::clear( void )
{
   _Store *st = (_Store*)BKPSRAM_BASE;

   for( int i = 0 ; i < _QB50_NPARAMS ; ++i )
      st->pv[ i ] = defs[ i ].def;

   st->nReset = 0;
   st->wHead  = 0;
   st->wTail  = 0;
}


Config::pid_t Config::chkParam( long p, long v )
{
   const Config::definition *def;

   if(( p < 0 ) || ( p >= _QB50_NPARAMS ))
      return PARAM_NONE;

   def = &defs[ p ];

   if(( def->pid == PARAM_NONE ) || ( v < def->min ) || ( v > def->max ))
      return PARAM_NONE;

   return def->pid;
}


Config::pval_t Config::setParam( Config::pid_t pid, Config::pval_t pval )
{
   _Store *st = (_Store*)BKPSRAM_BASE;

   Config::pval_t old = st->pv[ pid ];
   st->pv[ pid ] = pval;

   return old;
}


Config::pval_t Config::getParam( Config::pid_t pid )
{
   _Store *st = (_Store*)BKPSRAM_BASE;

   return st->pv[ pid ];
}

/*EoF*/
