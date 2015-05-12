#include "Telecommande.h"
#include "device/UART.h"
#include <cstring>
#include "system/qb50.h"

using namespace std;
using namespace qb50;

Telecommande::~Telecommande()
{
	//dtor
}

Telecommande::Telecommande()
{
	//We have to develop here the algorithm that will take the output of the TC module and change it into and instance of
	//the Telecommande class.
	//Initialisation des variables de la classe
	int i;
	buf = 0;
	for(i=0; i < 2;i++);
    {
        typeCmd[i] = '0';
        fstParameter[i] = '0';
        scdParameter[i] = '0';
    }
    for(i=0;i<8;i++)
    {
        if(i<4)
        {
            sender[i] = '0';
            receiver[i] = '0';
        }
        else
        {
            receiver[i] = '0';
        }

    }
}


//Read the value at the AX25 exit given a pointing space
void Telecommande::read(char* x)
{
    buf = UART6.read(x,64);
    adresseReference = x;
}

//Transform the serial value into an instance of Telecommande.
void Telecommande::charToTelecommande()
{
    int phase = 0;
    int bg = 0;
    char messageAX25;
    int i;
    int j = 0;
    int k = 0;

	for(i = 0; i < buf - 1; i++)
	{
	    messageAX25 = *(adresseReference + i);
		switch(phase)
		{
			case 0:
				if (messageAX25 == '>')
				{
					phase = 1;
					j = 0;
				}
				else
				{
					sender[j] = messageAX25;
					j++;
				}
				break;

			case 1:
				if (messageAX25 == ':')
				{
					phase = 2;
					j = 0;
				}
				else
				{
					receiver[j] = messageAX25;
					j++;
				}
				break;

			case 2:
				if(messageAX25 == 'C')
				{
				    phase = 3;
				}
				else
				{
            		typeCmd[k] = messageAX25;
					k++;
				}
				break;

			case 3:
				if(messageAX25 == ',')
				{
					phase = 4;
					j = 0;
				}
				else
				{
					fstParameter[j] = messageAX25;
					j++;
				}
				break;

			case 4:
				scdParameter[j] = messageAX25;
				j++;
				bg = 0;
				break;

			default:
				break;

		}

		if(bg == 1)
		{
		    for(j = 0; j < 8;j++)
            {
                scdParameter[j] = '0';
            }
		}

		//Il faut encore créer un outil de vérification des données. En gros il s'agit de vérifier que toutes les variables
		//de l'instance fonctionnent.
		//Envoyer ACK si c'est bon ou NACK si ça ne pose pas de problème.
	}
}

//Vérification de l'envoyeur
bool Telecommande::checkSender()
{
    return (sender[0] == 'A' and sender[1] == 'P' and sender[2] == 'T' and sender[3] == '3' and sender[4] == '1' and sender[5] == '0');
}

//Vérification du récepteur (que le message nous est bien adressé)
bool Telecommande::checkReceiver()
{
    return (receiver[0] == 'O' and receiver[1] == 'N' and receiver[2] == '0' and receiver[3] == 'F' and receiver[4] == 'R' and receiver[1] == '5');
}

//Verifier que le nombre de paramètres passés à la commande est bon
bool Telecommande::checkCmd()
{
	if (typeCmd[0] == '3' or typeCmd[0] == '6' or (typeCmd[0] == '9' or (typeCmd[1] == '1' and (typeCmd[0] == '1' or typeCmd[0] == '0' or typeCmd[0] == '2'))))
	{
		return (scdParameter[0] == '0' and scdParameter[1] == '0' and scdParameter[2] == '0' and fstParameter != 0);
	}
	else if(not(typeCmd[0] == '0' and typeCmd[1] != '0' and typeCmd[2] == '0') and typeCmd[0] == '7')
	{
		return (not(scdParameter[0] == '0' and scdParameter[1] == '0' and scdParameter[2] == '0') and fstParameter != 0);
	}
	else if(typeCmd[0] == '8' and typeCmd[1] == '0')
	{
		return (scdParameter[0] == '0' and scdParameter[1] == '0' and scdParameter[2] == '0' and fstParameter[0] == '0' and fstParameter[1] == '0');
	}
	else
	{
		return false;
	}
}

bool Telecommande::checkWorth()
{
	return checkCmd() and checkReceiver() and checkReceiver();
}

int Telecommande::giveReceiveTime()
{
    return receiveTime;
}


char* Telecommande::getSender()
{
    return sender;
}

char* Telecommande::getReceiver()
{
    return receiver;
}

char* Telecommande::getTypeCmd()
{
    return typeCmd;
}

char* Telecommande::getFstParameter()
{
    return fstParameter;
}

char* Telecommande::getScdParameter()
{
    return scdParameter;
}
