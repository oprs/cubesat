
#include "devices.h"
#include "Fipex.h"
#include <stdio.h>
#include <stdlib.h>


using namespace qb50;


CFIPEX::CFIPEX( UART& uart )
	: _uart( uart ), m_status( true )
{
	//m_serialPort= new CSerialPort(numPort);
	//m_status = m_serialPort->m_status;
}

CFIPEX::~CFIPEX(void)
{
	//delete m_serialPort;

}
bool CFIPEX::initialisation()	//testée et vérifiée le 15/01/15
{
	if(m_status)
	{
		sendCommand((uint8_t)SU_INIT,0,NULL);
	}

	return true;
}

bool CFIPEX::setOn()
{
	if(m_status)
	{
		//GPIO_SetBits(GPIOB,GPIO_Pin_14);
		PB14.enable().out();
		PB14.off();
	}

	return true;
}

bool CFIPEX::setOff()
{
	if(m_status)
	{
		PB14.on();
		//GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}

	return true;
}

bool CFIPEX::getReponse(uint8_t &rspId, uint8_t data[], uint8_t &length)
{
	bool retour=false;
	uint8_t trame[205];
	uint8_t chk=0;

	//m_serialPort->read(trame,0,205);
	(void)_uart.read( trame, 205 );
	length=trame[2];
	//verif chk
	for(int i=1;i<length+4;i++)
	{
		chk^=trame[i];
	}

(void)printf( "TRANE LENGTH: %d\n", length );
hexdump( trame, length+4 );

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

bool CFIPEX::sendCommand( uint8_t commandId, uint8_t length, uint8_t data[] )
{
	bool retour = false;
	uint8_t trame[10]={0};

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

	retour = ( _uart.write( trame, length+4 ) == (size_t)( length+4 ));

	return retour;
}

bool CFIPEX::stop()
{
	//GPIO_SetBits();
	return true;
}

bool CFIPEX::ping(fipexError &error)	//testée et vérifiée le 15/01/15
{
	bool retour = false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;

	if(sendCommand((uint8_t)SU_PING,0,NULL))
	{
		if(getReponse(rspId,reponse,length))
		{
			(void)printf( "getReponse OK\r\n" );
			retour=true;
			if(rspId==SU_R_ACK)
			{
				error=OK;
			}
			else if (rspId==SU_R_NACK)
			{
				error=(fipexError)reponse[0];
			}
		} else {
			(void)printf( "getReponse ERROR\r\n" );
		}
	}
	return retour;
}

bool CFIPEX::getSuId(uint8_t &ID)
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId=0;

	sendCommand((uint8_t)SU_ID,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ID)
		{
			ID=reponse[0];
			retour=true;
		}
	}
	return retour;
}
/*bool CFIPEX::getLastPackage( )
{
	fipexError retour=notDefined;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId=0;

	sendCommand((uint8_t)SU_RSP,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_)
		{
			ID=reponse[0];
			retour=OK;
		}
	}
	return retour;
}*/
bool CFIPEX::setParameters(uint8_t data[],uint8_t length,fipexError &error)
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t rspId;

	sendCommand((uint8_t)SU_SP,length,data);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=true;
		}
		else if (rspId==SU_R_NACK)
		{
			retour=false;
			error=(fipexError)reponse[0];
		}
	}
	return retour;
