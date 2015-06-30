/**
 *  @file       homePage.h
 *  @brief      Page d'accueil (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#ifndef _QB50_XTRUITES_HOME_PAGE_H_
#define _QB50_XTRUITES_HOME_PAGE_H_

#include "../Page.h"

namespace qb50
{

    namespace XTRUITES
    {

        class homePage : public Page
        {

            public:
                homePage(PageRepertory* pageRepertoryVal);



                void onLoad( void );
                void onUpdate( void );
                void onUnload( void );
                void onKeyPress( uint8_t key );

        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_HOME_PAGE_H_ */

/*EoF*/
