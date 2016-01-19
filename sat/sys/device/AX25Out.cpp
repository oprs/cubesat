
#include "AX25Out.h"
#include "system/Logger.h"


using namespace qb50;
using namespace std;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

AX25Out::AX25Out( const char *name, FIFO<bool>& fifo )
   : Device( name ), _fifo( fifo ), _nbit( 0 ), _fcs( 0xffff )
{
   _sendLock = xSemaphoreCreateMutex();
}


AX25Out::~AX25Out()
{
    vSemaphoreDelete( _sendLock );
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

AX25Out& AX25Out::init( void )
{
   kprintf( "%s: AX.25 Controller\r\n", _name );
   return *this;
}


AX25Out& AX25Out::enable( bool silent )
{
   (void)silent;
   return *this;
}


AX25Out& AX25Out::disable( bool silent )
{
   (void)silent;
   return *this;
}


void AX25Out::sendPacket( const uint8_t *x, unsigned len )
{
   unsigned i;

   xSemaphoreTake( _sendLock, portMAX_DELAY );

   _fcs = 0xffff;

   for( i = 0; i < 25; i++ )
      _sendByte( 0x7e, false );

   for( i = 0; i < len; i++ )
      _sendByte( x[i], true );

   uint16_t fcs = _fcs ^ 0xffff;

   _sendByte(  fcs        & 0xff, true );
   _sendByte(( fcs >> 8 ) & 0xff, true );

   _sendByte( 0x7e, false );

   xSemaphoreGive( _sendLock );
}


void AX25Out::_sendByte( uint8_t x, bool stuff )
{
   uint8_t bit, lsb;

   for ( int i = 0 ; i < 8 ; ++i )
   {
      bit = x & 0x01;

      if( stuff ) {
         lsb = _fcs & 0x01;
         _fcs >>= 1;
         if( lsb != bit )
            _fcs ^= 0x8408;
      }

      if( bit ) {

         if( !_fifo.isFull() )
            _fifo.push( 1 );

         ++_nbit;

         if( stuff && ( _nbit == 5 )) {
            _nbit = 0;
            if( !_fifo.isFull() )
               _fifo.push( 0 );
         }

      } else {

         _nbit = 0;

         if( !_fifo.isFull() )
            _fifo.push( 0 );

      }

      x = x >> 1;
   }
}

/*EoF*/
