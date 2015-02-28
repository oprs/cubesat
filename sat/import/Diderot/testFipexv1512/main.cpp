#include "Fipex.h"
#include "SerialPort.h"
#include "Script.h"

int main(void)
{

	SystemInit();
	RCC_DeInit();

	CScript *script=new CScript();
	CFIPEX *fipex= new CFIPEX(1);


	byte data[3]={0},cal[10]={0};
	byte ID=0;
	houseKeepingData hkData;

	/*data[0]=0x04;
	data[1]=0x00;
	data[2]=0x01;

	fipex->setParameters(data,3);
	fipex->getSuId(&ID);
	fipex->measure();
	fipex->getHousekeepingPacket(&hkData);
	fipex->ping();
	fipex->getScienceDataPacket();*/
	int i=0;
	int j=0;

	byte commandId=0;
	byte taille=0;
	byte delay[2]={0};
	script->open(1);

	do {
		commandId=0;
		taille=0;
		delay[1]=delay[2]=0;
		j=0;

		script->getCommande(i,j,commandId,data,taille,delay);
		switch (commandId)
		{
			case SU_PING:fipex->ping();
				break;
			case SU_INIT:fipex->initialisation();
				break;
			case SU_ID:fipex->getSuId(&ID);
				break;
			case SU_SP:fipex->setParameters(data,taille);
				break;
			case SU_HK:fipex->getHousekeepingPacket(&hkData);
				break;
			case SU_DP:fipex->getScienceDataPacket();
				break;
			case SU_STDBY:fipex->setStandbyMode();
				break;
			case SU_SC:fipex->setHealthCheckMode();
				break;
			case SU_SM:fipex->measure();
				break;
			/*case SU_CAL:fipex->calibrate();
				break;*/
			default:;
		}
	} while (commandId!=OBC_SU_END);


}
