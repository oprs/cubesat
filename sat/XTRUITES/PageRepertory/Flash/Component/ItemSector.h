/**
 *  @file     ItemSector.h
 *  @brief    Component permetant de visualiser les résultats des test sur chaque secteur (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_ITEM_SECTOR_H_
#define _QB50_XTRUITES_ITEM_SECTOR_H_

/// Couleur du premier plan des secteurs
#define XTRUITES_RAM_TEST_FOREGROUND_ITEM_SECTOR 21

#include "../../Component/Component.h"
#include "LabelSector.h"
#include "LabelBlock.h"
#include "FlashPage.h"

namespace qb50
{

  namespace XTRUITES
  {
    /**
     *  @class    ItemSector
     *  @brief    Component permetant de visualiser les résultats des test sur chaque secteur
     */
    class ItemSector : public Component
    {

      public:
        /// @brief  Constructeur: remise à zero de résultat de test
        /// @param[in]  labelBlockVal   Componant LabelBlock permetant de ce positionner horizontalement
        /// @param[in]  labelSectorVal  Componant LabelSector permetant de ce positionner verticalement
        ItemSector(LabelBlock* labelBlockVal, LabelSector* labelSectorVal);

        /// @brief  Affiche tout les secteurs à leurs valeurs initiales (vert)
        void onLoad( void );


        /**
         *  @brief  Enregistre le résultat du secteur cible (un échec rend la case plus proche du rouge)
         *          <br />Sélectionne les curseurs block et secteur correspondant puis affiche le résultat
         *  @param[in]  _cursorBlock  Numéro du block cible
         *  @param[in]  _cursorSector Numéro du secteur cible
         *  @param[in]  result        Résultat (true=réusite, false= échec)
         */
        void addResult(unsigned char _cursorBlock, unsigned char _cursorSector, bool result);

        /// @brief  Dégradé de vert (0) jusqu'à rouge (5) conformement à xTerm 256 colors
        static const unsigned char greenToRedGradient[6];



        void initializeResult( void );

      private:

        /// @brief  LabelBlock associé à l'ItemSector
        LabelBlock*  _labelBlock;

        /// @brief  LabelSector associé à l'ItemSector
        LabelSector* _labelSector;

        /// @brief  Liste des résultat connu les valeur sont généralement compris entre 0 et 4
        uint8_t resultList[ XTRUITES_RAM_TEST_BLOCK_SIZE ][ XTRUITES_RAM_TEST_SECTOR_SIZE ];

        /**
         *  @brief  Affichage des résultats d'un secteur (vert: réusite total rouge: échec total)
         *  @param[in]  _cursorBlock  Numéro du block cible
         *  @param[in]  _cursorSector Numéro du secteur cible
         */
        void writeSector(unsigned char _cursorBlock, unsigned char _cursorSector);
    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_ITEM_SECTOR_H_ */


/*EoF*/
