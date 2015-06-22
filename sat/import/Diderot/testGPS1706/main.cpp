#include "GPS.h"
#include "SerialPort.h"
#include <string.h>




int main(void)
{

	SystemInit();
	RCC_DeInit();

	CGPS *myGPS=new CGPS(3);
	infoGPS infoSat;
	bool info=false;

	info=myGPS->getInfo(&infoSat);

	delete(myGPS);
	return 0;
}
