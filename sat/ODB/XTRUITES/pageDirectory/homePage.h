/**
 *  @file       homePage.h
 *  @brief      Page d'accueil (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#ifndef _QB50_XTRUITES_HOME_PAGE_H_
#define _QB50_XTRUITES_HOME_PAGE_H_


#include "../textualInterface.h"


namespace qb50
{


    class XTRUITESListTextBlock;

    /**
     *  @class      XTRUITEShomePage
     *  @brief      Page d'accueil
     */
    class XTRUITEShomePage : public XTRUITESPage
    {


        public:
            XTRUITEShomePage(XTRUITES& _XTRUITESInterfaceVal);

            void load(void);
            void unload(void);
            uint8_t  keypress(uint8_t key);

            XTRUITESListTextBlock* menuList;
    };


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_HOME_PAGE_H_ */


/*EoF*/
