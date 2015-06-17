/**
 *  @file       textBlock.h
 *  @brief      Contrôle textBlock (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_TEXTBLOCK_H_
#define _QB50_TEXTBLOCK_H_


#include "../textualInterface.h"


namespace qb50
{


    /**
     *  @class      XTRUITESTextBlock
     *  @brief      Contrôle textBlock, affiche du contenu text dans une d'affichage fixe
     */
    class XTRUITESTextBlock
    {

        public:

            /// @brief  Hauteur de la zone d'écriture
            uint8_t     height;

            /// @brief  Longueur de la zone d'écriture
            uint8_t     width;

            /// @brief  Position horizontal de 0 (à droite) à 79 (à gauche)
            uint8_t     locationX;

            /// @brief  Position vertical de 0 (en haut) à 23 (en bas)
            uint8_t     locationY;

            /// @brief  Text contenu
            std::string text;

            /// @brief  Couleur de fond du cadre
            uint8_t     background= XTRUITES_DEFAULT_BACKGROUND;

            /// @brief  Couleur du caractére
            uint8_t     foreground= XTRUITES_DEFAULT_FOREGROUND;

            /**
             *  @brief  Remplisage
             *          true: Contenu complété par des espaces pour remplir entiérement l'espace disponible
             *          false: Contenu text seulement
             */
            bool        padding= true;

            /**
             *  @brief      Setter couleur d'arriére plan
             *  @param[in]  backgroundVal: Couleur d'arriére plan (voir XTRUITEScolorPalette)
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setBackground(uint8_t backgroundVal);

            /**
             *  @brief      Getter couleur d'arriére plan.
             *  @return     Couleur d'arriére plan courrant
             */
            uint8_t             getBackground();

            /**
             *  @brief      Setter couleur des caractéres
             *  @param[in]  foregroundVal: Couleur des caractéres (voir XTRUITEScolorPalette)
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setForeground(uint8_t foregroundVal);

            /**
             *  @brief      Getter couleur des caractéres
             *  @return     Couleur des caractéres courrante
             */
            uint8_t             getForeground();

            /**
             *  @brief      Setter position horizontal
             *  @param[in]  locationXVal: position horizontal de 0 (à droite) à 79 (à gauche)
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setLocationX(uint8_t locationXVal);

            /**
             *  @brief      Getter position horizontal
             *  @return     Position horizontal
             */
            uint8_t             getLocationX();

            /**
             *  @brief      Setter position vertical
             *  @param[in]  locationXVal: position vertical de 0 (en haut) à 23 (en bas)
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setLocationY(uint8_t locationYVal);

            /**
             *  @brief      Getter position vertical
             *  @return     Position vertical
             */
            uint8_t             getLocationY();

            /**
             *  @brief      Setter hauteur
             *  @param[in]  heightVal: hauteur
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setHeight(uint8_t heightVal);

            /**
             *  @brief      Getter hauteur
             *  @return     Hauteur
             */
            uint8_t             getHeight();

            /**
             *  @brief      Setter longueur
             *  @param[in]  widthVal: longueur
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setWidth(uint8_t widthVal);

            /**
             *  @brief      Getter longueur
             *  @return     longueur
             */
            uint8_t             getWidth();

            /**
             *  @brief      Setter text
             *  @param[in]  textVal: text
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  setText(std::string textVal);

            /**
             *  @brief      Getter text
             *  @return     text
             */
            std::string         getText();

            /**
             *  @brief      Affiche la textblock dans l'interface
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  display();

            /**
             *  @brief      Inverse la couleur des caractére et celle de l'arriére plan
             *  @return     Reference XTRUITESTextBlock courrante
             */
            XTRUITESTextBlock&  reversesColors();
    };


} /* namespace: qb50 */


#endif /* _QB50_TEXTBLOCK_H_ */


/*EoF*/
