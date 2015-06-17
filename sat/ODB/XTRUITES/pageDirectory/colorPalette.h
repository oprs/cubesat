/**
 *  @file       colorPalette.h
 *  @brief      Page affichant une palette de 256 couleurs (En-tête).
 *  @author     Jérôme skoda <jerome.skoda@hotmail.fr>
 *  @version    1.4
 *  @date       28/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_COLOR_PAGE_H_
#define _QB50_XTRUITES_COLOR_PAGE_H_


#include "../textualInterface.h"


namespace qb50
{


    /**
     *  @class      XTRUITEScolorPalette
     *  @brief      Page affichant une palette de 256 couleurs
     *  @author     Jérôme skoda <jerome.skoda@hotmail.fr>
     *  @version    1.4
     *  @date       28/05/2015 - 12/06/2015
     */
    class XTRUITEScolorPalette : public XTRUITESPage
    {


        public:
            XTRUITEScolorPalette(XTRUITES& _XTRUITESInterfaceVal);

            void load(void);
            void unload(void);
            uint8_t  keypress(uint8_t key);
    };

    /**
     *  @brief      Affiche la couleur et son numeros
     *  @param[in]  interface: Interface cible
     *  @param[in]  x: Position horizontal de 0 (à gauche) à 79 (à droite)
     *  @param[in]  y: Position vertical de 0 (en haut ) à 23 (en bas)
     *  @param[in]  color: Couleur
     */
    extern void writeColorPaletteItem(XTRUITES& interface, uint8_t x, uint8_t y, uint8_t color);


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COLOR_PAGE_H_ */


/*EoF*/