;
}
bool CFIPEX::getHousekeepingPacket(	houseKeepingData * data ) //testée et vérifiée le 19/01/2015
{

	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;

	sendCommand((uint8_t)SU_HK,0,NULL);
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

			data->time_heat=reponse[7];
			data->time_heat<<=8;
			data->time_heat+=reponse[6];

			data->time_delay_anode=reponse[9];
			data->time_delay_anode<<=8;
			data->time_delay_anode+=reponse[8];

			data->meas_time=reponse[11];
			data->meas_time<<=8;
			data->meas_time+=reponse[10];

			data->sensor=reponse[13];
			data->sensor<<=8;
			data->sensor+=reponse[12];

			data->cold_resistance_1=reponse[15];
			data->cold_resistance_1<<=8;
			data->cold_resistance_1+=reponse[14];

			data->cold_resistance_2=reponse[17];
			data->cold_resistance_2<<=8;
			data->cold_resistance_2+=reponse[16];

			data->meas_interval=reponse[19];
			data->meas_interval<<=8;
			data->meas_interval+=reponse[18];

			data->stm_interval=reponse[21];
			data->stm_interval<<=8;
			data->stm_interval+=reponse[20];

			data->set_temp=reponse[23];
			data->set_temp<<=8;
			data->set_temp+=reponse[22];

			data->set_max_anode=reponse[25];
			data->set_max_anode<<=8;
			data->set_max_anode+=reponse[24];

			data->set_reference=reponse[27];
			data->set_reference<<=8;
			data->set_reference+=reponse[26];

			uint16_t tempo=reponse[29];
			tempo<<=8;
			tempo+=reponse[28];
			data->STATUS_REG.ADCError=(bool)((tempo&0x8000)>>15);
			data->STATUS_REG.HeaterError=(bool)((tempo&0x4000)>>14);
			data->STATUS_REG.AnodeRegulationError=(bool)((tempo&0x2000)>>13);
			data->STATUS_REG.DataBufferError=(bool)((tempo&0x1000)>>12);
			data->STATUS_REG.HeaterState=(bool)((tempo&0x0800)>>11);
			data->STATUS_REG.SupplyVoltageError=(bool)((tempo&0x0400)>>10);
			data->STATUS_REG.SensorVoltageError=(bool)((tempo&0x0200)>>9);
			data->STATUS_REG.SensorCurrentError=(bool)((tempo&0x0100)>>8);
			data->STATUS_REG.HeaterVoltageError=(bool)((tempo&0x0080)>>7);
			data->STATUS_REG.HeaterCurrentError=(bool)((tempo&0x0040)>>6);
			data->STATUS_REG.XORError=(bool)((tempo&0x0020)>>5);
			data->STATUS_REG.etat=(state)(tempo&0x0003);

			//STM
			tempo=reponse[31]&0x0F;
			tempo<<=8;
			data->STM_sample.CH0=tempo+reponse[30];

			tempo=reponse[31]>>4;
			tempo+=reponse[32]<<4;
			data->STM_sample.CH1=tempo;

			tempo=reponse[34]&0x0F;
			tempo <<= 8;
			data->STM_sample.CH2=tempo+reponse[33];

			tempo=reponse[34]>>4;
			tempo+=reponse[35]<<4;
			data->STM_sample.CH3=tempo;

			tempo=reponse[37]&0x0F;
			tempo <<= 8;
			data->STM_sample.CH4=tempo+reponse[36];

			tempo=reponse[37]>>4;
			tempo+=reponse[38]<<4;
			data->STM_sample.CH5=tempo;

			//FIPEX si disponible
			if(length>38)
			{
				tempo=reponse[40]&0x0F;
				tempo <<= 8;
				data->FIPEX_sample.SENSOR_CURRENT=tempo+reponse[39];

				tempo=reponse[40]>>4;
				tempo+=reponse[41]<<4;
				data->FIPEX_sample.HEATER_VOLTAGE=tempo;

				tempo=reponse[43]&0x0F;
				tempo <<= 8;
				data->FIPEX_sample.HEATER_CURRENT=tempo+reponse[42];

				tempo=reponse[43]>>4;
				tempo+=reponse[44]<<4;
				data->FIPEX_sample.ANODE_VOLTAGE=tempo;

				data->FIPEX_sample.REFERENCE_DELTA=reponse[45];
			}
			retour=true;
		}
	}
	return retour;
}

