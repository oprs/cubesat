/**
 *  @file       textBlock.h
 *  @brief      Contrôle textBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_NAVIGATION_LABEL_H_
#define _QB50_XTRUITES_NAVIGATION_LABEL_H_

#include "Component.h"

namespace qb50
{

    namespace XTRUITES
    {
        class NavigationLabel : public Component
        {

            public:

              NavigationLabel(char const * nameVal, Page * page, unsigned char keyVal= 0, char const * labelVal= nullptr);
              NavigationLabel(char const * nameVal, char const * page, unsigned char keyVal= 0, char const * labelVal= nullptr);
              ~NavigationLabel();
              void initialize( Page * page, char const * labelVal);

              char const* name;
              Page* pageTarget;
              unsigned char keyTarget;
              char* label;

              Color* keyColor;

              void onKeyPress( uint8_t key );
              void onLoad( void );
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_NAVIGATION_LABEL_H_ */


/*EoF*/
