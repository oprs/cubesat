
#ifndef _QB50_CW_MORSE_H
#define _QB50_CW_MORSE_H

#include "system/qb50.h"


namespace qb50 {

class Morse
{

   public:

      Morse( GPIOPin& pin );
      ~Morse();

      void writeChar( char c );
      void write( const char *x );

   private:

      GPIOPin& _pin;

};

}


#endif /*_QB50_CW_MORSE_H*/

/*EoF*/
