/**
 *  @file       textBlock.h
 *  @brief      Contrôle textBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_NAVIGATION_MENU_H_
#define _QB50_XTRUITES_NAVIGATION_MENU_H_

#include "../Component.h"

namespace qb50
{

    namespace XTRUITES
    {
        class NavigationMenu : public Component
        {

            public:
                void onLoad( void );

                void addItem(char const * nameVal, Page * page, unsigned char key=0, char const * labelVal= nullptr);
                void addItem(char const * nameVal, char const * page, unsigned char key=0, char const * labelVal= nullptr);
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_NAVIGATION_MENU_H_ */


/*EoF*/
