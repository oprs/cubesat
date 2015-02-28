#ifndef CFIPEX_H
#define CFIPEX_H
#include "SerialPort.h"


enum fipexCommand
{
	OBC_SU_ON=0x0F,
	OBC_SU_OFF=0xF0,
	OBC_SU_END=0xFF,
	SU_PING=0x00,
	SU_INIT=0x01,
	SU_ID=0x04,
	SU_RSP=0x10,
	SU_SP=0x11,
	SU_HK=0x20,
	SU_DP=0x21,
	SU_STDBY=0x0A,
	SU_SC=0x0B,
	SU_SM=0x0C,
	SU_CAL=0x33,
};

enum fipexResponse
{
	SU_R_ACK=0x02,
	SU_R_NACK=0x03,
	SU_R_ID=0x04,
	SU_R_HK=0x20,
	SU_R_SDP=0x30,
	SU_R_CAL=0x33,
};

enum fipexError
{
	notDefined=0xFF,
	OK=0x00,
	SyncError=0x01,
	FcsError=0x02,	//Frame Check Sum (XOR) wrong
	wPID=0x03,	//Parameter ID unknown
	Poor=0x04,	//Parameter Out Of Range
	wMode=0x05,	//Wrong mode
	wCmd=0x06,	//Wrong command
	wLength=0x07,	//Wrong length
};

enum paramId
{
	time_heat=0x00,	//0 a 300 s
	time_delay_anode=0x01,	//0 a 300 s
	meas_time=0x02,	//0 a 2000 s
	sensor=0x04,	//1 ou 2
	cold_resistance_1=0x05,	//1000 a 10 000 Ohm
	cold_resistance_2=0x06,	//1000 a 10 000 Ohm
	meas_interval=0x07,	//10 a 5 000 ms
	stm_interval=0x08,	//0 a 1000 s
	set_temp=0x64,	//1000 a 3 500
	set_max_anode=0x65,
	set_reference=0x66,
};

enum calibration
{
	CAL_REQ=0x00,
	CMC_10K0=0x01,
	CMC_100k=0x02,
	CMC_1M00=0x03,
	CMC_10M0=0x04,
	CMC_100M=0x05,
	HRC_1=0x06,
	HRC_2=0x07,
	WRITE_1=0x10,
	WRITE_2=0x20,
	STORE=0xFF,
	ABORT=0xF0,
};

struct houseKeepingData
{
	byte version;
	byte ID;
	byte TIME[4];
	byte time_heat[2];
	byte time_delay_anode[2];
	byte meas_time[2];
	byte sensor[2];
	byte cold_resistance_1[2];
	byte cold_resistance_2[2];
	byte meas_intervale[2];
	byte stm_interval[2];
	byte set_temp[2];
	byte set_max_anode[2];
	byte set_reference[2];
	byte STATUS_REG[2];
	byte STM_sample[9];
	byte FIPEX_sample[7];
};

struct scienceDataPacket
{
	byte TIME_FIPEX[4];
	byte TIME_STM[4];
	byte ID;
	byte SAMPLE_HEADER_STM;
	byte SAMPLE_STM[9];
	byte SAMPLE_HEADER_FIPEX;
	byte SAMPLE_FIPEX[7];
};

class CFIPEX
{
	private:
		CSerialPort *m_serialPort;
		bool m_status;
	public:
		CFIPEX(int numPort);
		~CFIPEX();
		bool getReponse(byte &rspId, byte data[], byte &length);
		bool sendCommand(byte commandId,byte length, byte data[]);

		bool initialisation();
		bool setOn();
		bool setOff();
		bool stop();
		fipexError ping();
		bool getSuId(byte *rspId);
		bool getLastPackage();
		bool setParameters(byte data[],byte length);
		bool getHousekeepingPacket(houseKeepingData * data);
		bool getScienceDataPacket();
		bool setStandbyMode();
		bool setHealthCheckMode();
		bool measure();
		bool calibrate(byte data[],byte length);
};
#endif
