/**
 *  @file       EscapeSequences.h
 *  @brief      ANSI escape codes (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       11/05/2015 - 15/05/2015
 */

#ifndef _QB50_ESCAPE_SEQUENCES_H_
#define _QB50_ESCAPE_SEQUENCES_H_

#include "Component/Color.h"
#include "Component/Point.h"

namespace qb50
{

    namespace XTRUITES
    {

    /**
     *  @class      EscapeSequences
     *  @brief      Gestion des sorties ANSI escape codes
     */
    /* static */ class EscapeSequences
    {


        public:

            /**
             *  @brief      Déplacement du curseur
             *  @param[in]  x: Position horizontal de 0 (à gauche) à 79 (à droite)
             *  @param[in]  y: Position vertical de 0 (en haut ) à 23 (en bas)
             */
            static void moveCursor(uint8_t x, uint8_t y);
            static void moveCursor(Point* cursor);


            /// @brief      Efface tous le contenu de l'écran
            static void clearScreen();

            /**
             *  @brief      Change la couleur de fond
             *  @param[in]  color: Couleur (voir XTRUITEScolorPalette)
             *  @param[in]  force: Force le changement de couleur
             */
            static void setBackground(uint8_t color, bool force= false);

            /**
             *  @brief      Change la couleur des caractéres
             *  @param[in]  color: Couleur (voir XTRUITEScolorPalette)
             *  @param[in]  force: Force le changement de couleur
             */
            static void setForeground(uint8_t color, bool force= false);

            /// @brief  Inverse la couleur de fond et des caractéres
            static void reversesColors();

            /// @brief  Efface la ligne courrante
            static void erasesEntireCurrentLine();

            /**
             *  @brief      Déplacement de la position d'accueil du curseur
             *  @param[in]  x: Position horizontal de 0 (à gauche) à 79 (à droite)
             *  @param[in]  y: Position vertical de 0 (en haut ) à 23 (en bas)
             */
            static void setHomePosition(uint8_t x, uint8_t y);

            /// @brief Déplace le curseur à la position d'accueil
            static void moveCursorHome();

            /// @brief Réinitialise tous les attribut (couleur, position, scrolling)
            static void resetAttributes();

            /**
             *  @brief      Définie la zone de scrolling
             *  @param[in]  startRow: Ligne de début de 0 (en haut ) à 23 (en bas)
             *  @param[in]  endRow: Ligne de fin de 0 (en haut ) à 23 (en bas)
             */
            static void scrollScreen(uint8_t startRow, uint8_t endRow);

            /**
             *  @brief      Ecrit une chaîne de caractères formatée
             *  @details    Voir printf(): http://www.cplusplus.com/reference/cstdio/printf/
             *  @param[in]  format: chaîne de caractères formatée
             *  @param[in]  ... (additional arguments): argument
             */
            static int write(const char *format , ...);

            /// @brief      Postion horizontal d'accueil du curseur
            /// @details    Valeur de 0 (à gauche) à 79 (à droite)
            static uint8_t xHome;

            /// @brief      Postion vertical d'accueil du curseur
            /// @details    Valeur de 0 (en haut ) à 23 (en bas)
            static uint8_t yHome;

            /// @brief  Couleur de fond actuelle  (voir XTRUITEScolorPalette)
            static uint8_t currentBackground;

            /// @brief  Couleur des caractéres actuelle  (voir XTRUITEScolorPalette)
            static uint8_t currentForeground;



            /**
             *  @brief      Change la couleur de fond et premier plan
             *  @param[in]  color: Couleur (voir XTRUITEScolorPalette)
             *  @param[in]  force: Force le changement de couleur
             */
            static void setColor(Color* color, bool force= false);



    };

} /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_ESCAPE_SEQUENCES_H_ */


/*EoF*/
