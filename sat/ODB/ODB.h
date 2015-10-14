
#ifndef _QB50_ODB_H
#define _QB50_ODB_H

#include "device/GPIOPin.h"


namespace qb50 {

   class ODB
   {

      public:

         ODB( const char *name, GPIOPin& selPin, GPIOPin& asPin, GPIOPin& adPin );
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
         GPIOPin&    _selPin; /* satellite selection (in) */
         GPIOPin&    _asPin;  /* antenna status      (in) */
         GPIOPin&    _adPin;  /* antenna deploy     (out) */

   };

} /* qb50 */


#endif /*_QB50_ODB_H*/

/*EoF*/
