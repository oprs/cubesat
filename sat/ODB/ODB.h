
#ifndef _QB50_ODB_H
#define _QB50_ODB_H

#include "device/GPIO.h"


namespace qb50 {

   class ODB
   {

      public:

         ODB( const char *name, GPIO::Pin& selPin, GPIO::Pin& asPin, GPIO::Pin& adPin );
         virtual ~ODB();

         ODB& init( void );

         enum SatSel {
            FR01 = 0, /* X-CubeSat (Polytechnique)   */
            FR05 = 1  /* SpaceCube (Mines ParisTech) */
         };

         SatSel id( void );

         enum AntState {
            RETRACTED = 0,
            DEPLOYED  = 1
         };

         AntState aState  ( void );
         AntState aDeploy ( void );


      private:

         const char *_name;
         GPIO::Pin&  _selPin; /* satellite selection (in) */
         GPIO::Pin&  _asPin;  /* antenna status      (in) */
         GPIO::Pin&  _adPin;  /* antenna deploy     (out) */

   };

} /* qb50 */


#endif /*_QB50_ODB_H*/

/*EoF*/
