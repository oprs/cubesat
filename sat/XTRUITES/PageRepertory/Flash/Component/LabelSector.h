/**
 *  @file     LabelSector.h
 *  @brief    Component permetant l'affichage des numéros de Sector (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_LABEL_SECTOR_H_
#define _QB50_XTRUITES_LABEL_SECTOR_H_

#include "FlashLabel.h"

namespace qb50
{

  namespace XTRUITES
  {
    /// @class  LabelSector
    /// @brief  Component permetant l'affichage des numéros de Sector
    class LabelSector : public FlashLabel
    {
      public:
        /// @brief  Constructeur: Taille de la liste XTRUITES_RAM_TEST_SECTOR_SIZE
        LabelSector();

      private:
        /// @brief  Ecriture d'un label de Sector horizontalement avec le MSB à gauche
        /// @param[in]  number  Numéro du Sector
        /// @param[in]  color   Couleur du label
        void writeLabel( uint8_t number, Color color);

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_LABEL_SECTOR_H_ */

/*EoF*/
