#include "Telecommande.h"

Telecommande::Telecommande()
{
	//ctor
}

Telecommande::~Telecommande()
{
	//dtor
}

Telecommande::Telecommande(string messageAX25)
{
	//We have to develop here the algorithm that will take the output of the TC module and change it into and instance of
	//the Telecommande class.
	size = messageAX25.size();

	//Initialisation des variables de la classe
	sender = "";
	receiver = "";
	typeCmd = 0;
	fstParameter = 0;
	scdParameter = 0;
	phase = 0

	//Lecture du string et remplissage des différentes variables au fur et à mesure de la lecture
	for(i = 0; i < size - 1; i++)
	{
		switch(phase)
		{
			case 0:
				if (messageAX25[i] == ">")
				{
					phase = 1
				}
				else
				{
					sender = sender + messageAX25[i];
				}
				break;

			case 1:
				if (messageAX25[i] == ":")
				{
					phase = 2
				}
				else
				{
					receiver = receiver + messageAX25[i];
				}
				break;

			case 2:
				if(messageAX25[i] == "C")
				{
				}
				else
				{
					typeCmd = int(messageAX25[i]);
					phase = 3;
				}
				break;

			case 3:
				if(messageAX25[i] == ',')
				{
					phase = 4;
				}
				else
				{
					fstParameter = fstParameter + messageAX25[i];
				}
				break;

			case 4:
				sndParameter = sndParameter + messageAX25[i];
				break;

			default:
				break;

		}

		//Il faut encore créer un outil de vérification des données. En gros il s'agit de vérifier que toutes les variables
		//de l'instance fonctionnent.
		//Envoyer ACK si c'est bon ou NACK si ça ne pose pas de problème.
	}
}

bool Telecommande::checkReceiver()
{
	return (receiver == "APT310");
}
