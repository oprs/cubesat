
#ifndef _QB50_SYSTEM_DEVICE_H
#define _QB50_SYSTEM_DEVICE_H


namespace qb50 {

   class Device
   {
      public:

         Device() {}
         virtual ~Device() {}

         virtual void reset   ( void ) = 0;
         virtual void enable  ( void ) = 0;
         virtual void disable ( void ) = 0;
   };

} /* qb50 */


#endif /*_QB50_SYSTEM_DEVICE_H*/

/*EoF*/
