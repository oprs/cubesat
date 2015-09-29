
#ifndef _QB50_SYS_DEVICE_SATELLITE_H
#define _QB50_SYS_DEVICE_SATELLITE_H

#include "device/GPIOPin.h"


namespace qb50 {

   class Satellite : public Device
   {

      public:

         Satellite( const char *name, GPIOPin& selPin, GPIOPin& asPin, GPIOPin& adPin );
         virtual ~Satellite();

         Satellite& init    ( void );
         Satellite& enable  ( bool silent = false );
         Satellite& disable ( bool silent = false );

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

         GPIOPin&    _selPin; /* satellite selection (in) */
         GPIOPin&    _asPin;  /* antenna status      (in) */
         GPIOPin&    _adPin;  /* antenna deploy     (out) */

   };

   extern qb50::Satellite SAT;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SATELLITE_H*/

/*EoF*/
