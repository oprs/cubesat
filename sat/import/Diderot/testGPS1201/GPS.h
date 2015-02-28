#ifndef TESTGPS_H
#define TESTGPS\H
#include "SerialPort.h"


struct heure
{
	unsigned int h;
	unsigned int mn;
	float s;
};

struct coordonnee
{
	unsigned int degres;
	unsigned int mn;
	float s;
	char indicateur;
};

struct position
{
	heure heureAcquisition;
	coordonnee latitude;
	coordonnee longitude;
	int nbSatellite;
/*	int positionnement;
	float altitude;
	char uniteAltitude;*/
};


class CGPS
{
	private:
		char m_trame[73];
		heure m_heureAquisition;
		coordonnee m_longitude;
		coordonnee m_latitude;
		int m_positionnement;
		int m_nbSatellites;
		float precison;
		float m_altitude;
		char m_uniteAltitude;//altitude en metres
		CSerialPort *m_com;
		bool m_status;

	public:
		CGPS(int numPort);

		~CGPS();
	private:
		bool getTrameGGA();
//		bool connect(CSerialPort m_Com);
		bool verifierChecksum();//tester si la trame est valide
		bool analyserTrame();//analyse de la trame recu
	public:
		bool getPosition(position *pos);
//		void setGPSOn ();
//		void setGPSOff();

};


#endif
