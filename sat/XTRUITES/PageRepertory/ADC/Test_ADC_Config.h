#ifndef _QB50_XTRUITES_ADC_CONFIG_H_
#define _QB50_XTRUITES_ADC_CONFIG_H_

#include <string>
#include <map>

#define XTRUITES_TEST_ADC_NUMBER 4
#define XTRUITES_TEST_ADC_NUMBER_OF_CHANNEL 8

namespace qb50
{

  namespace XTRUITES
  {

    class TestADCChip;
    class ConvFormula;

    class Test_ADC_Config
    {
      public:
        Test_ADC_Config();
        ~Test_ADC_Config();

        TestADCChip* ADC[XTRUITES_TEST_ADC_NUMBER];

      private:
        void _initialize_ConvFormula( void );
        TestADCChip* _initialize_Test_ADC_Power_1( void );
        TestADCChip* _initialize_Test_ADC_Power_2( void );
        TestADCChip* _initialize_Test_ADC_ODB( void );
        TestADCChip* _initialize_Test_ADC_FiPEX( void );


        std::map<std::string, ConvFormula*> _convList;
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_ADC_CONFIG_H_ */

/*EoF*/
