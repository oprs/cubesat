
#include "devices.h"
#include "Fipex.h"
#include "Script.h"
#include "string.h"
#include "system/Logger.h"

using namespace qb50;

#if 0
void FiPEXThread( Thread *self )
{
   uint8_t c;

   (void)self;

   for( ;; ) {
      (void)UART2.read( &c, 1 );
      (void)UART6.write( &c, 1 );
   }
}
#endif

#if 0
void FiPEXThread1( Thread *self )
{
	(void)self;

	(void)printf( "UART2.enable()\r\n" );
	UART2.enable();

	delay( 250 );

	(void)printf( "UART2.baudRate( 9600 )\r\n" );
	UART2.baudRate( 9600 );

	delay( 250 );

/*
	SystemInit();
	RCC_DeInit();
*/

#if 0
	const char sequenceCommand[ 94 ] = {
		0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x20,0x20,0x0D,0x0A,   // Header
		0x7E,0x0F,0x00,0x0F,0x3C,0x00,0x20,0x0D,0x0A,                  // OBC_SU_ON
		0x7E,0x00,0x00,0x00,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0x11,0x03,0x00,0x00,0x00,0x12,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0x0B,0x00,0x0B,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0x04,0x00,0x04,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0x20,0x00,0x20,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0x0A,0x00,0x0A,0x01,0x00,0x20,0x0D,0x0A,
		0x7E,0xF0,0x00,0xF0,0xFF,0xFF,0x20,0x0D,0x0A,                  // OBC_SU_OFF
		0x7E,0xFF,0x01,0xFE,0x20,0x0D,0x0A                             // OBC_SU_END
	};
#endif

	const char standardCheckOut[ 145 ] = {
		0x7E,0x0F,0x00,0x0F,0x3C,0x00,0x20,0x0D,0x0A,                  // OBC_SU_ON
		0x7E,0x00,0x00,0x00,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_PING
		0x7E,0x20,0x00,0x20,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_HK @NOW
		0x7E,0x11,0x03,0x02,0x1E,0x00,0x0E,0x01,0x00,0x20,0x0D,0x0A,   // SU_SP meas_time=30 @00:01
		0x7E,0x0C,0x00,0x0C,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_SM @NOW
		0x7E,0x11,0x03,0x08,0x01,0x00,0x1B,0x3C,0x00,0x20,0x0D,0x0A,   // SU_SP stm_interval=1 @01:00
		0x7E,0x0A,0x00,0x0A,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_STDBY @NOW
		0x7E,0x20,0x00,0x20,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_HK @NOW
		0x7E,0x11,0x03,0x08,0x00,0x00,0x1A,0xFF,0xFF,0x20,0x0D,0x0A,   // SU_SP stm_interval=0 @NOW
		0x7E,0x11,0x03,0x04,0x02,0x00,0x14,0xFF,0xFF,0x20,0x0D,0x0A,   // SU_SP sensor=2 @NOW
		0x7E,0x0C,0x00,0x0C,0x1E,0x00,0x20,0x0D,0x0A,                  // SU_SM @00:30
		0x7E,0x0A,0x00,0x0A,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_STDBY @NOW
		0x7E,0x20,0x00,0x20,0xFF,0xFF,0x20,0x0D,0x0A,                  // SU_HK @NOW
		0x7E,0xF0,0x00,0xF0,0xFF,0xFF,0x20,0x0D,0x0A,                  // OBC_SU_OFF
		0x7E,0xFF,0x01,0xFE,0x20,0x0D,0x0A                             // OBC_SU_END
	};

#if 0
	const char testSU_DP[] = {
		0x7E,0x0C,0x00,0x0C,0x1E,0x00,0x20,0x0D,0x0A,                  // SU_SM @00:30
		0x7E,0x21,0x00,0x21,0x01,0x00,0x20,0x0D,0x0A
	};
#endif

	//int scriptLenght = 145;	//sequenceCommand=95
	//CScript *script=new CScript(testSU_DP,18,binaire);

	(void)printf( "new CScript()\r\n" );
	CScript *script=new CScript( standardCheckOut, 145, binaire );

	(void)printf( "new CFIPEX()\r\n" );
	CFIPEX *fipex= new CFIPEX( UART2 );

	uint8_t data[1]={0};
	uint8_t ID=0;
	houseKeepingData hkData;
	uint8_t commandId=0;
	uint8_t taille=0;
	uint8_t xdelay[2]={0};
	scienceDataPacket recupSDP;
	fipexError erreur;

	/*data[0]=0x04;
	data[1]=0x00;
	data[2]=0x01;

	fipex->setParameters(data,3);
	fipex->measure();
	fipex->getHousekeepingPacket(&hkData);*/
	//fipex->ping();
	/*fipex->getScienceDataPacket();
	fipex->getSuId(ID);
	fipex->ping();
	data[0]={0x05};
	fipex->calibrate(data,1);*/

	(void)printf( "*** FIPEX START...\r\n" );

	uint8_t x;
	UART2.read( &x, 1 );

	do
	{
		commandId=0;
		taille=0;
		xdelay[1]=xdelay[2]=0;

		delay( 100 );

		if(script->getCommande(commandId,data,taille,xdelay))
		{
			(void)printf( "--- cmd ID: 0x%02x ", commandId );
			switch (commandId)
			{
				case OBC_SU_ON:
					(void)printf( "(OBC_SU_ON)\r\n" );
					fipex->setOn();
					break;

				case SU_PING:
					(void)printf( "(SU_PING)\r\n" );
					if( fipex->ping(erreur) ) {
						(void)printf( "PING OK\r\n" );
					} else {
						(void)printf( "PING ERROR: %x\r\n", erreur );
					}
					break;

				case SU_INIT:
					(void)printf( "(SU_INIT)\r\n" );
					(void)printf( "PING\r\n" );
					if( fipex->initialisation() ) {
						(void)printf( "INIT OK\r\n" );
					} else {
						(void)printf( "INIT ERROR\r\n" );
					}
					break;

				case SU_ID:
					(void)printf( "(SU_ID)\r\n" );
					if( fipex->getSuId(ID) ) {
						(void)printf( "GETSUID OK: %x\r\n", ID );
					} else {
						(void)printf( "GETSUID ERROR\r\n" );
					}
					break;

				case SU_SP:
					(void)printf( "(SU_SP)\r\n" );
					fipex->setParameters(data,taille,erreur);
					break;

				case SU_HK:
					(void)printf( "(SU_HK)\r\n" );
					if( fipex->getHousekeepingPacket( &hkData ) ) {
						(void)printf( "HOUSEKEEPING OK\r\n" );
						(void)hexdump( &hkData, sizeof( struct houseKeepingData ));
					} else {
						(void)printf( "HOUSEKEEPING ERROR\r\n" );
					}
					break;

				case SU_DP:
					(void)printf( "(SU_HK)\r\n" );
					fipex->getScienceDataPacket(&recupSDP);
					break;

				case SU_STDBY:
					(void)printf( "(SU_STDBY)\r\n" );
					fipex->setStandbyMode();
					break;

				case SU_SC:
					(void)printf( "(SU_SC)\r\n" );
					fipex->setHealthCheckMode();
					break;

				case SU_SM:
					(void)printf( "(SU_SM)\r\n" );
					fipex->measure();
					break;

				/*case SU_CAL:fipex->calibrate();
					break;*/

				case OBC_SU_OFF:
					(void)printf( "(OBC_SU_OFF)\r\n" );
					fipex->setOff();
					break;

				default:;
					(void)printf( "(unknown)\r\n" );
			}
		}
	} while (commandId!=OBC_SU_END);

	(void)printf( "*** FIPEX DONE.\r\n" );
	for( ;; );
}
#endif
