#include <sys/time.h>
#include "GPS.h"
#include "SerialPort.h"
#include <string.h>
#include <stdlib.h>


CGPS::CGPS(int numPort)
{
	m_com= new CSerialPort(numPort,9600,USART_Parity_No,USART_WordLength_8b,USART_StopBits_1);
	m_status=m_com->m_status;
	for(int i=0;i<90;i++)
	{
		m_trame[i]=0;
	}
}


CGPS::~CGPS(void)
{
	delete m_com;
}

//Calcule le nombre de caractère constituant un champ de la trame
int CGPS::compterChar(int emplacement) //argument : emplacement de l'info -1 dans la trame
{
	int compterVirguleAV=0;
	int compterVirguleAP=0;
	int virguleAV=0;
	int virguleAP=0;
	int nbChar= 0;// virguleAP: detecte la virgule av ondulation // virguleAP: detecte la position de la virgule ap l'ondulation
	for(int i=0;i<90;i++)
	{
		if(m_trame[i]==',')// a chaque ',' rencontrée
		{
			//a chaque virgule les compteurs s'incremente
			compterVirguleAV=compterVirguleAV+1;
			compterVirguleAP=compterVirguleAP+1;
			//une fois l'emplacement de l'info atteinte
			if(compterVirguleAV==emplacement-1)
			{
				virguleAV=i; //emplacement du debut de l'information
			}
			if(compterVirguleAP==emplacement)//ne passera qu'a la prochaine virgule
			{
				virguleAP=i; //emplacement de la fin de l'information
				nbChar=(virguleAP-virguleAV)-1;//avec la difference des emplacement des virgule on obtient le nb de char
				break;
			}
		}
	}
	return nbChar;//retourne le nb de caracteres
}

//detecte le char '$' qui est le debut de chaque trame
bool CGPS::detecterChar()
{
	bool continuer=true;
	int i=0;
	do
	{
		m_com->read((byte&)m_trame[0]);
		if(i==250)
		{
			break;
		}
		i++;
	} while(m_trame[0]!='$');
	return continuer;
}

//execute les differentes methodes et retoune false si
//après un certaine nombre d'essai les info ne sont pas recupérées
bool CGPS::getInfo(infoGPS *infoSat)
{
	bool infoOk=false;
	int nbMax=0;//nom d'essai

	do {
		if(getTrameZDA()==true)
		{
			if(getTrameGGA()==true)
			{
				if(getTrameRMC()==true)//--> les 3 trames ont été stocker à la suite (elles ont les mêmes secondes)
				{
					if(getDate(&infoSat->dateGPS)==true)
					{
						if(getPosition(&infoSat->positionGPS)==true)
						{
							if(getVitesse(infoSat->vitesseGPS)==true)
							{
								infoOk=true;// --> toutes les info sont récuperé
							}
						}
					}
				}
			}
		}
	nbMax++;
	if(nbMax==200)
	{
		break;
	}

	} while(infoOk==false);

	return infoOk;
}

//accesseur : date (jj/mm/aaaa) et heure (hh/mm/ss.ss) du satellite
bool CGPS::getDate(date *dateT)
{
	// init du tableau de travail
	for(int i=0;i<80;i++)
	{
		m_trame[i]=0;
	}

	// recupération de la trame dans le tableau de travail
	for(int i=0;i<50;i++)
	{
		m_trame[i]=m_trameZDA[i];
	}

	bool retourDate = false;
	if(verifierChecksum())// verifie que le checksum reçu est égale au checksum calculé
	{
		if(analyserTrameZDA())// traitement des champs de la trame
		{
			dateT->j=m_dateAquisition.j;
			dateT->m=m_dateAquisition.m;
			dateT->a=m_dateAquisition.a;
			dateT->heureAcquisition=m_heureAquisition;
			retourDate=true;
		}
	}

	return retourDate;
}

//accesseur : position (longitude,latitude,altitude) du satellite
bool CGPS::getPosition(position *pos)
{

	for(int i=0;i<90;i++)
	{
		m_trame[i]=0;
	}
	for(int i=0;i<90;i++)
	{
		m_trame[i]=m_trameGGA[i];
	}

	bool retourPos = false;
	if(verifierChecksum())// verifie que le checksum reçu est égale au checksum calculé
	{
		if(analyserTrameGGA())// traitement des champs de la trame
		{
			pos->latitude=m_latitude;
			pos->longitude=m_longitude;
			pos->infoAltitude.valeurA=m_altitude.valeurA;
			pos->infoAltitude.uniteA=m_altitude.uniteA;
			retourPos=true;
		}
	}

	return retourPos;
}

//accesseur : vitesse (x.x) du satellite
bool CGPS::getVitesse(float &vit)
{
	for(int i=0;i<90;i++)
	{
		m_trame[i]=0;
	}
	for(int i=0;i<90;i++)
	{
		m_trame[i]=m_trameRMC[i];
	}

	bool retourVit = false;
	if(verifierChecksum())// verifie que le checksum reçu est égale au checksum calculé
	{
		if(analyserTrameRMC())// traitement des champs de la trame
		{
			vit=m_vitesse;
			retourVit=true;
		}
	}

	return retourVit;
}

