
#include "system/qb50.h"
#include <stdio.h>

#include "../../../ODB/AX25/AX25.cpp"
#include "../../../ODB/AX25/AX25_test.cpp"


using namespace qb50;


extern void ADCSThread              ( Thread *self );
extern void CWThread                ( Thread *self );
extern void FiPEXThread             ( Thread *self );
extern void GPSThread               ( Thread *self );

/** Test for AX25 **/
extern void AX25_PacketExampleThread   ( Thread *self );


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
	maxADC.enable();

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

		(void)printf( "[ADC]\r\n" );

		maxADC.conv( MAX111x::CH0, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH1, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH2, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH3, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH4, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH5, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH6, &conv );
		hexdump( &conv, sizeof( conv ));

		maxADC.conv( MAX111x::CH7, &conv );
		hexdump( &conv, sizeof( conv ));

		delay( 500 );
	}

	delete[] buf;


}


void TestThread( Thread *self )
{
	int cnt = 0;

	for( ;; ) {
		(void)printf( "hello: %p - %d\r\n", self, cnt );
		++cnt;
		delay( 100 );
	}
}

/**
 *  Lighting garland of LED
 *
 *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 *  @version    1.0             (22/04/2015)
 */
#define _LED_GARLAND_
#ifdef _LED_GARLAND_
void LED_GARLAND_0( Thread *self )
{
	while(1) {
        (void)self;
        delay(100);
        PA1.toggle();
        delay(1100);
	}
}
void LED_GARLAND_1( Thread *self )
{
	while(1) {
        (void)self;
        delay(200);
        PB1.toggle();
        delay(1000);
	}
}
void LED_GARLAND_2( Thread *self )
{
	while(1) {
        (void)self;
        delay(300);
        PB0.toggle();
        delay(900);
	}
}
void LED_GARLAND_3( Thread *self )
{
	while(1) {
        (void)self;
        delay(400);
        PC5.toggle();
        delay(800);
	}
}
void LED_GARLAND_4( Thread *self )
{
	while(1) {
        (void)self;
        delay(500);
        PC10.toggle();
        delay(700);
	}
}
void LED_GARLAND_5( Thread *self )
{
	while(1) {
        (void)self;
        delay(600);
        PC13.toggle();
        delay(600);
	}
}
void LED_GARLAND_6( Thread *self )
{
	while(1) {
        (void)self;
        delay(700);
        PB14.toggle();
        delay(500);
	}
}
void LED_GARLAND_7( Thread *self )
{
	while(1) {
        (void)self;
        delay(800);
        PA15.toggle();
        delay(400);
	}
}
void LED_GARLAND_8( Thread *self )
{
	while(1) {
        (void)self;
        delay(900);
        PC3.toggle();
        delay(300);
	}
}
void LED_GARLAND_9( Thread *self )
{
	while(1) {
        (void)self;
        delay(1000);
        PB12.toggle();
        delay(200);
	}
}
void LED_GARLAND_10( Thread *self )
{
	while(1) {
        (void)self;
        delay(1100);
        PB15.toggle();
        delay(100);
	}
}
void LED_GARLAND_11( Thread *self )
{
	while(1) {
        (void)self;
        delay(1200);
        PB13.toggle();
        delay(0);
	}
}
#endif /* _LED_GARLAND_ */

int main( void )
{
	/* enable UART6 (debug) */

	UART6.enable();

	/* create worker threads */

	(void)createThread( "ADCSThread",               ADCSThread              );
	(void)createThread( "CWThread",                 CWThread                );
	(void)createThread( "FiPEXThread",              FiPEXThread             );
	(void)createThread( "GPSThread",                GPSThread               );

	/* create test threads */
	(void)createThread( "AX25_PacketExampleThread", AX25_PacketExampleThread);


	LED1.enable().out().off();
	LED2.enable().out().off();
	LED3.enable().out().off();
	LED4.enable().out().off();
	PC13.enable().out().off();
	PC3.enable().out().off();
	PB12.enable().out().off();
	PB13.enable().out().off();
	PB14.enable().out().off();
	PC10.enable().out().off();
	PA15.enable().out().off();
	PB15.enable().out().off();


	/* Antenne */
	//PA15.enable().out().off();

	createThread( "Thread 1", thread1 );
	createThread( "test", TestThread );

    // Lighting garland of LED
    #ifdef _LED_GARLAND_
        createThread( "LED_GARLAND_0",   LED_GARLAND_0 );
        createThread( "LED_GARLAND_1",   LED_GARLAND_1 );
        createThread( "LED_GARLAND_2",   LED_GARLAND_2 );
        createThread( "LED_GARLAND_3",   LED_GARLAND_3 );
        createThread( "LED_GARLAND_4",   LED_GARLAND_4 );
        createThread( "LED_GARLAND_5",   LED_GARLAND_5 );
        createThread( "LED_GARLAND_6",   LED_GARLAND_6 );
        createThread( "LED_GARLAND_7",   LED_GARLAND_7 );
        createThread( "LED_GARLAND_8",   LED_GARLAND_8 );
        createThread( "LED_GARLAND_9",   LED_GARLAND_9 );
        createThread( "LED_GARLAND_10",   LED_GARLAND_10 );
        createThread( "LED_GARLAND_11",   LED_GARLAND_11 );
    #endif /* _LED_GARLAND_ */

	run();

	for( ;; );
}


/*EoF*/
