
#ifndef _QB50_SYS_DEVICE_GPIO_PIN_H
#define _QB50_SYS_DEVICE_GPIO_PIN_H

#ifndef _QB50_SYS_DEVICE_GPIO_H
 #error "can't include GPIO_Pin.h, try GPIO.h instead"
#endif


class Pin : public Device
{

   public:

      Pin( const char* name ) : Device( name )
      { ; }

      virtual ~Pin()
      { ; }

      virtual Pin& init   ( void )                = 0;
      virtual Pin& enable ( bool silent = false ) = 0;
      virtual Pin& disable( bool silent = false ) = 0;

      virtual Pin& in     ( void ) = 0;
      virtual Pin& out    ( void ) = 0;
      virtual Pin& on     ( void ) = 0;
      virtual Pin& off    ( void ) = 0;
      virtual Pin& toggle ( void ) = 0;
      virtual bool read   ( void ) = 0;

};

#endif /* _QB50_SYS_DEVICE_GPIO_PIN_H */

/*EoF*/
