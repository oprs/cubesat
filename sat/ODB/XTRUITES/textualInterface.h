/**
 *  @file       textualInterface.h
 *  @brief      Gestion comportemental de l'interface (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */


#ifndef _QB50_TEXTUAL_INTERFACE_H_
#define _QB50_TEXTUAL_INTERFACE_H_


#include <functional>
#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <sstream>

#include "system/qb50.h"

#include "conditionalPrinter.h" // Disable/Enable printf and hexdump
#include "escapeSequences.h"    // ANSI Escape Sequence lib
#include "inputHandler.h"

// Controls
#include "control/textBlock.h"
#include "control/listTextBlock.h"

// Pages
#include "page.h"
#include "pageDirectory/homePage.h"
#include "pageDirectory/colorPalette.h"
#include "pageDirectory/ADCS_test/ADC_TestPage.h"


namespace qb50
{


    /**
     *  @class      XTRUITES
     *  @brief      Gestion du comportement de l'interface utilisateur textuel
     *  @details    La class XTRUITES permet la gestion du comportement de l'interface utilisateur textuel
     *              Ce qui comprend:
     *              <ul>
     *                  <li>L'affichage du cadre de l'interface ainsi que la localisation</li>
     *                  <li>La gestion des évenements (caractére reçu)</li>
     *                  <li>Le chargement et déchargement de page</li>
     *                  <li>Les actions communes à toutes les pages comme par exemple: XTRUITES::refresh() et XTRUITES::quit()</li>
     *              </ul>
     */
    class XTRUITES
    {


        public:

            /// @brief  Page courrante
            XTRUITESPage*                       page;

            /**
             *  @brief      Etat de l'Interface
             *  @details    <ul>
             *                   <li>True: activé</li>
             *                   <li>False: désactivé</li>
             *              </ul>
             *              Remarque: enable est utilisé dans conditionalPrinter.cpp
             */
            static bool                         enable;

            /// @brief  Constructeur: initialise XTRUITES et charge la XTRUITEShomePage
            XTRUITES(void);

            /// @brief  Destructeur: décharge la XTRUITES::page, réinialise le terminal et désactive XTRUITES
            ~XTRUITES(void);

            ///  @brief  Effectue une réécriture du cadre et recharge la XTRUITES::page
            ///  @return Reference XTRUITES courrante
            XTRUITES& refresh();

            /// @brief  Décharge la XTRUITES::page, réinialise le terminal et désactive XTRUITES
            /// @return Reference XTRUITES courrante
            XTRUITES& quit();

            /// @brief  initialise XTRUITES et charge la XTRUITEShomePage
            /// @return Reference XTRUITES courrante
            XTRUITES& initialize();

            /// @brief  Initialise le terminal et affiche le cadre
            /// @return Reference XTRUITES courrante
            XTRUITES& displayDefaultLayout();

            /// @brief  Affiche la location (Nom de XTRUITES::page)
            /// @return Reference XTRUITES courrante
            XTRUITES& displayLocation();

            /// @brief  Supprime tout le contenu à l'interrieur du cadre
            /// @remark Pour supprimer des caractére parasite sur le cadre utilisez: XTRUITES::displayDefaultLayout()
            /// @return Reference XTRUITES courrante
            XTRUITES& clearContent();

            /**
             *  @brief      Quitte la page courrante et charge la nouvelle page
             *  @param[in]  newPage: Nouvelle page
             *  @return     Reference XTRUITES courrante
             */
            XTRUITES& loadPage(XTRUITESPage *newPage);

            /**
             *  @brief      Appelle les actions correspondantes aux touches reçus
             *  @remark     En premier les actions de XTRUITES::page puis les actions communes (comme XTRUITES::refresh() et XTRUITES::quit() )
             *  @param[in]  key: Touche pressé
             *  @return     Nombre d'action appellé
             */
            uint8_t readKey(uint8_t key);


    };


} /* namespace: qb50 */


#endif /* _QB50_TEXTUAL_INTERFACE_H_ */


/*EoF*/
