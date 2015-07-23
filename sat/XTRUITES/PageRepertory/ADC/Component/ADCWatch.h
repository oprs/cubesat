#ifndef _QB50_XTRUITES_ADC_WATCH_H_
#define _QB50_XTRUITES_ADC_WATCH_H_

#include <string>
#include "../../Component/Component.h"

namespace qb50
{

  namespace XTRUITES
  {

    class TestADCChip;

    class ADCWatch : public Component
    {

      public:
        ADCWatch(TestADCChip* chip);
        void onLoad( void );
        void onUpdate( void );

      private:
        TestADCChip*  _chip;

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_ADC_WATCH_H_ */


/*EoF*/
