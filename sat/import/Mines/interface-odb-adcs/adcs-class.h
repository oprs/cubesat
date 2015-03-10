#ifndef ADCS-CLASS_H_INCLUDED
#define ADCS-CLASS_H_INCLUDED




#include<stdio.h>
#include<string.h>
#include "structure.h"

class adcs
{

public:
int p=0;
void setADCSOn();
void InitADCS();
message readADCSmsg();
void writeADCSMessage(message a);
void WriteExtMemorie(signed int A,signed int *B);
int ReadExtMemorieint(signed int *D);
void setADCSOff();
adcs();

quaternion QUAT;
rotation ROT;
ping PING;
position POS;
message M_DETUMB;
message M_PING;
message M_GPS;
message M_POS;
message M_TEM;
message M_MES;
message M_QUAT;
message M_ROT;
message M_STOP;



};
#endif // ADCS-CLASS_H_INCLUDED
