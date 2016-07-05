
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

      struct CmdHeader
      {
         uint8_t  sb;    // start byte
         uint8_t  id;    // command ID
         uint8_t  len;   // len
         uint8_t  x[];   // payload
      } __attribute__(( packed ));

      struct ScriptHeader
      {
         uint8_t  len;   // script length
         uint32_t stime; // start time
         uint16_t rtime; // repeat time
         uint8_t  cnt;   // command count
      } __attribute__(( packed ));

      static bool makeScript  ( const uint8_t *x, size_t len );
      static bool checkScript ( const uint8_t *x, size_t len );

      Script&    load ( const uint8_t *x, size_t len );
      CmdHeader* next ( void );


   private:

      const uint8_t *_x;
      size_t         _len;

      unsigned _ccnt; // command count
      unsigned _ccur; // current command
      unsigned _off;

};


#endif /*_QB50_FIPEX_SCRIPT_H*/

/*EoF*/
