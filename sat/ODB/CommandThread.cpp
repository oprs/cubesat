
#include "devices.h"
#include "CommandThread.h"
#include "Config.h"

#include <task.h> // XXX out
#include <cmath>

using namespace qb50;


static const int _mdays[ 12 ] = {
   0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};

#define ISDIGIT( c ) (((c) >= '0') && ((c) <= '9'))
#define ISWHITE( c ) ( (c) == ' '                 )
#define  ISSIGN( c ) (((c) == '+') || ((c) == '-'))


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CommandThread::CommandThread()
   : Thread( "Command Handler", 1, 2048 )
{
   _x = new uint8_t[ 128 ];
   _m.reset( _x, 128 );
}


CommandThread::~CommandThread()
{
   delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CommandThread::run( void )
{
   UART6.enable();

   std::size_t n;

   for( ;; ) {

      n = UART6.readLine( _x, 128 );
      if( n == 0 ) {
         kprintf( "\033[31;1mEMPTY COMMAND\033[0m\r\n" );
         delay( 100 );
         continue;
      }

      _m.reset( _x, n );

      if( !_parseForm() ) {
         kprintf( "\033[31;1mINVALID COMMAND\033[0m\r\n" );
         delay( 100 );
         continue;
      }

      switch( _form.type ) {
         case Form::FORM_TYPE_C:
         {
            //xQueueSendToBack( evQueue, &form, portMAX_DELAY );
            break;
         }

         case Form::FORM_TYPE_H:
         {
            char tmp[ 32 ];

            (void)strftime( tmp, 32, "%a, %d %b %Y %T %Z", gmtime( &_form.H.tv.tv_sec ));
            kprintf( "+ H %lu [%s]\r\n", _form.H.tv.tv_sec, tmp );

            break;
         }

         case Form::FORM_TYPE_P:
         {
            if( _form.P.pid == Config::PARAM_NONE ) {
               kprintf( "- P%d: parameter out of bounds\r\n", _form.P.pid );
               break;
            }

            Config::pval_t old = CONF.setParam( _form.P.pid, _form.P.pval );

            if( _form.P.pval == old ) {
               kprintf( "+ P%d,%d (unchanged)\r\n", _form.P.pid, _form.P.pval );
            } else {
               kprintf( "+ P%d,%d (was: %d)\r\n", _form.P.pid, _form.P.pval, old );
            }

            break;
         }

         case Form::FORM_TYPE_T1:
         {
            kprintf( "+ T1:\r\n" );
            kprintf( "             Satellite number: %ld\r\n", _form.T1.sat );
            kprintf( "                   Epoch year: %ld\r\n", _form.T1.eyr );
            kprintf( "        Epoch day of the year: %f\r\n",  _form.T1.edy );
            kprintf( "      1st. derivative of mm/2: %f\r\n",  _form.T1.d1m );
            kprintf( "      2nd. derivative of mm/6: %f\r\n",  _form.T1.d2m );
            kprintf( "              BSTAR drag term: %f\r\n",  _form.T1.bdt );

            break;
         }

         case Form::FORM_TYPE_T2:
         {
            kprintf( "+ T2:\r\n" );
            kprintf( "             Satellite number: %ld\r\n", _form.T2.sat );
            kprintf( "        Inclination (degrees): %f\r\n",  _form.T2.inc );
            kprintf( "            R.A.A.N (degrees): %f\r\n",  _form.T2.ran );
            kprintf( "                 Eccentricity: %f\r\n",  _form.T2.ecc );
            kprintf( "    Arg. of perigee (degrees): %f\r\n",  _form.T2.aop );
            kprintf( "       Mean anomaly (degrees): %f\r\n",  _form.T2.man );
            kprintf( "        Mean motion (rev/day): %f\r\n",  _form.T2.mmo );
            kprintf( "    Revolution number @ epoch: %ld\r\n", _form.T2.rev );

            break;
         }

         default:
            ;
      }
   }
}


int
CommandThread::_parseForm( void )
{
   /* look for separator ':' */

   while( _m.avail() > 0 ) {
      if( *_m == ':' ) break;
      ++_m;
   }

   if(( _m.avail() < 2 ) || ( *_m != ':' ))
      return 0;

   ++_m; // skip ':'

   switch( *_m ) {

      case 'C':
      case 'c':
         ++_m; // skip 'C'
         return _parseCForm();

      case 'H':
      case 'h':
         ++_m; // skip 'H'
         return _parseHForm();

      case 'P':
      case 'p':
         ++_m; // skip 'P'
         return _parsePForm();

#if 0
      case 'T':
      case 't':
         ++_m; // skip 'T'
         return _parseTForm();
#endif

      default:
         ;
   }

   return 0;
}


int
CommandThread::_parseCForm( void )
{
   int i;

   //kprintf( "CForm: [%.*s]\r\n", _m.avail(), _m._x + _m._off );

   for( i = 0 ; i < 4 ; ++i ) {
      if( !_parseInteger( _form.C.argv[i] ))
         return 0;

      if( !_m.avail() || ( *(_m++) != ',' ))
         break;
   }

   _form.C.argc = i + 1;
   _form.type = Form::FORM_TYPE_C;

   return 1;
}


int
CommandThread::_parseHForm( void )
{
   size_t argc;
   long   argv[6];

   //kprintf( "HForm: [%.*s]\r\n", _m.avail(), _m._x + _m._off );

   for( argc = 0 ; argc < 6 ; ++argc ) {
      if(( !_m.avail() ) || ( *(_m++) != ',' ))
         break;

      if( !_parseInteger( argv[argc] ))
         break;;
   }

   if( argc < 3 ) return 0;

   while( argc < 6 )
      argv[argc++] = 0;

   // see: https://github.com/git/git/blob/master/date.c
   //      https://en.wikipedia.org/wiki/Leap_year

   long dd = argv[0];
   long mm = argv[1] - 1;
   long yy = argv[2] - 1970;

   if(( yy < 0 ) || ( yy > 129 )) return 0;
   if(( mm < 0 ) || ( mm > 11  )) return 0;

   if(( mm < 2 ) || (( yy + 2 ) % 4 ))
      --dd;

   if(( argv[3] < 0 ) || ( argv[4] < 0 ) || ( argv[5] < 0 ))
      return 0;

   time_t ts = ( yy * 365 + ( yy + 1 ) / 4 + _mdays[mm] + dd ) * 24 * 60 * 60
             + argv[3] * 60 * 60
             + argv[4] * 60
             + argv[5];

   _form.H.tv.tv_sec  = ts;
   _form.H.tv.tv_usec = 0;

   _form.type = Form::FORM_TYPE_H;

   return 1;
}


int
CommandThread::_parsePForm( void )
{
   long p, v;

   if( !_parseInteger( p ))
      return 0;

   if(( !_m.avail() ) || ( *(_m++) != ',' ))
      return 0;

   if( !_parseInteger( v ))
      return 0;

   _form.P.pid = CONF.chkParam( p, v );

   if( _form.P.pid == Config::PARAM_NONE ) {
      _form.P.pval = 0;
   } else {
      _form.P.pval = v & _QB50_PVAL_MASK;
   }

   _form.type = Form::FORM_TYPE_P;

   return 1;
}


#if 0
int
CommandThread::_parseTForm( void )
{
   if( !_m.avail() )
      return 0;

   switch( *_m ) {

      case '1':
         ++_m; // skip '1'
         return _parseT1Form();

      case '2':
         ++_m; // skip '2'
         return _parseT2Form();

      default:
         ;

   };

   return 0;
}


int
CommandThread::_parseT1Form( void )
{
   if( _m.avail() != 69 )
      return 0;

/*
   if( !_checkTLESum( x, n ))
      return 0;
*/

   if( !_parseInteger  ( _form.T1.sat, 2,   5 )
    || !_parseInteger  ( _form.T1.eyr, 18,  2 )
    || !_parseDouble   ( _form.T1.edy, 20, 12 )
    || !_parseDouble   ( _form.T1.d1m, 33, 10 )
    || !_parseNoradSci ( _form.T1.d2m, 44,  8 )
    || !_parseNoradSci ( _form.T1.bdt, 53,  8 ))
      return 0;

   _form.type = Form::FORM_TYPE_T1;

   return 1;
}


int
CommandThread::_parseT2Form( void )
{
   if( _m.avail() != 69 )
      return 0;

/*
   if( !_checkTLESum( x, n ))
      return 0;
*/

   if( !_parseInteger ( _form.T2.sat,  2,  5 )
    || !_parseDouble  ( _form.T2.inc,  8,  8 )
    || !_parseDouble  ( _form.T2.ran, 17,  8 )
    || !_parseDecimal ( _form.T2.ecc, 26,  7 )
    || !_parseDouble  ( _form.T2.aop, 34,  8 )
    || !_parseDouble  ( _form.T2.man, 43,  8 )
    || !_parseDouble  ( _form.T2.mmo, 52, 11 )
    || !_parseInteger ( _form.T2.rev, 63,  5 ))
      return 0;

   _form.type = Form::FORM_TYPE_T2;

   return 1;
}
#endif


int
CommandThread::_parseInteger( long &p )
{
   int  m = 1; /* multiplier   */
   long u = 0; /* integer part */

   uint8_t c;

   while( _m.avail() && ISWHITE( *_m ))
      ++_m;

   if( !_parseSign( m ))
      return 0;

   while( _m.avail() ) {
      c = *_m;
      if( !ISDIGIT( c )) break;
      u = u * 10 + ( c - '0' );
      ++_m;
   }

   p = u * m;

   return 1;
}


int
CommandThread::_parseDecimal( double &p )
{
   long d = 1; /* divisor      */
   long u = 0; /* decimal part */

   uint8_t c;

   if( !_m.avail() || !ISDIGIT( *_m ))
      return 0;

   while( _m.avail() ) {
      c = *_m;
      if( !ISDIGIT( c )) break;
      u = u * 10 + ( c - '0' );
      d *= 10;
      ++_m;
   }

   p = (double)u / d;

   return 1;
}


int
CommandThread::_parseDouble( double &p )
{
   int     m = 1; /* multiplier   */
   long   ip = 0; /* integer part */
   double dp = 0; /* decimal part */

   while( _m.avail() && ISWHITE( *_m ))
      ++_m;

   if( !_parseSign( m ))
      return 0;

   if( !_parseInteger( ip ))
      return 0;

   if( _m.avail() && ( *_m == '.' )) {
      ++_m;
      if( !_parseDecimal( dp ))
         dp = 0;
   }

   p = ( dp + ip ) * m;

   return 1;
}


int
CommandThread::_parseSign( int &p )
{
   if( !_m.avail() )
      return 0;

   switch( *_m ) {
      case '-': p = -1; ++_m; break;
      case '+': p =  1; ++_m; break;
       default: p =  1;       break;
   }

   return 1;
}


#if 0
int
CommandThread::_parseNoradSci( double &p, const uint8_t *x, size_t& off, size_t n )
{
   size_t off = 0;
   int      m = 0; /* multiplier   */
   double  dp = 0; /* decimal part */
   double   e = 0; /* exponent     */

   while(( off < n ) && ISWHITE( x[off] ))
      ++off;

   off +=     _parseSign( m,  x + off, n - off );
   off +=  _parseDecimal( dp, x + off, n - off );
   off += _parseExponent( e,  x + off, n - off );

   p = dp * e * m;

   return off;
}


int
CommandThread::_parseNoradExp( double &p, const uint8_t *x, size_t& off, size_t n )
{
   size_t off = 0;
   long     u = 0; /* decimal part */

   if(( n < 1 ) || !ISSIGN( x[0] )) return 0;

   off += _parseInteger( u, x + off, n - off );

   //p = exp10( u );
   p = pow( 10, u );

   return off;
}
#endif


int
CommandThread::_checkTLESum( const uint8_t *x, size_t& off, size_t n )
{
   uint8_t c;
   uint8_t s = 0;

   if(( n < 69 ) || ( !ISDIGIT( x[68] ))) return 0;

   for( off = 0 ; off < 68 ; ++off ) {
      c = x[off];
      if( ISDIGIT(c) ) {
         s = ( s + ( c - '0' )) % 10;
      } else if( c == '-' ) {
         s = ( s + 1 ) % 10;
      }
   }

   if( s != ( x[68] - '0' )) return 0;

   return 1;
}

/*EoF*/
