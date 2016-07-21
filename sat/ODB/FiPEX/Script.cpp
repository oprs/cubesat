
#include "Fipex.h"

#define VKI_EPOCH 946684800


using namespace qb50;


struct Cmd {
   const Fipex::Script::ScriptCmd id;
   const char *name;
};


static const Cmd C00 = { Fipex::Script::SU_PING,    "SU_PING"    };
static const Cmd C01 = { Fipex::Script::SU_INIT,    "SU_INIT"    };
static const Cmd C04 = { Fipex::Script::SU_ID,      "SU_ID"      };
static const Cmd C0a = { Fipex::Script::SU_STDBY,   "SU_STDBY"   };
static const Cmd C0b = { Fipex::Script::SU_SC,      "SU_SC"      };
static const Cmd C0c = { Fipex::Script::SU_SM,      "SU_SM"      };
static const Cmd C0f = { Fipex::Script::OBC_SU_ON,  "OBC_SU_ON"  };
static const Cmd C10 = { Fipex::Script::SU_RSP,     "SU_RSP"     };
static const Cmd C11 = { Fipex::Script::SU_SP,      "SU_SP"      };
static const Cmd C20 = { Fipex::Script::SU_HK,      "SU_HK"      };
static const Cmd C21 = { Fipex::Script::SU_DP,      "SU_DP"      };
static const Cmd C33 = { Fipex::Script::SU_CAL,     "SU_CAL"     };
static const Cmd Cf0 = { Fipex::Script::OBC_SU_OFF, "OBC_SU_OFF" };
static const Cmd Cff = { Fipex::Script::OBC_SU_END, "OBC_SU_END" };

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

time_t Fipex::Script::startTime( ScriptHeader *sh )
{
   return sh->stime + VKI_EPOCH;
}


time_t Fipex::Script::nextTime( ScriptHeader *sh )
{
   return sh->stime + VKI_EPOCH; // XXX
}


unsigned Fipex::Script::delay( CmdHeader *ch )
{
   const uint8_t *x = &ch->x[ ch->len + 4U ];
   return ((unsigned)x[1]) << 8 | x[0];
}


Fipex::Script& Fipex::Script::load( ScriptHeader *sh )
{
   CmdHeader *ch;
   unsigned clen, cid, sec;

   if(( sh->len < 10 ) || ( sh->len > 254 )) {
      kprintf( RED( "Fipex::Script::load(): invalid script length" ) "\r\n" );
      throw ScriptFormatException;
   }

   _sh = sh;

   _cind = 0;
   _coff = 0;

   ch = next();

   while( ch != (CmdHeader*)0 ) {
      cid = ch->id;

      if( cid == OBC_SU_END ) {
         kprintf( "%s\r\n", cmdv[ cid ]->name );
      } else {
         clen = ch->len;
         sec  = ch->x[ clen + 1 ] | ( ch->x[ clen + 2 ] << 8 );
         kprintf( "%s @%02d:%02d\r\n", cmdv[ cid ]->name, sec / 60, sec % 60 );
      }

      ch = next();
   }

   _cind = 0;
   _coff = 0;

   return *this;
}


Fipex::Script::CmdHeader* Fipex::Script::next( void )
{
   CmdHeader *ch;
   unsigned cid;

   if((( _sh->len + 1 ) - _coff ) < 8 ) {
      kprintf( RED( "Fipex::Script::next(): unexpected end of script" ) "\r\n" );
      throw ScriptFormatException;
   }

   ch = (CmdHeader*)( _sh->x + _coff );

   if( ch->sb != 0x7e ) {
      kprintf( RED( "Fipex::Script::next(): start byte not found at offset #%lu" ) "\r\n", _coff );
      throw ScriptFormatException;
   }

   cid = ch->id;

   if( cmdv[ cid ] == ECMD ) {
      kprintf( RED( "Fipex::Script::next(): unsupported command 0x%02x" ) "\r\n", cid );
      throw ScriptFormatException;
   }

   if( cid == OBC_SU_END ) {

      _coff += 4; // OBC_SU_END is 4 bytes long

      if( _coff != (( _sh->len + 1U ) - 8U )) {
         kprintf( RED( "Fipex::Script::next(): script length mismatch" ) "\r\n" );
         throw ScriptFormatException;
      }

      _cind = 0;
      _coff = 0;

      ch = (CmdHeader*)0;

   } else {

      _coff += 3 /* header */ + ch->len /* payload */ + 1 /* checksum */ + 2 /* delay */;

      if( _coff >= _sh->len ) {
         kprintf( RED( "Fipex::Script::next(): command length mismatch" ) "\r\n" );
         throw ScriptFormatException;
      }

   }

   return ch;
}

/*EoF*/
