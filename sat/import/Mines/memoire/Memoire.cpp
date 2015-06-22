class Memoire {
	// Deux pointeurs READ et WRITE seront necessaires.
		// WRITE pointera sur la zone mémoire ou doit être écrite la valeur la plus récente
		// READ pointera sur le début de la plus ancienne Data à lire
	// READ sera modifié dans put et read 
	// WRITE sera modifié dans put uniquement
	// Si WRITE pousse READ alors les données sont perdues
	// L'opération de lecture s'arrête quand READ pousse WRITE

	private void put_new_Data(uint8_t string[], int length);
	private void read_Data(uint8_t adress[3], uint8_t target[], int length);

	public void init_memory();
	public void erase_Data();

	public uint8_t get_arg(int code); //retourne la code-ieme variable globale : Table à définir
	public void set_arg(int code, uint8_t value);

	/////////////////////////////////////////////// Les fonctions ci dessus sont supposées codées

	void operator<<( Memoire const& memoire, Data data )
	{
		memoire.put_new_Data(data.toBinary(),data.toBinaryLength());
	}
	void operator>>( Memoire const& memoire, Data data )
	{
		// A définir selon des modalités spécifiques (question de la taille).
	}
};
class Data {
	uint_8 identifiant;
	Data() {
		identifiant = 0;
	}
	static Data fromBinary(uint_8* data, int length) {
		if(data[0] == 0)
			return new Data();
		else if(data[0] == 1)
		{
			return new Data_Wod(to_uint_32(data+1),data[4],to_uint_64(data+6),to_uint_64(data+14),to_uint_64(data+22),to_uint_16(data+30));
		}
	}
	public virtual uint_8* toBinary() {
		uint_8[] data = new uint_8[1];
		data[0] = identifiant;
		return data;
	}
};
	
class Data_Wod : Data {
	// taille = 31+ID
	uint_32 timestamp; 
	uint_8 mode;
	uint_64 ADC_1;
	uint_64 ADC_2;
	uint_64 ADC_3;
	uint_16 ADC_GHI;
	
	Data_Wod(uint_32 timestamp,	uint_8 mode, uint_64 ADC_1,	uint_64 ADC_2, uint_64 ADC_3, uint_16 ADC_GHI) {
		identifiant = 1;
		this.timestamp = timestamp;
		this.mode = mode;
		this.ADC_1 = ADC_1;
		this.ADC_2 = ADC_2;
		this.ADC_3 = ADC_3;
		this.ADC_GHI = ADC_GHI;
	}

	public override uint_8* toBinary() {
		// codé dans l'ordre d'apparition des types produits dans la classe
		uint_8[] data = new uint_8[32];
		data[0] = identifiant;
		uint_8[] time = from_uint_32(timestamp);
		uint_8[] ADC1 = from_uint_64(ADC_1);
		uint_8[] ADC2 = from_uint_64(ADC_2);
		uint_8[] ADC3 = from_uint_64(ADC_3);
		uint_8[] ADCGHI = from_uint_16(ADC_GHI);
		for(int i = 0;i<3;i++)
			data[1+i] = time[i];
		data[5] = mode;
		for(int i = 0;i<8;i++)
			data[6+i] = ADC1[i];
		for(int i = 0;i<8;i++)
			data[14+i] = ADC2[i];
		for(int i = 0;i<8;i++)
			data[22+i] = ADC3[i];
		for(int i = 0;i<2;i++)
			data[30+i] = ADC_GHI[i];
		return data;
	}
};


class Data_GPS : Data {
	Data_Wod() {
		identifiant = 2;
	}
	//timestamp
	//champs codés selon la trame désignée page 44 du dossier technique du calculateur
	//A voir comment on stocke concrètement les variables en binaire
	public override uint_8* toBinary() {
		return null;
	}
};
class Data_Sci : Data {
	// La taille vaut LEN + 28 + ID octets
	uint_8 RSP_ID;
	uint_8 LEN;
	uint_8 SEQ_CNT;
	uint_8* DATA;
	uint_8 XOR;
	uint_32 TIME;
	uint_16 Q1;
	uint_16 Q2;
	uint_16 Q3;
	uint_16 Q4;
	uint_16 Xdot;
	uint_16 Ydot;
	uint_16 Zdot;

	Data_Wod(uint_8 RSP_ID,	uint_8 LEN,	uint_8 SEQ_CNT,	uint_8* DATA, uint_8 XOR, uint_34 TIME, uint_16 Q1, uint_16 Q2, uint_16 Q3, uint_16 Q4, uint_16 Xdot, uint_16 Ydot, uint_16 Zdot) {
		identifiant = 3;
		this.RSP_ID = RSP_ID;
		this.LEN = LEN;
		this.SEQ_CNT = SEQ_CNT;
		this.DATA = DATA;
		this.XOR = XOR;
		this.TIME = TIME;
		this.Q1 = Q1;
		this.Q2 = Q2;
		this.Q3 = Q3;
		this.Q4 = Q4;
		this.Xdot = Xdot;
		this.Ydot = Ydot;
		this.Zdot = Zdot;
	}

	override uint_8* toBinary() {
		return null;
	}
};


uint_8* from_uint_16(uint_16 u) {
	uint_8[] result = new uint_8[2];
	result[0] = u%(256);
	result[1] = (u-result[0])/256;
	return result;
}
uint_8* from_uint_32(uint_32 u) {
	uint_8[] result = new uint_8[4];
	uint_32 temp = u;
	result[0] = u%256;
	for(int i = 0; i<3;i++)
	{
		temp = (temp - result[i])/256;
		result[i+1] = temp%256;
	}
}
uint_8* from_uint_64(uint_64 u) {
	uint_8[] result = new uint_8[8];
	uint_64 temp = u;
	result[0] = u%256;
	for(int i = 0; i<7;i++)
	{
		temp = (temp - result[i])/256;
		result[i+1] = temp%256;
	}
}
uint_16 to_uint_16(uint_8* u)
{
	return 256*u[1] + u[0];
}
uint_32 to_uint_32(uint_8* u)
{
	uint_32 temp = u[3];
	for(int i =2;i>=0;i--)
	{
		temp = 256*temp + u[i];
	}
	return temp;
}
uint_64 to_uint_64(uint_8* u)
{
	uint_64 temp = u[7];
	for(int i =6;i>=0;i--)
	{
		temp = 256*temp + u[i];
	}
	return temp;
}
