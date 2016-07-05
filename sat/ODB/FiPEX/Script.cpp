
#include "Fipex.h"

using namespace qb50;


struct Cmd {
   const Fipex::ScriptCmd id;
   const char *name;
};


static const Cmd C00 = { Fipex::SU_PING,    "SU_PING"    };
static const Cmd C01 = { Fipex::SU_INIT,    "SU_INIT"    };
static const Cmd C04 = { Fipex::SU_ID,      "SU_ID"      };
static const Cmd C0a = { Fipex::SU_STDBY,   "SU_STDBY"   };
static const Cmd C0b = { Fipex::SU_SC,      "SU_SC"      };
static const Cmd C0c = { Fipex::SU_SM,      "SU_SM"      };
static const Cmd C0f = { Fipex::OBC_SU_ON,  "OBC_SU_ON"  };
static const Cmd C10 = { Fipex::SU_RSP,     "SU_RSP"     };
static const Cmd C11 = { Fipex::SU_SP,      "SU_SP"      };
static const Cmd C20 = { Fipex::SU_HK,      "SU_HK"      };
static const Cmd C21 = { Fipex::SU_DP,      "SU_DP"      };
static const Cmd C33 = { Fipex::SU_CAL,     "SU_CAL"     };
static const Cmd Cf0 = { Fipex::OBC_SU_OFF, "OBC_SU_OFF" };
static const Cmd Cff = { Fipex::OBC_SU_END, "OBC_SU_END" };

#if 1

#define ECMD (Cmd*)0

static const Cmd* cmdv[ 256 ] = {
   &C00, &C01, ECMD, ECMD, &C04, ECMD, ECMD, ECMD,  ECMD, ECMD, &C0a, &C0b, &C0c, ECMD, ECMD, &C0f,
   &C10, &C11, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   &C20, &C21, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, &C33, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   &Cf0, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, &Cff
};

#else

#define ECMD 0xff

static const uint8_t cmdv[ 256 ] = {
   /* 0x00 */ Fipex::SU_PING,
   /* 0x01 */ Fipex::SU_INIT,
               ECMD, ECMD,
   /* 0x04 */ Fipex::SU_ID,
                                 ECMD, ECMD, ECMD,  ECMD, ECMD,
   /* 0x0a */ Fipex::SU_STDBY,
   /* 0x0b */ Fipex::SU_SC,
   /* 0x0c */ Fipex::SU_SM,
                                                                                  ECMD, ECMD,
   /* 0x0f */ Fipex::OBC_SU_ON,
   /* 0x10 */ Fipex::SU_RSP,
   /* 0x11 */ Fipex::SU_SP,
               ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   /* 0x20 */ Fipex::SU_HK,
   /* 0x21 */ Fipex::SU_DP,
               ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD,
   /* 0x33 */ Fipex::SU_CAL,
                           ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,

   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   /* 0xf0 */ Fipex::OBC_SU_OFF,
         ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,  ECMD, ECMD, ECMD, ECMD, ECMD, ECMD, ECMD,
   /* 0xff */ Fipex::OBC_SU_END
};

#endif


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Fipex::Script::Script()
   : _x( 0 ), _len( 0 ), _ccnt( 0 ), _ccur( 0 ), _off( 0 )
{ ; }


Fipex::Script::~Script()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

bool Fipex::Script::makeScript( const uint8_t *x, size_t len )
{
   return true;
}


