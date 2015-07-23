/**
 *  @file
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version
 *  @date
 */

#ifndef _QB50_XTRUITES_H_
#define _QB50_XTRUITES_H_

#include "Container.h"
#include "OutputStream/OutputStream.h"
#include "OutputStream/OutputStreamChannel.h"

/// @brief  Titre affiché au centre en haut
#define XTRUITES_TITLE_STR                        "XCubeSat Textual Rapid User Interface to Test Embedded Systems"
/// @brief  Longueur du titre
#define XTRUITES_TITLE_WIDTH                      62

// color definition
/// @brief  Fond par défaut
#define XTRUITES_DEFAULT_COLOR_BACKGROUND         23
/// @brief  Premier plan par défaut
#define XTRUITES_DEFAULT_COLOR_FOREGROUND         253

/// @brief  Fond des touche de raccourcis par défaut
#define XTRUITES_DEFAULT_COLOR_KEY_BACKGROUND     23
/// @brief  Premier plan des touche de raccourcis par défaut
#define XTRUITES_DEFAULT_COLOR_KEY_FOREGROUND     41

/// @brief  Premier plan de la localisation (nom de page en bas à gauche)
#define XTRUITES_LOCATION_FOREGROUND              214

/// @brief  Position en x des XTRUITES::Component par défaut
#define XTRUITES_DEFAULT_LOCATION_X               0
/// @brief  Position en y des XTRUITES::Component par défaut
#define XTRUITES_DEFAULT_LOCATION_Y               0

/// @brief  Longeur des XTRUITES::Component par défaut
#define XTRUITES_DEFAULT_WIDTH                    40
/// @brief  Hauteur des XTRUITES::Component par défaut
#define XTRUITES_DEFAULT_HEIGHT                   2

/// @brief  Taille du FIFO des touche reçus enregistré (multiple de 2)
#define XTRUITES_FIFO_DEPTH                       8

/// @brief  Affiche la derniére touche pressé
#define XTRUITES_DEBUG_ENABLED                    true

/// @brief  Longueur de l'écran
#define XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH     132
/// @brief  Largeur de l'écran
#define XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT    43


namespace qb50
{

    namespace XTRUITES
    {

        extern Container            XTRUITESContainer;
        extern OutputStream         OutputStreamUART3;

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

extern qb50::XTRUITES::OutputStreamChannel& OutputStreamChannelSyscalls;

#endif /* _QB50_XTRUITES_H_ */

/*EoF*/
