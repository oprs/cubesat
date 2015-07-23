#ifndef _QB50_XTRUITES_TEST_ADC_CHIP_H_
#define _QB50_XTRUITES_TEST_ADC_CHIP_H_

#include "system/qb50.h"
#include "../Test_ADC_Config.h"

namespace qb50
{

  namespace XTRUITES
  {

    class TestADCChannel;
    class ConvFormula;

    class TestADCChip
    {
      public:
        TestADCChip(qb50::MAX111x& chip, char const * name);

        ~TestADCChip();

        TestADCChannel* channel[XTRUITES_TEST_ADC_NUMBER_OF_CHANNEL]= { nullptr };

        TestADCChip& addChannel(qb50::MAX111x::Channel, char const * name, ConvFormula* convFormula);

        char const * name;
        qb50::MAX111x&    chip;
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_TEST_ADC_CHIP_H_ */


/*EoF*/
