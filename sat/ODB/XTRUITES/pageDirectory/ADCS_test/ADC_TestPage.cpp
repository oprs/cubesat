/*!
 * @file ADC_TestPage.cpp
 * @brief Page de test dédié aux ADC
 * @author Jérôme skoda <jerome.skoda@hotmail.fr>
 * @version 0.3
 * @date 28 mai 2015
 *
 * Page de test pour afficher toutes les valeurs des canaux ADC (MAX111x).
 *
 */


#include "ADC_TestPage.h"


using namespace qb50;
using namespace std;


uint8_t XTRUITESADC_TestPage::currentADC_read=2;


/*!
 *  @brief Constructeur
 *
 *  Constructeur de la classe fieldADC
 *
 *  @param[in] nameVal          Nom associé au canal.
 *  @param[in] converterVal     Fonction de conversion.
 *  @param[in] unitVal          Unité du canal.
 */
fieldADC::fieldADC(std::string nameVal, std::function<float(uint16_t)> converterVal, std::string unitVal)
{
    name= nameVal;
    converter= converterVal;
    unit= unitVal;
}


/*!
 *  @brief Ajout d'un morceau
 *
 *  Methode qui permet d'ajouter un morceau a liste de
 *  lecture
 *
 *  @param strSong : le morceau a ajouter
 *  @return true si morceau deja present dans la liste,
 *  false sinon
 */
std::string fieldADC::convertValue(uint16_t value)
{
    stringstream ss;
    ss << converter(value);
    return (ss.str() + " " + unit);
}