bool CFIPEX::getScienceDataPacket(scienceDataPacket *recupSDP)
{

	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;
	uint16_t tempo =0;
	int numSample=0;

	if(sendCommand((uint8_t)SU_DP,0,NULL))
	{
		if(getReponse(rspId,reponse,length))
		{
			if(rspId==SU_R_SDP)
			{
				for (int i=0;i<4;i++)
				{
					recupSDP->TIME_FIPEX[i]=reponse[i];
				}
				for (int j=0;j<4;j++)
				{
					recupSDP->TIME_STM[j]=reponse[4+j];
				}
				recupSDP->ID=reponse[8];
				if(length>9)
				{
					do
					{
						recupSDP->SAMPLE_HEADER.gain=reponse[9+numSample]&0x07;
						recupSDP->SAMPLE_HEADER.sensor=(reponse[9+numSample]&0x38)>>3;
						recupSDP->SAMPLE_HEADER.type=(reponse[9+numSample]&0x40)>>6;
						recupSDP->SAMPLE_HEADER.last=(reponse[9+numSample]&0x80)>>7;

						if( recupSDP->SAMPLE_HEADER.type==0)	//STM
						{
							tempo=reponse[11+numSample]&0x0F;
							tempo <<= 8;

							recupSDP->SAMPLE.STM.CH0=tempo+reponse[10+numSample];

							tempo=reponse[11+numSample]>>4;
							tempo+=reponse[12+numSample]<<4;
							recupSDP->SAMPLE.STM.CH1=tempo;

							tempo=reponse[14+numSample]&0x0F;
							tempo <<= 8;
							recupSDP->SAMPLE.STM.CH2=tempo+reponse[13+numSample];

							tempo=reponse[14+numSample]>>4;
							tempo+=reponse[15+numSample]<<4;
							recupSDP->SAMPLE.STM.CH3=tempo;

							tempo=reponse[17+numSample]&0x0F;
							tempo <<= 8;
							recupSDP->SAMPLE.STM.CH4=tempo+reponse[16+numSample];

							tempo=reponse[17+numSample]>>4;
							tempo+=reponse[18+numSample]<<4;
							recupSDP->SAMPLE.STM.CH5=tempo;

							numSample+=10;
						}
						else		//FIPEX
						{
							tempo=reponse[11+numSample]&0x0F;
							tempo <<= 8;
							recupSDP->SAMPLE.FIPEX.SENSOR_CURRENT=tempo+reponse[10+numSample];

							tempo=reponse[11+numSample]>>4;
							tempo+=reponse[12+numSample]<<4;
							recupSDP->SAMPLE.FIPEX.HEATER_VOLTAGE=tempo;

							tempo=reponse[14+numSample]&0x0F;
							tempo <<= 8;
							recupSDP->SAMPLE.FIPEX.HEATER_CURRENT=tempo+reponse[13+numSample];

							tempo=reponse[14+numSample]>>4;
							tempo+=reponse[15+numSample]<<4;
							recupSDP->SAMPLE.FIPEX.ANODE_VOLTAGE=tempo;

							recupSDP->SAMPLE.FIPEX.REFERENCE_DELTA=reponse[16+numSample];
							numSample+=8;
						}

					} while (recupSDP->SAMPLE_HEADER.last!=1);  //tant que ce n'est pas le dernier sample
				}

			}
			retour=true;
		}
	}
	return retour;
}
bool CFIPEX::setStandbyMode()	//testée et vérifiée le 15/01/15
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;

	sendCommand((uint8_t)SU_STDBY,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=true;
		}
	}
	return retour;
}
bool CFIPEX::setHealthCheckMode()	//testée et vérifiée le 15/01/15
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;

	sendCommand((uint8_t)SU_SC,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=true;
		}
	}
	return retour;
}
bool CFIPEX::measure()	//testée et vérifiée le 15/01/15
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t length=0,rspId;

	sendCommand((uint8_t)SU_SM,0,NULL);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_ACK)
		{
			retour=true;
		}
	}
	return retour;
}
bool CFIPEX::calibrate(uint8_t data[],uint8_t length)
{
	bool retour=false;
	uint8_t reponse[205]={0};
	uint8_t rspId;

	sendCommand((uint8_t)SU_CAL,length,data);
	if(getReponse(rspId,reponse,length))
	{
		if(rspId==SU_R_CAL)
		{
			retour=true;
		}
	}
	return retour;
}
