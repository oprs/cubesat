
#ifndef _QB50_FIPEX_SCRIPT_H
#define _QB50_FIPEX_SCRIPT_H

#ifndef _QB50_FIPEX_H
 #error "can't include Script.h, try Fipex.h instead"
#endif


class Script
{

   public:

      Script();
      virtual ~Script();

      enum ScriptCmd
      {
         SU_PING    = 0x00,
         SU_INIT    = 0x01,
         SU_ID      = 0x04,
         SU_STDBY   = 0x0a,
         SU_SC      = 0x0b,
         SU_SM      = 0x0c,
         OBC_SU_ON  = 0x0f,
         SU_RSP     = 0x10,
         SU_SP      = 0x11,
         SU_HK      = 0x20,
         SU_DP      = 0x21,
         SU_CAL     = 0x33,
         OBC_SU_OFF = 0xf0,
         OBC_SU_END = 0xff
      };

      struct ScriptHeader
      {
         uint8_t  len;   // script length
         uint32_t stime; // start time
         uint16_t rtime; // repeat time
         uint8_t  ccnt;  // command count
         uint8_t  x[];   // payload
      } __attribute__(( packed ));

      struct CmdHeader
      {
         uint8_t  sb;    // start byte
         uint8_t  id;    // command ID
         uint8_t  len;   // payload length
         uint8_t  x[];   // payload
      } __attribute__(( packed ));

      struct RspHeader
      {
         uint8_t  sb;    // start byte
         uint8_t  id;    // response ID
         uint8_t  len;   // payload length
         uint8_t  seq;   // sequence count
         uint8_t  x[];   // payload
      } __attribute__(( packed ));

      static time_t   startTime ( ScriptHeader *sh );
      static time_t   nextTime  ( ScriptHeader *sh );
      static unsigned delay     ( CmdHeader    *ch );

      Script&    load ( ScriptHeader *sh );
      CmdHeader* next ( void );


   private:

      ScriptHeader *_sh;

      unsigned _cind; // current command index
      unsigned _coff; // current command offset

};


#endif /*_QB50_FIPEX_SCRIPT_H*/

/*EoF*/
