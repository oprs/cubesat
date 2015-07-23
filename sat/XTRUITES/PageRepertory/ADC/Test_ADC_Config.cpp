#include "system/qb50.h"
#include "TestADCChip.h"
#include "TestADCChannel.h"
#include "ConvFormula.h"
#include "config.h"
#include "ADCWatch.h"

using namespace qb50::XTRUITES;
using namespace qb50;




Test_ADC_Config::Test_ADC_Config()
{
  _initialize_ConvFormula();

  ADC[0] = _initialize_Test_ADC_Power_1();
  ADC[1] = _initialize_Test_ADC_Power_2();
  ADC[2] = _initialize_Test_ADC_ODB();
  ADC[3] = _initialize_Test_ADC_FiPEX();
}

Test_ADC_Config::~Test_ADC_Config()
{

  for (std::map<std::string, ConvFormula*>::iterator it = _convList.begin(); it != _convList.end(); ++it)
  {
    if(it->second != nullptr)
      delete it->second;
  }
  _convList.clear();

  for(unsigned char i=0; i< XTRUITES_TEST_ADC_NUMBER; i++)
  {
    if(ADC[i] != nullptr)
      delete ADC[i];
  }
}




void Test_ADC_Config::_initialize_ConvFormula( void )
{

  //        Name                          Unit          Coef  Offset
  _convList[ "default" ]=  new ConvFormula("Undefined",  1,    0   );
  _convList[ "T_Bat"   ]=  new ConvFormula("°C",         12,   -14 );
  _convList[ "V_Bat"   ]=  new ConvFormula("mV",         3,    -41 );
}




TestADCChip* Test_ADC_Config::_initialize_Test_ADC_Power_1( void )
{
  //                                        ADC         Nom
  TestADCChip*  ADC_Chip= new TestADCChip( ADC_Power_1, "ADC Power 1 (U5)"    );

  //                    Channel       Nom           Formule de conversion
  ADC_Chip->addChannel(MAX111x::CH0,  "V4",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH1,  "I4",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH2,  "T4",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH3,  "V1",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH4,  "I1",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH5,  "T1",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH6,  "T_bat",      _convList["T_Bat"]);
  ADC_Chip->addChannel(MAX111x::CH7,  "V_bat",      _convList["V_Bat"]);

  return ADC_Chip;
}

TestADCChip* Test_ADC_Config::_initialize_Test_ADC_Power_2( void )
{
  //                                        ADC         Nom
  TestADCChip*  ADC_Chip= new TestADCChip( ADC_Power_2, "ADC Power 1 (U5)"    );

  //                    Channel       Nom           Formule de conversion
  ADC_Chip->addChannel(MAX111x::CH0,  "V2",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH1,  "T2",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH2,  "I2",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH3,  "V3",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH4,  "T3",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH5,  "I3",         _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH6,  "I_SURT",     _convList["default"]);
  ADC_Chip->addChannel(MAX111x::CH7,  "CH7",        _convList["default"]);

  return ADC_Chip;
}

TestADCChip* Test_ADC_Config::_initialize_Test_ADC_ODB( void )
{
  //                                        ADC         Nom
  TestADCChip*  ADC_Chip= new TestADCChip( ADC_ODB,     "ADC ODB (U7)"  );

  //                    Channel       Nom           Formule de conversion
  ADC_Chip->addChannel( MAX111x::CH0, "I_ADCS",     _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH1, "T_ARM",      _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH2, "I_RX",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH3, "RSSI",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH4, "I_TX",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH5, "P_TX",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH6, "P_PA",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH7, "T_PA",       _convList["default"]);

  return ADC_Chip;
}


TestADCChip* Test_ADC_Config::_initialize_Test_ADC_FiPEX( void )
{
  //                                        ADC         Nom
  TestADCChip*  ADC_Chip= new TestADCChip(  ADC_FiPEX,  "ADC Alim Fipex (U2)" );

  //                    Channel       Nom           Formule de conversion
  ADC_Chip->addChannel( MAX111x::CH0, "I_ADCS",     _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH1, "I_GPS",      _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH2, "CH2_CSS",    _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH3, "I_3,3V",     _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH4, "V_3,3V",     _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH5, "I_5V",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH6, "V_5V",       _convList["default"]);
  ADC_Chip->addChannel( MAX111x::CH7, "SU_TH_Go",   _convList["default"]);

  return ADC_Chip;
}

/* EoF */
