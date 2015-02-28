#include "GPS.h"
#include "SerialPort.h"


int main(void)
{

	SystemInit();
	RCC_DeInit();

	CGPS *myGPS=new CGPS(3);
	position posSatellite;

	myGPS->getPosition(&posSatellite);

	delete(myGPS);
	return 0;
}
