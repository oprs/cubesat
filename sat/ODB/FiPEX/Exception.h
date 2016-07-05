
#ifndef _QB50_FIPEX_EXCEPTION_H
#define _QB50_FIPEX_EXCEPTION_H

#include <exception>
#include <stdexcept>


namespace qb50 {

   class FipexException : public std::runtime_error
   {

      public:

         FipexException( const char *msg )
            : std::runtime_error( msg )
         { ; }

   };


   class FormatException : public FipexException
   {

      public:

         FormatException()
            : FipexException( "Fipex script format exception" )
         { ; }

   };


   extern qb50::FormatException ScriptFormatException;

} /*qb50*/


#endif /*_QB50_FIPEX_EXCEPTION_H*/

/*EoF*/
