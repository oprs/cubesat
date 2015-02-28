#include "Script.h"
#include"Fipex.h"
#include <string.h>

CScript::CScript()
{
	m_isOpened=false;
	strcpy(m_script[0],"OBC_SU_ON @01:00\n\rSU_SC @01:00\n\rSU_SP 0x04 0x01 00 00 @NOW\n\rSU_SP 0x05 0x10 0a00 @NOW\n\rSU_SP 0x02 0xc8 00 00 @NOW\n\rSU_SM @05:00\n\rSU_HK @NOW\n\rSU_DP @NOW\n\rOBC_SU_OFF @NOW\n\rOBC_SU_END");
	strcpy(m_script[1],"SU_PING @NOW\n\rSU_SP 0x04 0x00 0x01 @NOW\n\rSU_SP 0x06 0x27 0a0f @NOW\n\rSU_SM @05:00\n\rSU_HK @NOW\n\rOBC_SU_OFF @NOW\n\rOBC_SU_END");

}

CScript::~CScript()
{

}

bool CScript::open(byte numScript)
{
	bool retour=false;
	m_numScript=numScript;
	m_isOpened=true;
	return retour;
}

bool CScript::getCommande(int &i,int &j, byte &commandId, byte data[], byte &taille, byte delay[2])
{
	bool retour=false;
	byte test=0;
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
		for(int l=0;l<9;l++)
		{
			if(tabId[l]==on[l])
			{
				m++;
			}
			if(m==9)
			{
				commandId=0x0F;
			}
		}
		m=0;
		for(int l=0;l<10;l++)
		{
			if(tabId[l]==off[l])
			{
				m++;
			}
			if(m==10)
			{
				commandId=0xF0;
			}
		}
		m=0;
		for(int l=0;l<10;l++)
		{
			if(tabId[l]==end[l])
			{
				m++;
			}
			if(m==10)
			{
				commandId=0xFF;
			}
		}
		m=0;
		for(int l=0;l<7;l++)
		{
			if(tabId[l]==ping[l])
			{
				m++;
			}
			if(m==7)
			{
				commandId=0x00;
			}
		}
		m=0;
		for(int l=0;l<7;l++)
		{
			if(tabId[l]==init[l])
			{
				m++;
			}
			if(m==7)
			{
				commandId=0x01;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==id[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x04;
			}
		}
		m=0;
		for(int l=0;l<6;l++)
		{
			if(tabId[l]==rsp[l])
			{
				m++;
			}
			if(m==6)
			{
				commandId=0x10;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==sp[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x11;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==hk[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x20;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==dp[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x21;
			}
		}
		m=0;
		for(int l=0;l<8;l++)
		{
			if(tabId[l]==stdby[l])
			{
				m++;
			}
			if(m==8)
			{
				commandId=0x0A;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==sc[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x0B;
			}
		}
		m=0;
		for(int l=0;l<5;l++)
		{
			if(tabId[l]==sm[l])
			{
				m++;
			}
			if(m==5)
			{
				commandId=0x0C;
			}
		}
		m=0;
		for(int l=0;l<6;l++)
		{
			if(tabId[l]==cal[l])
			{
				m++;
			}
			if(m==6)
			{
				commandId=0x33;
			}
		}
	}
		i++;

		//récupérer les data
		if(commandId==SU_SP||commandId==SU_CAL)
		{
			char param[4]={0};
			int paramInt=0;
			int n=0;
			do {
				test=m_script[m_numScript][i];
				if(m_script[m_numScript][i]==' ')
				{
					for(int o=0;o<4;o++)
					{
						data[taille]+=(byte)param[o];
					}
					taille++;
					i++;
					n=0;
				}
				else
				{
					param[n]=m_script[m_numScript][i];
					i++;
					n++;
				}
			} while (m_script[m_numScript][i]!='@');

		}

		//récupérer le delais
		if(m_script[m_numScript][i]=='@')
		{
			do {
				i++;
				test=m_script[m_numScript][i];
				if (m_script[m_numScript][i]==':')
				{
					j++;
				}
				delay[j]+=m_script[m_numScript][i];
			} while (m_script[m_numScript][i]!='\n');
		}
		retour =true;
		i+=2;
	return retour;
}

bool CScript::close()
{

}