bool Fipex::Script::checkScript( const uint8_t *x, size_t len )
{
   unsigned slen, ccnt, clen, off, sec, n;
   ScriptCmd cid;

   if( len < 12 ) {
      kprintf( RED( "checkScript(): garbage in payload" ) "\r\n" );
      return false;
   }

   slen = x[ 0 ];

   if(( slen > 254 ) || ( slen != ( len - 1 ))) {
      kprintf( RED( "checkScript(): error in script length" ) "\r\n" );
      return false;
   }

   ccnt = x[ 7 ];
   off  = 8;

   for( n = 0 ; n < ccnt ; ++n ) {

 //kprintf( "N: %lu, OFF: %lu, LEN: %lu\r\n", n, off, len );

      if(( len - off ) < 4 ) {
         kprintf( RED( "checkScript(): unexpected end of script" ) "\r\n" );
         return false;
      }

      if( x[ off ] != 0x7e ) {
         kprintf( RED( "checkScript(): start byte not found in cmd #%lu" ) "\r\n", n );
         return false;
      }

      cid = (ScriptCmd)( x[ off + 1 ] );

      if( cmdv[ cid ] == ECMD ) {
         kprintf( RED( "checkScript(): unsupported command 0x%02x" ) "\r\n", cid );
         return false;
      }

/*
      switch( cid ) {
      }
*/

      if( cid == OBC_SU_END ) {
         off += 4; // OBC_SU_END is 4 bytes long
         if( off != len ) {
            kprintf( RED( "checkScript(): script length mismatch" ) "\r\n" );
            return false;
         }
         kprintf( "%s\r\n", cmdv[ cid ]->name );
      } else {
         clen = 3 + x[ off + 2 ];
         off += clen;
         off += 1; // checksum
         sec = x[ off ] | ( x[ off + 1 ] << 8 );
         off += 2; // delay
         if( off >= len ) {
            kprintf( RED( "checkScript(): command length mismatch" ) "\r\n" );
            return false;
         }
         kprintf( "%s @%02d:%02d\r\n", cmdv[ cid ]->name, sec / 60, sec % 60 );
      }

   }

   return true;
}


Fipex::Script& Fipex::Script::load( const uint8_t *x, size_t len )
{
   Fipex::Script::CmdHeader *cmd;
   unsigned slen, clen, cid, sec;

   if( len < 12 ) {
      kprintf( RED( "Fipex::Script::load(): garbage in payload" ) "\r\n" );
      throw ScriptFormatException;
   }

   slen = x[ 0 ];

   if(( slen > 254 ) || ( slen != ( len - 1 ))) {
      kprintf( RED( "Fipex::Script::load(): invalid script length" ) "\r\n" );
      throw ScriptFormatException;
   }

   _x    = x;
   _len  = len;

   _ccnt = x[ 7 ];
   _ccur = 0;
   _off  = 8;

   while( _ccur < _ccnt ) {
      cmd = next();
      cid = cmd->id;

      if( cid == OBC_SU_END ) {
         kprintf( "%s\r\n", cmdv[ cid ]->name );
      } else {
         clen = cmd->len;
         sec  = cmd->x[ clen + 1 ] | ( cmd->x[ clen + 2 ] << 8 );
         kprintf( "%s @%02d:%02d\r\n", cmdv[ cid ]->name, sec / 60, sec % 60 );
      }

      ++_ccur;
   }

   _ccur = 0;
   _off  = 8;

   return *this;
}


Fipex::Script::CmdHeader* Fipex::Script::next( void )
{
   unsigned cid;
   const uint8_t *cbuf;

   if(( _len - _off ) < 4 ) {
      kprintf( RED( "Fipex::Script::next(): unexpected end of script" ) "\r\n" );
      throw ScriptFormatException;
   }

   cbuf = _x + _off;

   if( cbuf[ 0 ] != 0x7e ) {
      kprintf( RED( "Fipex::Script::next(): start byte not found at offset #%lu" ) "\r\n", _off );
      throw ScriptFormatException;
   }

   cid = cbuf[ 1 ];

   if( cmdv[ cid ] == ECMD ) {
      kprintf( RED( "Fipex::Script::next(): unsupported command 0x%02x" ) "\r\n", cid );
      throw ScriptFormatException;
   }

   if( cid == OBC_SU_END ) {

      _off += 4; // OBC_SU_END is 4 bytes long

      if( _off != _len ) {
         kprintf( RED( "Fipex::Script::next(): script length mismatch" ) "\r\n" );
         throw ScriptFormatException;
      }

   } else {

      _off += 3 /* header */ + cbuf[ 2 ] /* payload */ + 1 /* checksum */ + 2 /* delay */;

      if( _off >= _len ) {
         kprintf( RED( "Fipex::Script::next(): command length mismatch" ) "\r\n" );
         throw ScriptFormatException;
      }

   }

   return (CmdHeader*)cbuf;
}

/*EoF*/
