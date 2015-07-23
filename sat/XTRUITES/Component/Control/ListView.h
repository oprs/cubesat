/**
 *  @file       textBlock.h
 *  @brief      Contrôle textBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_LIST_H_
#define _QB50_XTRUITES_LIST_H_

#include "Component.h"

namespace qb50
{

  class TextBlock;

  namespace XTRUITES
  {
    class ListView : public Component
    {
      public:
        void onLoad( void );
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_TEXTBLOCK_H_ */


/*EoF*/
