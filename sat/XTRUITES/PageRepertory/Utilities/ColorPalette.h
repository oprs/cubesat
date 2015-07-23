/**
 *  @file       colorPalette.h
 *  @brief      colorPalettePage (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#ifndef _QB50_XTRUITES_COLOR_PALETTE_H_
#define _QB50_XTRUITES_COLOR_PALETTE_H_

#include "../Page.h"

namespace qb50
{

  namespace XTRUITES
  {

    class colorPalettePage : public Page
    {

      public:
        void onLoad( void );
        void writeColorPaletteItem(uint8_t x, uint8_t y, uint8_t color);

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_COLOR_PALETTE_H_ */

/*EoF*/
