#include "system/qb50.h"
#include "AX25/AX25.h"
#include "CTCSS/CTCSS.h"

#ifdef XTRUITES
#include "XTRUITES/textualInterface.h"
#endif


using namespace std;
using namespace qb50;


extern void ADCSThread  ( Thread *self );
extern void CWThread    ( Thread *self );
extern void FiPEXThread ( Thread *self );
extern void GPSThread   ( Thread *self );
extern void CTCSSThread ( Thread *self );


/*
 * LEDS:
 *
 * 12: green   PD12
 * 13: orange  PD13
 * 14: red     PD14
 * 15: blue    PD15
 */

#if 0
 #define LED1 PD12
 #define LED2 PD13
 #define LED3 PD14
 #define LED4 PD15
#else
 #define LED1 PC5
 #define LED2 PB0
 #define LED3 PB1
 #define LED4 PA1
#endif

void thread1( Thread *self )
{

	(void)self;

	A25Lxxx::RDIDResp rdid;
	A25Lxxx::REMSResp rems;
	A25Lxxx::RDSRResp rdsr;
	MAX111x::ConvResp conv;

	uint8_t *buf = new uint8_t[1024];

	PA0.enable().pullUp().out().on();
	PA4.enable().pullUp().out().on();
	PA5.enable().pullUp().out().on();
	PA6.enable().pullUp().out().on();
	PA7.enable().pullUp().out().on();
	PC4.enable().pullUp().out().on();

    PC10.enable().out().off();

#if 0
	uint8_t rom[ 64 ] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
		0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	};
#endif

	dataMem.enable();
	softMem.enable();

#if 0
	(void)printf( "Sector Erase...\r\n" );

	dataMem.WREN();
	dataMem.SE( 0 );

	(void)printf( "Page Program...\r\n" );

	dataMem.WREN();
	dataMem.PP( 0, rom, 64 );
#endif

	for( ;; ) {
		//LED1.toggle();
		//PC10.toggle();
		//LED2.on();

		(void)printf( "[DATA]\r\n" );

		dataMem.RDID( &rdid );
		hexdump( &rdid, sizeof( rdid ));

		dataMem.REMS( &rems );
		hexdump( &rems, sizeof( rems ));

		dataMem.RDSR1( &rdsr );
		hexdump( &rdsr, sizeof( rdsr ));

		dataMem.RDSR2( &rdsr );
		hexdump( &rdsr, sizeof( rdsr ));

		dataMem.READ( 0, buf, 64 );
		hexdump( buf, 64 );

		(void)printf( "[SOFT]\r\n" );

		softMem.RDID( &rdid );
		hexdump( &rdid, sizeof( rdid ));


		softMem.REMS( &rems );
		hexdump( &rems, sizeof( rems ));

		softMem.RDSR1( &rdsr );
		hexdump( &rdsr, sizeof( rdsr ));

		softMem.RDSR2( &rdsr );
		hexdump( &rdsr, sizeof( rdsr ));

		softMem.READ( 0, buf, 64 );
		hexdump( buf, 64 );


		LED2.on();
		delay( 500 );
	}

	delete[] buf;
}


void AX25NIMAThread(Thread *self )
{

	int cnt = 0;
    uint8_t tmp8[8] = {0xAA, 0xFF, 0x01, 0xCB, 0xFF, 0x23, 0xE9, 0x44};

	for( ;; ) {
		(void)printf( "hello: %p - %d\r\n", self, cnt );
		++cnt;

		//ax25.sendPacket(tmp8, 8);
		delay( 100 );
	}
}


#ifdef XTRUITES
void XTRUITESThread(Thread *self )
{
    (void)self;

    UART3.enable();

    uint8_t keyPress;
    XTRUITES *interface= new XTRUITES();

    while(1)
    {
        UART3.read(&keyPress, 1);
        interface->readKey(keyPress);
        delay(100);
    }
}
#endif


int main( void )
{



	//LED1.enable().out().off();
	//LED2.enable().out().on();
	//LED3.enable().out().off();
	//LED4.enable().out().off();

    //EXTI1.trigged( PC9 );
	/* Antenne */
	//PA15.enable().out().off();

    //ax25.enable();

    //ctcss( PB15, PB12 );
    //ctcss.enable();

	(void)createThread("Thread 1", thread1 );
/*
#ifdef XTRUITES
	(void)createThread("XTRUITE Thread"             , XTRUITESThread            );
#endif
   (void)createThread("AX25NIMAThread"             , AX25NIMAThread            );
*/
   (void)createThread("CTCSSThread", CTCSSThread );

	run();

	for( ;; );
}

/*EoF*/
