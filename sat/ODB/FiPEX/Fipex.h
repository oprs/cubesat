
#ifndef CFIPEX_H
#define CFIPEX_H

#include "system/qb50.h"
#include "Device.h"


namespace qb50 {

	enum fipexCommand
	{
		OBC_SU_ON  = 0x0f,
		OBC_SU_OFF = 0xf0,
		OBC_SU_END = 0xff,
		SU_PING    = 0x00,
		SU_INIT    = 0x01,
		SU_ID      = 0x04,
		SU_RSP     = 0x10,
		SU_SP      = 0x11,
		SU_HK      = 0x20,
		SU_DP      = 0x21,
		SU_STDBY   = 0x0a,
		SU_SC      = 0x0b,
		SU_SM      = 0x0c,
		SU_CAL     = 0x33,
	};

	enum fipexResponse
	{
		SU_R_ACK   = 0x02,
		SU_R_NACK  = 0x03,
		SU_R_ID    = 0x04,
		SU_R_HK    = 0x20,
		SU_R_SDP   = 0x30,
		SU_R_CAL   = 0x33,
	};

	enum fipexError
	{
		notDefined  = 0xff,
		OK          = 0x00,
		SyncError   = 0x01,
		FcsError    = 0x02,	//Frame Check Sum (XOR) wrong
		wPID        = 0x03,	//Parameter ID unknown
		Poor        = 0x04,	//Parameter Out Of Range
		wMode       = 0x05,	//Wrong mode
		wCmd        = 0x06,	//Wrong command
		wLength     = 0x07	//Wrong length
	};

	enum paramId
	{
		time_heat         = 0x00,	//0 a 300 s
		time_delay_anode  = 0x01,	//0 a 300 s
		meas_time         = 0x02,	//0 a 2000 s
		sensor            = 0x04,	//1 ou 2
		cold_resistance_1 = 0x05,	//1000 a 10 000 Ohm
		cold_resistance_2 = 0x06,	//1000 a 10 000 Ohm
		meas_interval     = 0x07,	//10 a 5 000 ms
		stm_interval      = 0x08,	//0 a 1000 s
		set_temp          = 0x64,	//1000 a 3 500
		set_max_anode     = 0x65,
		set_reference     = 0x66
	};

	enum calibration
	{
		CAL_REQ     = 0x00,
		CMC_10K0    = 0x01,
		CMC_100k    = 0x02,
		CMC_1M00    = 0x03,
		CMC_10M0    = 0x04,
		CMC_100M    = 0x05,
		HRC_1       = 0x06,
		HRC_2       = 0x07,
		WRITE_1     = 0x10,
		WRITE_2     = 0x20,
		STORE       = 0xff,
		ABORT       = 0xf0
	};

	struct stmDataStructure
	{
		uint16_t CH0; //prendre 2 octets et faire un masque sur 12 bits
		uint16_t CH1;
		uint16_t CH2;
		uint16_t CH3;
		uint16_t CH4;
		uint16_t CH5;
	};

	struct fipexDataStructure
	{
		uint16_t SENSOR_CURRENT;
		uint16_t HEATER_VOLTAGE;
		uint16_t HEATER_CURRENT;
		uint16_t ANODE_VOLTAGE;
		uint8_t  REFERENCE_DELTA;
	};

	enum state
	{
		STANDBY  = 0,
		ERREUR   = 1,
		SCIENCE  = 2,
		CHECK    = 3
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
		uint8_t  version;
		uint8_t  ID;
		uint8_t  TIME[4];
		uint16_t time_heat;
		uint16_t time_delay_anode;
		uint16_t meas_time;
		uint16_t sensor;
		uint16_t cold_resistance_1;
		uint16_t cold_resistance_2;
		uint16_t meas_interval;
		uint16_t stm_interval;
		uint16_t set_temp;
		uint16_t set_max_anode;
		uint16_t set_reference;

		StatusRegister     STATUS_REG;
		stmDataStructure   STM_sample;
		fipexDataStructure FIPEX_sample;
	};

	struct sampleHeaderdef
	{
		uint8_t gain;
		uint8_t sensor;
		uint8_t type;
		uint8_t last;
	};


	union sample
	{
		stmDataStructure   STM;
		fipexDataStructure FIPEX;
	};


	struct scienceDataPacket
	{
		uint8_t TIME_FIPEX[4];
		uint8_t TIME_STM[4];
		uint8_t ID;
		sampleHeaderdef SAMPLE_HEADER;
		sample SAMPLE;
	};


	class CFIPEX
	{
		private:
			//CSerialPort *m_serialPort;
			UART& _uart;
			bool  m_status;

		public:

			CFIPEX( UART& uart );
			~CFIPEX();
			bool initialisation();
			bool setOn();
			bool setOff();
			bool stop();
			bool ping(fipexError &erreur);
			bool getSuId(uint8_t &rspId);
			bool getLastPackage();
			bool setParameters(uint8_t data[],uint8_t length, fipexError &error);
			bool getHousekeepingPacket(houseKeepingData * data);
			bool getScienceDataPacket(scienceDataPacket *recupSDP);
			bool setStandbyMode();
			bool setHealthCheckMode();
			bool measure();
			bool calibrate(uint8_t data[],uint8_t length);

		private:

			bool getReponse(uint8_t &rspId, uint8_t data[], uint8_t &length);
			bool sendCommand(uint8_t commandId,uint8_t length, uint8_t data[]);
	};

} /* qb50 */

#endif
