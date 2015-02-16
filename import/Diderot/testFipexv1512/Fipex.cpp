#include "Fipex.h"

CFIPEX::CFIPEX(int numPort)
{
	m_serialPort= new CSerialPort(numPort);
	m_status=m_serialPort->m_status;
}
CFIPEX::~CFIPEX(void)
{
	delete m_serialPort;

}
bool CFIPEX::initialisation()	//testée et vérifiée le 15/01/15
{
	if(m_status)
	{
		sendCommand((byte)SU_INIT,0,NULL);
	}
}
bool CFIPEX::setOn()
{
	if(m_status)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
	}
}
bool CFIPEX::setOff()
{
	if(m_status)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
}
bool CFIPEX::getReponse(byte &rspId, byte data[], byte &length)
{
	bool retour=false;
	byte trame[205];
	byte chk=0;

	m_serialPort->read(trame,0,205);
	length=trame[2];
	//verif chk
	for(int i=1;i<length+4;i++)
	{
		chk^=trame[i];
	}

	if((chk==trame[length+4]) && (trame[0]==0x7E))
	{
		for (int i=0; i<length;i++)
		{
			data[i]=trame[i+4];
		}
		rspId=trame[1];
		retour=true;
	}
	else
	{
		rspId=0;
		length=0;
		retour=false;
	}
	return retour;

}
bool CFIPEX::sendCommand(byte commandId,byte length, byte data[])
{
	bool retour=false;
	byte trame[10]={0};

	trame[0]=0x7E;
	trame[1]=commandId;
	trame[2]=length;
	for(int i=0;i<length;i++)
	{
		trame[i+3]=data[i];
	}
	for(int i=1;i<length+3;i++)
	{
		trame[length+3]^=trame[i];
	}
	m_serialPort->write(trame,0,length+4);


	return retour;
}
bool CFIPEX::stop()
{
	//GPIO_SetBits();
}

fipexError CFIPEX::ping()	//testée et vérifiée le 15/01/15
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_PING,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=OK;
		}
		else if (rspId==SU_R_NACK)
		{
			retour=(fipexError)reponse[0];
		}
	}
	return retour;
}

bool CFIPEX::getSuId(byte *ID)
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId=0;

	sendCommand((byte)SU_ID,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ID)
		{

			retour=OK;
		}
	}
	return retour;
}/*
bool CFIPEX::getLastPackage( )
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;
	sendCommand((byte)SU_RSP,0,NULL);
}*/
bool CFIPEX::setParameters(byte data[],byte length)
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte rspId;

	sendCommand((byte)SU_SP,length,data);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=OK;
		}
		else if (rspId==SU_R_NACK)
		{
			retour=(fipexError)reponse[0];
		}
	}
	return retour;
;
}
bool CFIPEX::getHousekeepingPacket(	houseKeepingData * data)	//testée et vérifiée le 19/01/2015
{

	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_HK,0,NULL);
	bool repRecue=getReponse(rspId,reponse,length);
	if(repRecue)
	{
		if(rspId==SU_R_HK)
		{
			data->version=reponse[0];
			data->ID=reponse[1];
			for (int i=0;i<4;i++)
			{
				data->TIME[i]=reponse[2+i];
			}
			data->time_heat[0]=reponse[6];				data->time_heat[1]=reponse[7];
			data->time_delay_anode[0]=reponse[8];		data->time_delay_anode[1]=reponse[9];
			data->meas_time[0]=reponse[10];				data->meas_time[1]=reponse[11];
			data->sensor[0]=reponse[12];				data->sensor[1]=reponse[13];
			data->cold_resistance_1[0]=reponse[14];		data->cold_resistance_1[1]=reponse[15];
			data->cold_resistance_2[0]=reponse[16];		data->cold_resistance_2[1]=reponse[17];
			data->meas_intervale[0]=reponse[18];		data->meas_intervale[1]=reponse[19];
			data->stm_interval[0]=reponse[20];			data->stm_interval[1]=reponse[21];
			data->set_temp[0]=reponse[22];				data->set_temp[1]=reponse[23];
			data->set_max_anode[0]=reponse[24];			data->set_max_anode[1]=reponse[25];
			data->set_reference[0]=reponse[26];			data->set_reference[1]=reponse[27];
			data->STATUS_REG[0]=reponse[28];			data->STATUS_REG[1]=reponse[29];
			for (int j=0;j<9;j++)
				{
					data->STM_sample[j]=reponse[30+j];
				}
			for (int k=0;k<7;k++)
				{
					data->FIPEX_sample[k]=reponse[39+k];
				}
			retour=OK;
		}
	}
	return retour;
}

bool CFIPEX::getScienceDataPacket()
{
	scienceDataPacket recupSDP;
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_DP,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_SDP)
		{
			for (int i=0;i<4;i++)
			{
				recupSDP.TIME_FIPEX[i]=reponse[i];
			}
			for (int j=0;j<4;j++)
			{
				recupSDP.TIME_STM[j]=reponse[4+j];
			}
			recupSDP.ID=reponse[8];
			recupSDP.SAMPLE_HEADER_STM=reponse[9];
			for (int k=0;k<9;k++)
			{
				recupSDP.SAMPLE_STM[k]=reponse[10+k];
			}
			recupSDP.SAMPLE_HEADER_FIPEX=reponse[20];
			for (int l=0;l<7;l++)
			{
				recupSDP.SAMPLE_FIPEX[l]=reponse[21+l];
			}
			retour=OK;
		}
	}
	return retour;
}
bool CFIPEX::setStandbyMode()	//testée et vérifiée le 15/01/15
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_STDBY,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=OK;
		}
	}
	return retour;
}
bool CFIPEX::setHealthCheckMode()	//testée et vérifiée le 15/01/15
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_SC,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=OK;
		}
	}
	return retour;
}
bool CFIPEX::measure()	//testée et vérifiée le 15/01/15
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte length=0,rspId;

	sendCommand((byte)SU_SM,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=OK;
		}
	}
	return retour;
}
bool CFIPEX::calibrate(byte data[],byte length)
{
	fipexError retour=notDefined;
	byte reponse[205]={0};
	byte rspId;

	sendCommand((byte)SU_CAL,length,data);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_CAL)
		{
			retour=OK;
		}
	}
	return retour;
}