// stocke la trame reçu par le GPS dans un tableau
bool CGPS::getTrameZDA()
{
	bool trameOk= true; // représente la validité de la trame aprés chaque test
	if (detecterChar()==true)//synchronisation sur le caractère $
	{
		int i=0;
		for(int j=1;j<50;j++)
		{
			m_trameZDA[j]=0;
		};

		m_trameZDA[0]=m_trame[0];//recupére le '$' dans le tableau de travail
		for(i=1;i<=7;i++)
		{
			m_com->read((byte&)m_trameZDA[i]);// recupère les 6 caractères (identifiant trame)+ le 1er du champs suivants
		}

		if(m_trameZDA[1]=='G'&&m_trameZDA[2]=='P'&&m_trameZDA[3]=='Z'&&m_trameZDA[4]=='D'&&m_trameZDA[5]=='A'&&m_trameZDA[6]==','&&m_trameZDA[7]!=',')//verifie qu'il s'agit d'une trame ZDA
		{
			i=8;
			do
			{
				m_com->read((byte&)m_trameZDA[i]);//rempli le tableau correspondant
				i++;
				if(i==50)//le tab fait 50 cases max donc il ne doit pas depasser
				{
					trameOk=false;
					break;
				};
			}while(m_trameZDA[i-3]!='*');//jusqu'au 2 caractères suivant le checksum
			m_trameZDA[i+1]='\0';// applique à la suite le caratère de fin de chaine
			if(m_trameZDA[17]=='V')//verifie que les données de la trame sont valides (d'après le GPS)
			{
				trameOk=false;
			}
		}else {
			trameOk= false;
		}
	}else{
		trameOk=false;
	}
	return trameOk;
}

// stocke la trame reçu par le GPS dans un tableau
bool CGPS::getTrameGGA()
{
	bool trameOk=true;
	if (detecterChar()==true)//synchronisation sur le caractère $
	{
		int i=0;
		for(int j=1;j<90;j++)
		{
			m_trameGGA[j]=0;
		};
		m_trameGGA[0]=m_trame[0];

		for(i=1;i<=7;i++)
		{
			m_com->read((byte&)m_trameGGA[i]);
		}

		if(m_trameGGA[1]=='G'&&m_trameGGA[2]=='P'&&m_trameGGA[3]=='G'&&m_trameGGA[4]=='G'&&m_trameGGA[5]=='A'&&m_trameGGA[6]==','&&m_trameGGA[7]!=',')// verifie le type de trame + que la trame contient des données
		{
			i=8;
			do
			{
				m_com->read((byte&)m_trameGGA[i]);
				if(i==90)// si au bout de 90 caractères le checksum n'est pas atteint, la trame est invalide
				{
					trameOk=false;
					break;
				};
				i++;
			} while (m_trameGGA[i-3]!='*');//verifie que la trame est fini en verifiant que le checksum est recuperer
			m_trameGGA[i+1]='\0';

		}else{
			trameOk=false;
		}
	}else{
		trameOk=false;
	}
	return trameOk;

}


// stocke la trame reçu par le GPS dans un tableau
bool CGPS::getTrameRMC()
{
	bool trameOk = true;
	if (detecterChar()==true)//synchronisation sur le caractère $
	{
		int i =0;
		for(int j=0;j<90;j++)
		{
			m_trameRMC[j]=0;
		};

		m_trameRMC[0]=m_trame[0];
		for(i=1;i<=7;i++)
		{
			m_com->read((byte&)m_trameRMC[i]);// recupère les 6 caractères (identifiant trame)+ le 1er du champs suivants
		}

		if(m_trameRMC[1]=='G'&&m_trameRMC[2]=='P'&&m_trameRMC[3]=='R'&&m_trameRMC[4]=='M'&&m_trameRMC[5]=='C'&&m_trameRMC[6]==','&&m_trameRMC[7]!=',')//gp ou gn pour le glonass ||m_trame[2]=='N'
		{
			i=8;
			do
			{
				m_com->read((byte&)m_trameRMC[i]);
				i++;
				if(i==90)// si au bout de 90 caractères le checksum n'est pas atteint, la trame est invalide
				{
					trameOk=false;
					break;
				};
			}while(m_trameRMC[i-3]!='*');
			m_trameRMC[i+1]='\0';
			trameOk=true;
		}else {
			trameOk= false;
		}
	}else{
		trameOk=false;
	}
	return trameOk;
}


