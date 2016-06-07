
#include "b64.h"

using namespace qb50;

#define ECHR 0x40
#define CHEQ 0x3d


static const char e64v[ 64 ] = {
   'A', 'B', 'C' ,'D', 'E', 'F', 'G', 'H',
   'I', 'J', 'K' ,'L', 'M', 'N', 'O', 'P',
   'Q', 'R', 'S' ,'T', 'U', 'V', 'W', 'X',
   'Y', 'Z', 'a', 'b', 'c' ,'d', 'e', 'f',
   'g', 'h', 'i', 'j', 'k' ,'l', 'm', 'n',
   'o', 'p', 'q', 'r', 's' ,'t', 'u', 'v',
   'w', 'x', 'y', 'z', '0', '1', '2', '3',
   '4', '5', '6', '7', '8', '9', '+', '/'
};


static const uint8_t d64v[ 128 ] = {
   ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR,  ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR,
   ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR,  ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR,
   ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR, ECHR,  ECHR, ECHR, ECHR, 0x3e, ECHR, ECHR, ECHR, 0x3f,
   0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,  0x3c, 0x3d, ECHR, ECHR, ECHR, 0x00, ECHR, ECHR,

   ECHR, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,  0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e,
   0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,  0x17, 0x18, 0x19, ECHR, ECHR, ECHR, ECHR, ECHR,
   ECHR, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20,  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
   0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30,  0x31, 0x32, 0x33, ECHR, ECHR, ECHR, ECHR, ECHR
};


size_t qb50::e64( char *dst, const uint8_t *src, size_t len )
{
   size_t i = 0;
   uint8_t a, b, c;

   while( len > 0 ) {
      a = src[ 0 ];
      dst[ 0 ] = e64v[ a >> 2 ];
      if( len > 1 ) {
         b = src[ 1 ];
         dst[ 1 ] = e64v[ (( a & 0x03 ) << 4 ) | (( b & 0xf0 ) >> 4 ) ];
         if( len > 2 ) {
            c = src[ 2 ];
            dst[ 2 ] = e64v[ (( b & 0x0f ) << 2 ) | (( c & 0xc0 ) >> 6 ) ];
            dst[ 3 ] = e64v[  ( c & 0x3f ) ];
            len -= 3;
         } else {
            dst[ 2 ] = e64v[ ( b & 0x0f ) << 2 ];
            dst[ 3 ] = '=';
            len -= 2;
         }
      } else {
         dst[ 1 ] = e64v[ (( a & 0x03 ) << 4 ) ];
         dst[ 2 ] = '=';
         dst[ 3 ] = '=';
         len -= 1;
      }

      src += 3;
      dst += 4;
      i   += 4;
   }

   return i;
}


size_t qb50::d64( uint8_t *dst, const char *src, size_t len )
{
   const uint8_t *x = (const uint8_t*)src;

   uint8_t a, b, c, d;

   size_t id = 0;
   size_t is = 0;

   if(( len % 4 ) != 0 ) {
      return 0; // bad len
   }

   while( len >= 4 ) {

      a = (uint8_t)d64v[ x[ is     ]];
      b = (uint8_t)d64v[ x[ is + 1 ]];
      c = (uint8_t)d64v[ x[ is + 2 ]];
      d = (uint8_t)d64v[ x[ is + 3 ]];

      if(( a == ECHR ) || ( b == ECHR ) || ( c == ECHR ) || ( d == ECHR ))
         return 0;

      dst[ id     ] = ( a << 2 ) | ( b >> 4 );
      dst[ id + 1 ] = ( b << 4 ) | ( c >> 2 );
      dst[ id + 2 ] = ( c << 6 ) | ( d      );

      id += 3;
      is += 4;

      len -= 4;

   }

   a = (uint8_t)d64v[ x[ is     ]];
   b = (uint8_t)d64v[ x[ is + 1 ]];
   c = (uint8_t)d64v[ x[ is + 2 ]];
   d = (uint8_t)d64v[ x[ is + 3 ]];

   switch( len ) {

      case 0:
         break;

      case 1:

         if(( a == ECHR ) || ( b != CHEQ ) || ( c != CHEQ ) || ( d != CHEQ ))
            return 0;

         dst[ id     ] = ( a << 2 );
         dst[ id + 1 ] = 0;
         dst[ id + 2 ] = 0;
         dst[ id + 3 ] = 0;

         id += 1;

         break;

      case 2:

         if(( a == ECHR ) || ( b == ECHR ) || ( c != CHEQ ) || ( d != CHEQ ))
            return 0;

         dst[ id     ] = ( a << 2 ) | ( b >> 4 );
         dst[ id + 1 ] = ( b << 4 );
         dst[ id + 2 ] = 0;
         dst[ id + 3 ] = 0;

         id += 2;

         break;

      case 3:

         if(( a == ECHR ) || ( b == ECHR ) || ( c == ECHR ) || ( d != CHEQ ))
            return 0;

         dst[ id     ] = ( a << 2 ) | ( b >> 4 );
         dst[ id + 1 ] = ( b << 4 ) | ( c >> 2 );
         dst[ id + 2 ] = ( c << 6 );
         dst[ id + 3 ] = 0;

         id += 3;

         break;

   }

   return id;
}

/*EoF*/
