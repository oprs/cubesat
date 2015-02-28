
	void putString(char[] adress, char* character, int length); l'adresse est en octet
	void readString(char[] adress, char* character,int length);
	void getGlobalVariables(*char values,int length); // a voir l'implémentation exacte
	void erase(char[] from,char[] to)


Fonctions utiles :
char* fromInt(long int X)
{
	char[] c = [0,0,0];
	c[2]=X%256;
	c[1]=((X-C)/256)%256;
	c[0] = ((X-C)/256-b)%256; (erreur si a>255)
	return c;
}
long int toInt(char[] c)
{
	return a*256*256+b*256+c;
}
char readChar(char[] adress)
{
	char* c = NULL;
	readString(adress,c,1);
	return *c;
}
void putChar(char[] adress,char c)
{
	putString(adress,&c,1);
}


Prototypes des fonctions crées pour la gestion de mémoire :
	void init_memory();

	void put_new_Data(char* string, int length);
	void read_Data(char* target,int* target_length);
	void erase_Data();

	char get_arg(int code); //retourne la code-ieme variable globale : Table à définir
	void set_arg(int code, char value);



Code des fonctions (C99) :

#define MEMLENGTH 16000000
#define NBVARIABLES 5

	void init_memory()
	{
		char* settings = NULL;
		int i = 0;
		char[] pointeur = [0,0,0];
		getGlobalVariables(settings,NBVARIABLES);
		putString(3,settings,NBVARIABLES); // Ecriture des variables globales
		putString([0,0,0],fromInt(NBVARIABLES+3),3); //Ecriture du pointeur
	}

	char get_arg(int code) //code de 0 à NBVARIABLES -1
	{
		return readChar(6*NBSECTOR + code);
	}
	void set_arg(int code, char value)
	{
		putChar(6*NBSECTOR + code, value);
	}

	void put_new_Data(char* string, int length)
	{
		char* adress = NULL;
		readString([0,0,0],adress,3);
		putString(adress,string,length);
		putString([0,0,0],fromInt(toInt(adress)+length)),3);
	}
	void read_Data(char[] adress, char* target,int length, int* memoryRead) // Attention, il va falloir gérer le fait que la mémoire soit déjà lue ou pas. target est une adresse relative.
	{
		char* d_adress = NULL;
		readString([0,0,0],d_adress,3);
		if(toInt(adress)+toInt(d_adress)+length<=MEMLENGTH)
		{
			readString(fromInt(toInt(adress)+toInt(d_adress)),target,length);
			*memoryRead = false;
		}
		else
		{
			readString(fromInt(toInt(adress)+toInt(d_adress)),target,MEMLENGTH-toInt(adress)-toInt(d_adress)); // on tronque
			*memoryRead = true; //on averti que la sortie est peut être tronquée
		}

	}
	void erase_Data()
	{
		erase(fromInt(NBVARIABLES+3),[255,255,255]);
	}
