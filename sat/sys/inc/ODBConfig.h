
#ifndef _QB50_SYS_ODB_CONFIG_H
#define _QB50_SYS_ODB_CONFIG_H

#include "TLE.h"


namespace qb50 {

   struct ODBConfig
   {

      uint32_t params[ 256 ];  //!< parameters
      uint16_t nReset;         //!< reset counter
      TLE      tle;            //!< latest TLE known to the satellite
    //MTT      mtt;            //!< mode-thread table
    //STT      stt;            //!< state-transition table

   };

} /* qb50 */


#endif /*_QB50_SYS_ODB_CONFIG_H*/

/*EoF*/
