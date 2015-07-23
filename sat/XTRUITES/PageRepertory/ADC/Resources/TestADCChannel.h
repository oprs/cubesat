#ifndef _QB50_XTRUITES_TEST_ADC_CHANNEL_H_
#define _QB50_XTRUITES_TEST_ADC_CHANNEL_H_

#include <string>
#include "system/qb50.h"

namespace qb50
{

  namespace XTRUITES
  {

    class TestADCChip;
    class ConvFormula;

    class TestADCChannel
    {
      public:
        TestADCChannel(TestADCChip* ADC, qb50::MAX111x::Channel, char const * name, ConvFormula* convFormula);

        TestADCChip*            ADC;
        char const *            name;
        ConvFormula*            convFormula;
        qb50::MAX111x::Channel  chNumber;
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_TEST_ADC_CHANNEL_H_ */


/*EoF*/
