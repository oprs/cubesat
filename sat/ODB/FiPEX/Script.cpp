
#include "Fipex.h"


using namespace qb50;


struct Cmd {
   const Fipex::CmdId id;
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


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Fipex::Script::Script()
   : _sh( 0 ), _cind( 0 ), _coff( 0 )
{ ; }


Fipex::Script::~Script()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

time_t Fipex::Script::startTime( Header *sh )
{
   return sh->stime + VKI_EPOCH;
}


unsigned Fipex::Script::repeatTime( Header *sh )
{
   return sh->rtime;
}


unsigned Fipex::Script::delay( CmdHeader *ch )
{
   const uint8_t *x = &ch->x[ ch->len + 1U ];
   unsigned sec = ((unsigned)x[1]) << 8 | x[0];

   return
      ( sec == 0xffff ) ? 0 : sec;
}

#if 0
Fipex::Script& Fipex::Script::dump( void )
{
   CmdHeader *ch;

   _cind = 0;
   _coff = 0;

   ch = next();

   for( ;; ) {
      cid = ch->id;

      if( cid == OBC_SU_END ) {
         kprintf( "%s\r\n", cmdv[ cid ]->name );
         break;
      } else {
         clen = ch->len;
       //sec  = ch->x[ clen + 1 ] | ( ch->x[ clen + 2 ] << 8 );
         sec  = delay( ch );
         kprintf( "%s @%02d:%02d\r\n", cmdv[ cid ]->name, sec / 60, sec % 60 );
      }

      ch = next();
   }

   return *this;
}
#endif


Fipex::Script& Fipex::Script::load( Header *sh )
{
   CmdHeader *ch;
   unsigned clen, cid, sec;

   if(( sh->len < 10 ) || ( sh->len > 254 )) {
      kprintf( RED( "Fipex::Script::load(): invalid script length" ) "\r\n" );
      throw FipexScriptFormatException;
   }

   _sh = sh;

   _cind = 0;
   _coff = 0;

   ch = next();

   for( ;; ) {
      cid = ch->id;

      if( cid == OBC_SU_END ) {
         kprintf( "%s\r\n", cmdv[ cid ]->name );
         break;
      } else {
         clen = ch->len;
       //sec  = ch->x[ clen + 1 ] | ( ch->x[ clen + 2 ] << 8 );
         sec  = delay( ch );
         kprintf( "%s @%02d:%02d\r\n", cmdv[ cid ]->name, sec / 60, sec % 60 );
      }

      ch = next();
   }

 //dump();
   reset();

   return *this;
}


Fipex::Script& Fipex::Script::reset( void )
{
   _cind = 0;
   _coff = 0;

   return *this;
}


Fipex::CmdHeader* Fipex::Script::next( void )
{
   CmdHeader *ch;
   unsigned cid;

   if((( _sh->len + 1 ) - _coff ) < 8 ) {
      kprintf( RED( "Fipex::Script::next(): unexpected end of script" ) "\r\n" );
      throw FipexScriptFormatException;
   }

   ch = (CmdHeader*)( _sh->x + _coff );

   if( ch->sb != 0x7e ) {
      kprintf( RED( "Fipex::Script::next(): start byte not found at offset #%lu" ) "\r\n", _coff );
      throw FipexScriptFormatException;
   }

   cid = ch->id;

   if( cmdv[ cid ] == ECMD ) {
      kprintf( RED( "Fipex::Script::next(): unsupported command 0x%02x" ) "\r\n", cid );
      throw FipexScriptFormatException;
   }

   if( cid == OBC_SU_END ) {

      _coff += 4; // OBC_SU_END is 4 bytes long

      if( _coff != (( _sh->len + 1U ) - 8U )) {
         kprintf( RED( "Fipex::Script::next(): script length mismatch" ) "\r\n" );
         throw FipexScriptFormatException;
      }

      _cind = 0;
      _coff = 0;

   } else {

      _coff += 3 /* header */ + ch->len /* payload */ + 1 /* checksum */ + 2 /* delay */;

      if( _coff >= _sh->len ) {
         kprintf( RED( "Fipex::Script::next(): command length mismatch" ) "\r\n" );
         throw FipexScriptFormatException;
      }

   }

   return ch;
}

/*EoF*/
