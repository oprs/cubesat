
#ifndef _QB50_SYS_DEVICE_GYRO_H
#define _QB50_SYS_DEVICE_GYRO_H

#include <cstdint>


namespace qb50 {

   class Gyro
   {

      public:

         struct vec3d {
            float xr;
            float yr;
            float zr;
         };

         Gyro();
         virtual ~Gyro();

         virtual Gyro& omega( vec3d& v ) = 0;

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_GYRO_H*/

/*EoF*/
