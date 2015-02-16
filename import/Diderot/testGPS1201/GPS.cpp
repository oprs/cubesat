#include "GPS.h" //ajouter les fichier necessaire a la liaison serie
#include "SerialPort.h"
#include <string.h>
#include <stdlib.h>


CGPS::CGPS(int numPort)
{
	m_com= new CSerialPort(numPort,4800,USART_Parity_No,USART_WordLength_8b,USART_StopBits_1); //Creation du port serie et attribution s des different parametres
	m_status=m_com->m_status;
	for(int i=0;i<73;i++)
		m_trame[i]=0;
}

CGPS::~CGPS(void)
{
	delete m_com;

}

bool CGPS::getPosition(position *pos)
{
	bool retour= false;
	if(getTrameGGA())
	{
		if(verifierChecksum())
		{

			if(analyserTrame())
			{
				pos->heureAcquisition=m_heureAquisition;
				pos->latitude=m_latitude;
				pos->longitude=m_longitude;
				pos->nbSatellite=m_nbSatellites;
				retour=true;
			}

		}
	}
	return retour;
}

bool CGPS::getTrameGGA()
{
	bool retour=false;

	//En attente de reception d'un $
	do
	{
		m_com->read((byte&)m_trame[0]);
		//m_com->read(m_trame,0,1);
	} while(m_trame[0]!='$');

	m_com->read((byte*)m_trame,1,6);
	if(m_trame[1]=='G'&&m_trame[2]=='P'&&m_trame[3]=='G'&&m_trame[4]=='G'&&m_trame[5]=='A')
	{
		//m_com->read((byte*)m_trame,6,71);	//trame GGA possède 71 car
		int i=6;
		do
		{
			m_com->read((byte&)m_trame[i]);
			i++;
		} while (m_trame[i-1]!='\r');
		retour=true;
	}
	return retour;
}


/*bool CGPS::connect(CSerialPort m_Com)//mettre en parametre l'objet ou le cree ds main
{
	bool connecter=false;
//	m_Com.CSerialPort(numPort);
	connecter=m_Com.m_status;//methode de l'obj utiliser
	return connecter;
}*/

bool CGPS::verifierChecksum()//tester si la trame est valide
{
	bool retour=false;
	int i=0;
	byte checksumCalcule=0, checksumRecu=0;

	int taille=strlen((const char *)m_trame);

	char sChecksumRecu[3]={0};
	sChecksumRecu[0]=m_trame[taille-3];
	sChecksumRecu[1]=m_trame[taille-2];
	sChecksumRecu[2]='\0';

	checksumRecu=strtol(sChecksumRecu,NULL,16);


	for(i=1;i < taille-4;i++)
	{
	  checksumCalcule^=m_trame[i];
	}

	if(checksumCalcule==checksumRecu)
	{
		retour=true;
	}
	else
	{
		retour=false;
	}
	return retour;
}

bool CGPS::analyserTrame()//analyse de la trame recu
{
	char tempo[10]={0}; //tableau tempo Heure

	float precision=0;
	int i=0;


	// Acquisition Heure
	//heure
	tempo[0]=m_trame[7];
	tempo[1]=m_trame[8];
	tempo[2]='\0';
	m_heureAquisition.h=strtol(tempo,NULL,10);
	//minute
	tempo[0]=m_trame[9];
	tempo[1]=m_trame[10];
	tempo[2]='\0';
	m_heureAquisition.mn=strtol(tempo,NULL,10);
	//seconde
	for(i=0;i<6;i++)
	{
		tempo[i]=m_trame[i+11];
	};

	tempo[i]='\0';
	m_heureAquisition.s=atof(tempo);


	//Acquisition Latitude
	//degre
	tempo[0]=m_trame[18];
	tempo[1]=m_trame[19];
	tempo[2]='\0';
	m_latitude.degres=atoi(tempo);
	//minute
	tempo[0]=m_trame[20];
	tempo[1]=m_trame[21];
	tempo[2]='\0';
	m_latitude.mn=atoi(tempo);
	//seconde
	for (i=0;i<5;i++)
	{
		tempo[i]=m_trame[i+22];
	}
	tempo[i]='\0';
	m_latitude.s=atof(tempo);
	m_latitude.s=m_latitude.s*60;//conv en sec
	//indicateur latitude
	m_latitude.indicateur=m_trame[28];

	//Acquisition Longitude
	//degre
	tempo[0]=m_trame[30];
	tempo[1]=m_trame[31];
	tempo[2]=m_trame[32];
	tempo[3]='\0';
	m_longitude.degres=atoi(tempo);
	//minute
	tempo[0]=m_trame[33];
	tempo[1]=m_trame[34];
	tempo[2]='\0';
	m_longitude.mn=atoi(tempo);
	//seconde
	for (i=0;i<5;i++)
	{
		tempo[i]=m_trame[i+35];
	}
	tempo[i]='\0';
	m_longitude.s=atof(tempo);
	m_longitude.s=m_longitude.s*60;//conv en sec
	//indicateur longitude
	m_longitude.indicateur=m_trame[41];

	//Nb Satellites
	tempo[0]=m_trame[45];
	tempo[1]=m_trame[46];
	tempo[2]='\0';
	m_nbSatellites=atoi(tempo);

	/*
	//Positionnement
	tempo[0]=m_trame[43];
	tempo[1]='\0';
	positionnement=atoi(tempo);

	//Altitude
	tempo[0]=m_trame[51];
	tempo[1]=m_trame[52];
	tempo[2]=m_trame[53];
	tempo[3]=m_trame[54];
	tempo[4]=m_trame[55];
	tempo[5]='\0';
	m_altitude=atof(tempo);

	//unité altitude
	m_uniteAltitude=m_trame[57];

*/
	return true;
}


/*void CGPS::setGPSOn ()
{
	GPIO_SetBits(GPIOC,GPIO_Pin_3);

}
void CGPS::setGPSOff()
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}*/



