
#include "Script.h"
#include "Fipex.h"

#include <string.h>

CScript::CScript(const char *standardCheckOut,int taille,typeScript type)
{
	m_position=0;
	m_taille=taille;
	m_type=type;
	 m_bCommande= new char[150];
	 m_posDebutCommande= new char[150];
	 for(int i=0;i<taille;i++)
	 {
		 m_posDebutCommande[i]=standardCheckOut[i];
		 m_bCommande[i]=standardCheckOut[i];
	 }
}

CScript::~CScript()
{

}

bool CScript::getCommande(uint8_t &idCommand,uint8_t data[], uint8_t &taille, uint8_t delay[2])
{
	bool retour=false;
	if(m_type==binaire)
		retour=getCommandeBinaire(idCommand,data,taille,delay);
	else
		retour=getCommandeASCII(idCommand,data,taille,delay);
	return retour;
}

bool  CScript::getCommandeBinaire(uint8_t &idCommand,uint8_t data[], uint8_t &taille, uint8_t delay[2])
{

	bool retour=false;
		//int debut=0;
		//m_posDebutCommande=strchr(m_posDebutCommande,0x7E);
		while (m_posDebutCommande[m_position]!=0x7E && m_position<m_taille)
		{
			m_position++;
		}

		if(m_posDebutCommande[m_position]==0x7E)
		{
			idCommand=m_posDebutCommande[++m_position];
			taille=m_posDebutCommande[++m_position];
			for (int k=0;k<taille;k++)
			{
				m_position=m_position+k;
				data[k]=m_posDebutCommande[++m_position];
			}
			m_position+=taille;
			//uint8_t checksum=m_posDebutCommande[++m_position];
			delay[0]=m_posDebutCommande[++m_position];
			delay[1]=m_posDebutCommande[++m_position];
			m_position++;
			retour=true;
		}
		else
		{
			retour=false;
		}
	return retour;
}


bool CScript::getCommandeASCII(uint8_t &commandId, uint8_t data[], uint8_t &taille, uint8_t delay[2])
{
	(void)commandId;
	(void)data;
	(void)taille;
	(void)delay;

	bool retour=false;
	/*uint8_t test=0;
	int k=0,m=0;
	char tabId[10]={0},on[9]={0},off[10]={0},end[10]={0},ping[7]={0},init[7]={0},id[5]={0},rsp[6]={0},sp[5]={0},hk[5]={0},dp[5]={0},stdby[8]={0},sc[5]={0},sm[5]={0},cal[6]={0};
	strcpy(on,"OBC_SU_ON");strcpy(off,"OBC_SU_OFF");strcpy(end,"OBC_SU_END");strcpy(ping,"SU_PING");strcpy(init,"SU_INIT");strcpy(id,"SU_ID");strcpy(rsp,"SU_RSP");strcpy(sp,"SU_SP");strcpy(hk,"SU_HK");strcpy(dp,"SU_dp");
	strcpy(stdby,"SU_STDBY");strcpy(sc,"SU_SC");strcpy(sm,"SU_SM");strcpy(cal,"SU_CAL");

	if(m_isOpened)
	{
		//récupérer le commandId
		do {
			test=m_script[m_numScript][i];
			tabId[k]=m_script[m_numScript][i];
			i++;
			k++;
		} while (m_script[m_numScript][i]!=' ');
		if(strcmp(tabId,on)==0)
		{
			commandId=0x0F;
		}
		if(strcmp(tabId,off)==0)
		{
			commandId=0xF0;
		}
		if(strcmp(tabId,end)==0)
		{
			commandId=0xFF;
		}
		if(strcmp(tabId,ping)==0)
		{
			commandId=0x00;
		}
		if(strcmp(tabId,init)==0)
		{
			commandId=0x01;
		}
		if(strcmp(tabId,id)==0)
		{
			commandId=0x04;
		}
		if(strcmp(tabId,rsp)==0)
		{
			commandId=0x10;
		}
		if(strcmp(tabId,sp)==0)
		{
			commandId=0x11;
		}
		if(strcmp(tabId,hk)==0)
		{
			commandId=0x20;
		}
		if(strcmp(tabId,dp)==0)
		{
			commandId=0x21;
		}
		if(strcmp(tabId,stdby)==0)
		{
			commandId=0x0A;
		}
		if(strcmp(tabId,sc)==0)
		{
			commandId=0x0B;
		}
		if(strcmp(tabId,sm)==0)
		{
			commandId=0x0C;
		}
		if(strcmp(tabId,cal)==0)
		{
			commandId=0x33;
		}
	}
		i++;

		//récupérer les data
		if(commandId==SU_SP||commandId==SU_CAL)
		{
			char param[4]={0};

			do
			{
				if(m_script[m_numScript][i]==' ')
				{
					data[taille]=temp;
					taille++;
				}
				data=(uint8_t)atol("0x02",null,16);
				if(m_script[m_numScript][i]==' ')
				{
					for(int k=0;k<3;k++)
					{
						param[k]=m_script[m_numScript][i+1];
					}
					i++;
				}
				i++;
			} while (m_script[m_numScript][i]!='@');
		}

		//récupérer le delais
		if(m_script[m_numScript][i]=='@')
		{
			char delais[4]={0};
			char delaisSecondes=0,delais1=0,delais2=0,delais3=0,delais4=0;
			delais[0]=m_script[m_numScript][i+1];
			delais[1]=m_script[m_numScript][i+2];
			delais[2]=m_script[m_numScript][i+4];
			delais[3]=m_script[m_numScript][i+5];
			delais1=delais[0]*600;
			delais2=delais[1]*60;
			delais3=delais[2]*10;
			delais4=delais[3];
			delaisSecondes=delais1+delais2+delais3+delais4;
		}
		while(m_script[m_numScript][i]!='\n')
		{
			i++;
		}
		retour =true;
		test=m_script[m_numScript][i];
		i+=2;
		test=m_script[m_numScript][i];*/
	return retour;
}


