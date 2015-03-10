#include <iostream>
#include "detumbling.h"
#include "adcs-class.h"
#include <time.h>
using namespace std;
void detumbling()
{
	adcs adcs1;
	message msg;
	signed int T;
	int p;
	signed int pos[3];

//demander les parametre GPS


do{
adcs1.setADCSOn();                                                                                                                                      //1.	Mise de l’ADCS sous tension.
adcs1.InitADCS();

clock_t startt=clock();
do{

adcs1.writeADCSMessage(adcs1.M_PING);
msg=adcs1.readADCSmsg();                                //2.	Vérification que l’ADCS est fonctionnelle.
if (msg.typ== T_PING)
adcs1.PING=msg.pin;

if (adcs1.PING.p==1) break;

}
while((clock()-startt)<=5000);


if (adcs1.PING.p==0)
		break;


T=adcs1.ReadExtMemorieint(&p);                               //3.	Envoyer le temps
adcs1.M_TEM.tem.t=T;
adcs1.writeADCSMessage(adcs1.M_TEM);


pos[0]=adcs1.ReadExtMemorieint(&p);                      //Envoyer les paramètres GPS.
pos[1]=adcs1.ReadExtMemorieint(&p);
pos[2]=adcs1.ReadExtMemorieint(&p);
for (int i=0;i<=2;i++) {adcs1.M_GPS.gpss.GPST[i]=pos[i];}
adcs1.writeADCSMessage(adcs1.M_GPS);





adcs1.writeADCSMessage(adcs1.M_DETUMB);	                               	             //4.	activation du mode détumbling.

do{
clock_t start_time=clock();

adcs1.writeADCSMessage(adcs1.M_MES);                                                          //5.	activation du mode de mesure.

adcs1.writeADCSMessage(adcs1.M_QUAT);	                                //6.	reception des parametres d'attitude.
msg=adcs1.readADCSmsg();
if(msg.typ==T_QUAT)
adcs1.QUAT=msg.quat;
//fair un save

adcs1.writeADCSMessage(adcs1.M_ROT);
msg=adcs1.readADCSmsg();
if(msg.typ==T_ROT)
adcs1.ROT=msg.rot;
//fair un save

adcs1.writeADCSMessage(adcs1.M_POS);
msg=adcs1.readADCSmsg();
if(msg.typ==T_POS)
adcs1.POS=msg.pos;
//fair un save

do{
}while((clock()-start_time)<=10000)
;


} while (1);

	adcs1.writeADCSMessage(adcs1.M_STOP);	                //7.	Arrêt de tout calcul dans l’ADCS.


	adcs1.setADCSOff();				//8.	désactivation de l’ADCS.

}while(1);

}