void qb50::ADCPageThreadUpdate( Thread *self )
{
    delay( 500 );

    int valueNum=0;
	uint8_t i = 0;
	char lineData[41];
	string text;
	MAX111x::ConvResp conv;

    const MAX111x::Channel i2ch[8] = {
        MAX111x::CH0, MAX111x::CH1, MAX111x::CH2, MAX111x::CH3,
		MAX111x::CH4, MAX111x::CH5, MAX111x::CH6, MAX111x::CH7
    };

    MAX111x i2ADC[4] = {
        ADC_Power_1, ADC_Power_2, ADC_ODB, ADC_FiPEX
    };

    fieldADC* converterADC[4][8]=
    {
        {
            /** ADC_Power_1 **/
            //              Name            Converter                                                   Unit
            new fieldADC("V4",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I4" ,         [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T4",          [&](uint16_t value) -> float { return value*0.008; },         "°C " ),
            new fieldADC("V1",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I1",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T1",          [&](uint16_t value) -> float { return value*0.008; },         "°C " ),
            new fieldADC("T_bat",       [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("V_bat",       [&](uint16_t value) -> float { return value*0.008; },         "V   " )
        },{
            /** ADC_Power_2 **/
            //              Name            Converter                                                   Unit
            new fieldADC("V2",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T2",          [&](uint16_t value) -> float { return value*0.008; },         "°C " ),
            new fieldADC("I2",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("V3",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T3",          [&](uint16_t value) -> float { return value*0.008; },         "°C " ),
            new fieldADC("I3",          [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I_SURT",      [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("CH7",         [&](uint16_t value) -> float { return value*0.008; },         "V   " )
        },{
            /** ADC_ODB **/
            //              Name            Converter                                                   Unit
            new fieldADC("I_ADCS",      [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T_ARM" ,      [&](uint16_t value) -> float { return value*0.008; },         "°C " ),
            new fieldADC("I_RX",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("RSSI",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I_TX",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("P_TX",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("P_PA",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("T_PA",        [&](uint16_t value) -> float { return value*0.008; },         "°C " )
        },{
            /** ADC_FiPEX **/
            //              Name            Converter                                                   Unit
            new fieldADC("I_ADCS",      [&](uint16_t value) -> float { return value*0.008; },         "A   " ),
            new fieldADC("I_GPS" ,      [&](uint16_t value) -> float { return value*0.008; },         "A   " ),
            new fieldADC("CH2_CSS",     [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I_3,3V",      [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("V_3,3V",      [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("I_5V",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("V_5V",        [&](uint16_t value) -> float { return value*0.008; },         "V   " ),
            new fieldADC("SU_TH_Go",    [&](uint16_t value) -> float { return value*0.008; },         "V   " )
        }
    };


    XTRUITESTextBlock* ADCmenu[4];
        ADCmenu[0] = new XTRUITESTextBlock();
        ADCmenu[0]->setLocationY(2).setLocationX( 2).setHeight(1).setWidth(10).setText("Power 1").display();

        ADCmenu[1] = new XTRUITESTextBlock();
        ADCmenu[1]->setLocationY(2).setLocationX(22).setHeight(1).setWidth(10).setText("Power 2").display();

        ADCmenu[2] = new XTRUITESTextBlock();
        ADCmenu[2]->setLocationY(2).setLocationX(42).setHeight(1).setWidth(10).setText("ODB").display();

        ADCmenu[3] = new XTRUITESTextBlock();
        ADCmenu[3]->setLocationY(2).setLocationX(62).setHeight(1).setWidth(10).setText("FiPEX").display();


    uint8_t currentADC= XTRUITESADC_TestPage::currentADC_read;


    // Display selected current ADC
    ADCmenu[currentADC]->reversesColors().display();
    escapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);
    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);

    while(1)
    {
        if(currentADC != XTRUITESADC_TestPage::currentADC_read)
        {
            ADCmenu[currentADC]->reversesColors().display();
            currentADC= XTRUITESADC_TestPage::currentADC_read;
            ADCmenu[currentADC]->reversesColors().display();
            escapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);
            escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);
        }

		for (uint8_t channel = 0; channel < 8; channel++)
		{


			i2ADC[XTRUITESADC_TestPage::currentADC_read].conv(i2ch[channel], &conv);

            valueNum = ((int)(conv.rb3 << 2) | (int)(conv.rb4 >> 6));

			escapeSequences::moveCursor(10, 10 + channel);
			escapeSequences::write("%8s", FIELD_CURRENT_ADC->name.c_str());


			escapeSequences::moveCursor(21, 10 + channel);
            escapeSequences::write("%02X %02X %02X %02X", conv.rb1, conv.rb2, conv.rb3, conv.rb4);

			escapeSequences::moveCursor(35, 10 + channel);
            escapeSequences::write("%4d", valueNum);

			escapeSequences::moveCursor(42, 10 + channel);
            escapeSequences::write("%20s", FIELD_CURRENT_ADC->convertValue(valueNum).c_str() );

            escapeSequences::moveCursorHome();
            escapeSequences::write("\n");
		}
		delay( 100 );
    }
}

// Write location
XTRUITESADC_TestPage::XTRUITESADC_TestPage(XTRUITES& _XTRUITESInterfaceVal)
    : XTRUITESPage(_XTRUITESInterfaceVal, "ADCS") { }


void XTRUITESADC_TestPage::load(void)
{
    getInterface().clearContent();
    getInterface().displayLocation();

	XTRUITESTextBlock *titre = new XTRUITESTextBlock();
	titre->setLocationX(2).setLocationY(4)
		.setWidth(20).setHeight(15)
		.setText("Valeur des ADCS\r\n").display();



 escapeSequences::moveCursor(8,7);
    escapeSequences::write(      "┌──────────┬─────────────┬──────┬──────────────────────┐");
    escapeSequences::moveCursor(8,8);
    escapeSequences::write(      "│   NAME   │     HEX     │  VAL │                      │");
    escapeSequences::moveCursor(2,9);
    escapeSequences::write("┌─────┼──────────┼─────────────┼──────┼──────────────────────┤");

    for (uint8_t channel = 0; channel < 8; channel++)
    {
        escapeSequences::moveCursor(2,10+channel);
        escapeSequences::write("│ CH%01d │          │ 00 00 00 00 │ 0000 │  ..................  │", channel);
    }
    escapeSequences::moveCursor(2,18);
    escapeSequences::write("└─────┴──────────┴─────────────┴──────┴──────────────────────┘");


    updateADCSVal= createThread("XTRUITESADC_TestPage", ADCPageThreadUpdate);
}


void XTRUITESADC_TestPage::unload(void)
{
    updateADCSVal->suspend();
}

uint8_t XTRUITESADC_TestPage::keypress(uint8_t key)
{
    if(key == 0x43)
    {
        XTRUITESADC_TestPage::currentADC_read= (XTRUITESADC_TestPage::currentADC_read>= 3)?0:XTRUITESADC_TestPage::currentADC_read+1;
        return 1;
    }
    else if(key == 0x44)
    {
        XTRUITESADC_TestPage::currentADC_read=  (XTRUITESADC_TestPage::currentADC_read<= 0)?3:XTRUITESADC_TestPage::currentADC_read-1;
        return 1;
    }
    return 0;
}




