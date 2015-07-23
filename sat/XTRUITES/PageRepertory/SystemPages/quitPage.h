/**
 *  @file       quitPage.h
 *  @brief      Page d'accueil (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#ifndef _QB50_XTRUITES_QUIT_PAGE_H_
#define _QB50_XTRUITES_QUIT_PAGE_H_

#include "../Page.h"

namespace qb50
{

  namespace XTRUITES
  {

    class quitPage : public Page
    {

      public:
        void onLoad( void );
        void onUnload( void );
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_QUIT_PAGE_H_ */

/*EoF*/
