
#include "device/AX25Out.h"
#include "device/GPIOPin.h"
#include "device/NRZI.h"


using namespace qb50;
using namespace std;


AX25Out::AX25Out( FIFO<bool>& fifo )
	: _fifo(fifo)
{
    _sendLock = xSemaphoreCreateMutex();
}


AX25Out::~AX25Out()
{
    disable();

    vSemaphoreDelete( _sendLock );
}


AX25Out& AX25Out::enable( void )
{
#if 0
    _txPin.enable().out().off();  // _txPin is in Output mode
#endif
    return *this;
}


AX25Out& AX25Out::disable( void )
{   return *this; }


//  - - - - - - - - - - - - - - //
//  F L A G    F I E L D        //
//  - - - - - - - - - - - - - - //

void AX25Out::sendFlag()
{
/*
    register uint8_t octetFlag = 0x7E;
    Sample bit;

    for ( int k = 0; k < 8; k++ )
            {
                bit = nrzi.push( octetFlag & 0x01 ? HIGH : LOW );
                if( !_fifo.isFull() ) {
                  _fifo.push( bit );
                }
                octetFlag >>= 1;
            }
*/
   _fifo.push( 0 )
        .push( 1 )
        .push( 1 )
        .push( 1 )
        .push( 1 )
        .push( 1 )
        .push( 1 )
        .push( 0 )
   ;
}


//  - - - - - - - - - - - - - - - - - //
//  D A T A   F R A M E   P A C K E T //
//  - - - - - - - - - - - - - - - - - //

void AX25Out::sendPacket( const uint8_t *x, unsigned len )
{
    unsigned i = 0, j = 0;
    int bit_compteur = 0;

    NRZI nrzi;

    xSemaphoreTake( _sendLock, portMAX_DELAY );

    hexdump( x, len );

    // 25 flags denoting the beginning of the frame
    for( j = 0; j < 25; j++ )
        sendFlag();

    // Beginning of the frame
    for( i = 0; i < len; i++ )
    {
        uint8_t val = x[i];

        for ( int k = 0 ; k < 8 ; ++k )
        {
            if( val & 0x01 ) // Testing bit by bit
            {
                bit_compteur++;

                if( bit_compteur == 6 )
                {
                    bit_compteur = 0;
                    if( !_fifo.isFull() )
                      _fifo.push( 0 );
                }
                if( !_fifo.isFull() )
                  _fifo.push( 1 );
            }
            else
            {
                bit_compteur = 0;
                if( !_fifo.isFull() )
                  _fifo.push( 0 );
            }

            val = val >> 1;
        }
    }

    sendFlag(); // Flag denoting the end of the frame

    xSemaphoreGive( _sendLock );

}

/*

void modeNRZI(uint8_t *dataTable)
{
    int i(0), len(0);
    uint8_t elmt = dataTable[i];
    len = sizeof(dataTable);//????

    for ( i=0; i<len; i++ )
    {
        if ( elmt &= 1 )
        {
            if ( PULLUP )
            {
                pullDn();
            }
            else
            {
                pullUp();
            }
        }
        else
        {

        }
    }
}



void fifoBuffer(const std::queue<uint8_t>& val)
{
    queue<uint8_t> stream = val;
    int dataSize = stream.size();
    int front(-1), back(-1);

    if ( stream.empty() )
    {
        stream.push_back(val);
        back += back % dataSize;
    }

    if ( !stream.empty() )
    {
        stream.front();
        (void)printf("%d", stream.front());
        stream.pop_front();
        front += front % dataSize;
    }

    if ( abs(back - front) == dataSize - 1 )
    {
        throw printf("Fifo is full");
    }

    if ( front == back )
    {
        throw printf("Fifo is empty");
    }
}



void afficherFifoBuffer(const std::queue<uint8_t>& dataFifo)
{
    queue<uint8_t> data = dataFifo;

    while ( !data.empty() )
    {
        (void)printf("%d", data.front());
        data.pop_front();
            if(!data.empty())
                (void)printf(" , ");
    }
}
*/
