#ifndef TESTGPS_H
#define TESTGPS_H
#include "SerialPort.h"
#include <strings.h>


struct heure
{
	unsigned int h;
	unsigned int mn;
	float s;
};

struct date
{
	unsigned int j;
	unsigned int m;
	unsigned int a;
	heure heureAcquisition;
};

struct coordonnee
{
	unsigned int degres;
	unsigned int mn;
	float s;
	char indicateur;
};

struct altitude
{
	float valeurA;
	char uniteA;
};

struct position
{
	coordonnee latitude;
	coordonnee longitude;
	altitude infoAltitude;
};

struct infoGPS
{
	date dateGPS;
	position positionGPS;
	float vitesseGPS;
};

class CGPS
{
	private:
		char m_trame[90];// un tableau de "travail"
		char m_trameZDA[50];
		char m_trameGGA[90];
		char m_trameRMC[90];
		heure m_heureAquisition;
		date m_dateAquisition;
		coordonnee m_longitude;
		coordonnee m_latitude;
		altitude m_altitude;
		float m_vitesse;
		CSerialPort *m_com;
		bool m_status;

	public:
		CGPS(int numPort);
		~CGPS();
		bool getInfo(infoGPS*);

	private:
		bool getTrameGGA();
		bool getTrameZDA();
		bool getTrameRMC();
		bool verifierChecksum();
		bool analyserTrameGGA();
		bool analyserTrameRMC();
		bool analyserTrameZDA();
		bool detecterChar();
		int compterChar(int);

		bool getDate(date *dateT);
		bool getPosition(position *pos);
		bool getVitesse(float &vit);

};


#endif
