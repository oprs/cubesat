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

struct stmDataStructure
{
	ushort CH0; //prendre 2 octets et faire un masque sur 12 bits
	ushort CH1;
	ushort CH2;
	ushort CH3;
	ushort CH4;
	ushort CH5;
};

struct fipexDataStructure
{
	ushort SENSOR_CURRENT;
	ushort HEATER_VOLTAGE;
	ushort HEATER_CURRENT;
	ushort ANODE_VOLTAGE;
	byte REFERENCE_DELTA;

};

enum state
{
	STANDBY=0,
	ERREUR=1,
	SCIENCE=2,
	CHECK=3,
};

struct StatusRegister
{
	bool ADCError;
	bool HeaterError;
	bool AnodeRegulationError;
	bool DataBufferError;
	bool HeaterState;
	bool SupplyVoltageError;
	bool SensorVoltageError;
	bool SensorCurrentError;
	bool HeaterVoltageError;
	bool HeaterCurrentError;
	bool XORError;
	bool UndefinedBit1;
	bool UndefinedBit2;
	bool UndefinedBit3;
	state etat;
};

struct houseKeepingData
{
	byte version;
	byte ID;
	byte TIME[4];
	ushort time_heat;
	ushort time_delay_anode;
	ushort meas_time;
	ushort sensor;
	ushort cold_resistance_1;
	ushort cold_resistance_2;
	ushort meas_interval;
	ushort stm_interval;
	ushort set_temp;
	ushort set_max_anode;
	ushort set_reference;
	StatusRegister STATUS_REG;
	stmDataStructure STM_sample;
	fipexDataStructure FIPEX_sample;
};

struct sampleHeaderdef
{
	byte gain;
	byte sensor;
	byte type;
	byte last;
};


union sample
{
	stmDataStructure STM;
	fipexDataStructure FIPEX;
};

struct scienceDataPacket
{
	byte TIME_FIPEX[4];
	byte TIME_STM[4];
	byte ID;
	sampleHeaderdef SAMPLE_HEADER;
	sample SAMPLE;
};

class CFIPEX
{
	private:
		CSerialPort *m_serialPort;
		bool m_status;
	public:
		CFIPEX(int numPort);
		~CFIPEX();
		bool initialisation();
		bool setOn();
		bool setOff();
		bool stop();
		bool ping(fipexError &erreur);
		bool getSuId(byte &rspId);
		bool getLastPackage();
		bool setParameters(byte data[],byte length, fipexError &error);
		bool getHousekeepingPacket(houseKeepingData * data);
		bool getScienceDataPacket(scienceDataPacket *recupSDP);
		bool setStandbyMode();
		bool setHealthCheckMode();
		bool measure();
		bool calibrate(byte data[],byte length);
	private:
		bool getReponse(byte &rspId, byte data[], byte &length);
		bool sendCommand(byte commandId,byte length, byte data[]);


};
#endif
