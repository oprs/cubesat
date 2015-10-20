
#ifndef _QB50_CW_MORSE_H
#define _QB50_CW_MORSE_H

#include "device/GPIO.h"


namespace qb50 {

class Morse
{

   public:

      Morse( GPIO::Pin& pin );
      ~Morse();

      void writeChar( char c );
      void write( const char *x );

   private:

      GPIO::Pin& _pin;

};

}


#endif /*_QB50_CW_MORSE_H*/

/*EoF*/