bool CGPS::analyserTrameZDA()
{
	char tempo[10]={0};
	int i=0;

	// Acquisition Heure

	//heure
	tempo[0]=m_trame[7];
	tempo[1]=m_trame[8];
	tempo[2]='\0'; //securité pour eviter que strtol ne depasse cette case du tableau
	m_heureAquisition.h=strtol(tempo,NULL,10);
	//minute
	tempo[0]=m_trame[9];
	tempo[1]=m_trame[10];
	tempo[2]='\0';
	m_heureAquisition.mn=strtol(tempo,NULL,10);
	//seconde
	for(i=0;i<5;i++)
	{
		tempo[i]=m_trame[i+11];
	};

	tempo[i]='\0';
	m_heureAquisition.s=atof(tempo);//pas de conv pour les secondes de l'acquisition trame

	tempo[10]={0};

	// Acquisition Date

	//Jour
	tempo[0]=m_trame[17];
	tempo[1]=m_trame[18];
	tempo[3]='\0';
	m_dateAquisition.j=strtol(tempo,NULL,10);
	//Mois
	tempo[0]=m_trame[20];
	tempo[1]=m_trame[21];
	tempo[2]='\0';
	m_dateAquisition.m=strtol(tempo,NULL,10);
	//Année
	tempo[0]=m_trame[23];
	tempo[1]=m_trame[24];
	tempo[2]=m_trame[25];
	tempo[3]=m_trame[26];
	tempo[4]='\0';
	m_dateAquisition.a=strtol(tempo,NULL,10);

	return true;
}


bool CGPS::analyserTrameGGA()
{
	char tempo[10]={0};
	int i=0;
	int nbChar=0;

	// Acquisition Latitude

	//Degré
	tempo[0]=m_trame[17];
	tempo[1]=m_trame[18];
	tempo[2]='\0';
	m_latitude.degres=atoi(tempo);
	//Minute
	tempo[0]=m_trame[19];
	tempo[1]=m_trame[20];
	tempo[2]='\0';
	m_latitude.mn=atoi(tempo);
	//Seconde
	nbChar=compterChar(3);// recupére le nombre de caractères constituant les secondes
	for (i=0;i<nbChar-2;i++)
	{
		tempo[i]=m_trame[i+22];
	}
	tempo[i]='\0';
	m_latitude.s=atof(tempo);
	m_latitude.s=(m_latitude.s*60)/10000;//convertion des secondes
	//Indicateur latitude
	m_latitude.indicateur=m_trame[nbChar+18];// 18+nbChar=emplacement de l'indicateur

	// Acquisition Longitude

	//Degré
	tempo[0]=m_trame[nbChar+20];
	tempo[1]=m_trame[nbChar+21];
	tempo[2]=m_trame[nbChar+22];
	tempo[3]='\0';
	m_longitude.degres=atoi(tempo);
	//Minute
	tempo[0]=m_trame[nbChar+23];
	tempo[1]=m_trame[nbChar+24];
	tempo[2]='\0';
	m_longitude.mn=atoi(tempo);
	//Seconde
	int nbChar2=0;
	nbChar2=compterChar(5);
	for (i=0;i<nbChar2-6;i++)
	{
		tempo[i]=m_trame[nbChar+26+i];
	}
	tempo[i]='\0';
	m_longitude.s=atof(tempo);
	m_longitude.s=(m_longitude.s*60)/10000;//convertion des secondes
	//Indicateur longitude
	nbChar=17+nbChar2+nbChar+3;
	m_longitude.indicateur=m_trame[nbChar+1];

	// Altitude

	//ecrase le tableau à 0 pour eviter les erreurs de atof
	for(i=0;i<=10;i++)
	{
		tempo[i]=0;
	};
	tempo[9]='\0';

	char* token=NULL;
	token = strtok (m_trame,",");
	int emplacement=0;
	while (token != NULL)
	{
		if(emplacement==9)// emplacement-1 de l'altitude dans la trame GGA
		{
			m_altitude.valeurA=atof(token);
			break;
		}
	token = strtok (NULL,",");
	emplacement++;
	}
	m_altitude.uniteA='M';

	return true;
}

bool CGPS::analyserTrameRMC()
{
	char* token=NULL;
	int emplacement=0;
	token = strtok (m_trame,",");
	while (token != NULL)
	{
	if(emplacement==7)// emplacement-1 de la vitesse dans la trame RMC
	{
		m_vitesse=atof(token);
		break;
	}
	token = strtok (NULL,",");
	emplacement++;
	}
	return true;
};


bool CGPS::verifierChecksum()
{
	bool retour=false;
	int i=0;
	byte checksumCalcule=0;
	byte checksumRecu=0;

	int taille=strlen((const char *)m_trame);

	//le checksum reçu est stocker dans un tableau
	char sChecksumRecu[3]={0};
	sChecksumRecu[0]=m_trame[taille-2];
	sChecksumRecu[1]=m_trame[taille-1];
	sChecksumRecu[2]='\0';
	checksumRecu=strtol(sChecksumRecu,NULL,16);

	//comparaison du checksum reçu de la trame avec celui calculé
	for(i=1;i < taille-3;i++)
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
