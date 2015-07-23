/**
 *  @file       textBlock.h
 *  @brief      Contrôle textBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_TEXTBLOCK_H_
#define _QB50_XTRUITES_TEXTBLOCK_H_

#include "Component.h"

namespace qb50
{

  namespace XTRUITES
  {
    class TextBlock : public Component
    {

      public:

        /// @brief  Text contenu
        std::string text;

        /**
        *  @brief  Remplisage
        *          true: Contenu complété par des espaces pour remplir entiérement l'espace disponible
        *          false: Contenu text seulement
        */

        enum class Mode : unsigned char
        {
          defaultMode=0,
          paddingMode=1,
          adaptiveSizeMode=2,
          linePaddingAdaptiveHeightMode=3
        };

        Mode mode= Mode::defaultMode;



        /**
        *  @brief      Setter text
        *  @param[in]  textVal: text
        *  @return     Reference XTRUITESTextBlock courrante
        */
        TextBlock&  setText(std::string textVal);

        /**
        *  @brief      Getter text
        *  @return     text
        */
        std::string getText();

        void onLoad( void );

    };

    extern Point writePadding(unsigned char beginX, unsigned char beginY, unsigned char endX, unsigned char endY, unsigned char offset, unsigned char maximum);
    extern Point writePadding(Point beginP, Point endP, unsigned char offset, unsigned char maximum);

  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_TEXTBLOCK_H_ */


/*EoF*/
