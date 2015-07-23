/**
 *  @file
 *  @brief
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_ADC_PAGE_H_
#define _QB50_XTRUITES_ADC_PAGE_H_

#include "../Page.h"
#include "../PageRepertory.h"
#include "Test_ADC_Config.h"

namespace qb50
{

  namespace XTRUITES
  {

    class ADCWatch;
    class Test_ADC_Config;

    class ADCPage : public Page
    {

      public:
        ADCPage();

        void onLoad( void );
//        void onUpdate( void );
        void onUnload( void );
//        void onKeyPress( uint8_t key );

        ADCWatch* ADCWatchComponent[XTRUITES_TEST_ADC_NUMBER_OF_CHANNEL] = { nullptr};
        Test_ADC_Config* test_ADC_Config;
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_ADC_PAGE_H_ */

/*EoF*/
