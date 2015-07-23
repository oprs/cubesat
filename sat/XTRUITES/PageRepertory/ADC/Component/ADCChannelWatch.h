 /**
 *  @file     ItemSector.h
 *  @brief    Component permetant de visualiser les résultats des test sur chaque secteur (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_FIELD_ADC_H_
#define _QB50_XTRUITES_FIELD_ADC_H_

#include <string>
#include "../../Component/Component.h"
#include "system/qb50.h"

namespace qb50
{

  namespace XTRUITES
  {


    class TestADCChannel;

    /**
     *  @class    ItemSector
     *  @brief    Component permetant de visualiser les résultats des test sur chaque secteur
     */
    class ADCChannelWatch : public Component
    {

      public:
        ADCChannelWatch(TestADCChannel* channel);
        void onLoad( void );
        void onUpdate( void );

      private:
        TestADCChannel* _channel;
        qb50::MAX111x::ConvResp _lastConv= { 0, 0, 0, 0};

    };


  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_FIELD_ADC_H_ */


/*EoF*/

