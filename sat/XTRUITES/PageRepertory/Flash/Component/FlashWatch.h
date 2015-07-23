/**
 *  @file     FlashWatch.h
 *  @brief    Component permetant d'effectuer et de visualiser les tests sur une RAM (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_RAM_WATCH_H_
#define _QB50_XTRUITES_RAM_WATCH_H_

#include "FlashPage.h"
#include "../../Component/Component.h"
#include "LabelSector.h"
#include "LabelBlock.h"
#include "ItemSector.h"

namespace qb50
{

  namespace XTRUITES
  {
    /// @class  FlashWatch
    /// @brief  Component permetant d'effectuer et de visualiser les tests sur une RAM
    class FlashWatch : public Component
    {

      public:
        /// @brief  Constructeur: initialise et liee tout les components fils: LabelBlock, LabelSector et ItemSector
        FlashWatch();
        /// @brief  Affiche les titres (Sector et Block), postionne les components fils puis les charge
        void onLoad( void );
        /// @brief  Met à jour la machine à état
        void onUpdate( void );

        private:
        /// @brief  Block cible
        uint8_t _cursorBlock=0;
        /// @brief  Secteur cible
        uint8_t _cursorSector=0;
        /// @brief  Component affichant les numéros de block
        LabelBlock  _labelBlock;
        /// @brief  Component affichant les numéros de secteur
        LabelSector _labelSector;
        /// @brief  Component affichant le résultat des tests d'un secteur
        ItemSector  _itemSector;

        /**
         *  @brief  Etape du test
         *  <ol>
         *  <li>0: waitTest</li>
         *  <li>1: sectorErase</li>
         *  <li>2: singleWrite</li>
         *  <li>3: blockErase</li>
         *  <li>4: writeConsecutive</li>
         *  <li>5: chipErase</li>
         *  <li>6: endTest</li>
         *  </ol>
         */
        unsigned char _stepTest=0;

        /**
         *  @brief  Etat du FlashWatch
         *  <ol>
         *  <li>initialize: Affiche le menu et récupère le Device Identification</li>
         *  <li>test: test en cour, affiche les résultats au fur et à mesure</li>
         *  <li>wait: test terminé, attend une instruction</li>
         *  </ol>
         */
        enum : unsigned char {
          initialize = 0,
          test = 1,
          wait = 2
        } _state= initialize;

        /// @brief  Effectue le test correspondant au _stepTest, _labelSector et _labelBlock sélectionné
        /// @return Résultat du test (true= réussi, false= échec)
        bool runTestSequence( void );

        /// @brief  Affiche le titre "SECTOR" en vertical
        /// @param[in]  xLocation  Position horizontal du titre
        /// @param[in]  yLocation  Position vertical du titre
        void _sectorTitle( unsigned char xLocation, unsigned char yLocation );

        /// @brief  Affiche le titre "BLOCK" en horizontal
        /// @param[in]  xLocation  Position horizontal du titre
        /// @param[in]  yLocation  Position vertical du titre
        void _blockTitle( unsigned char xLocation, unsigned char yLocation );

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_RAM_WATCH_H_ */


/*EoF*/
