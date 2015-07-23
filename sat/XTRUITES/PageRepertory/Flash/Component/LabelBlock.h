/**
 *  @file     LabelBlock.h
 *  @brief    Component permetant l'affichage des numéros de Block (Entête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_LABEL_BLOCK_H_
#define _QB50_XTRUITES_LABEL_BLOCK_H_

#include "FlashLabel.h"

namespace qb50
{

  namespace XTRUITES
  {
    /// @class  LabelBlock
    /// @brief  Component permetant l'affichage des numéros de Block
    class LabelBlock : public FlashLabel
    {
      public:
        /// @brief  Constructeur: Taille de la liste XTRUITES_RAM_TEST_BLOCK_SIZE
        LabelBlock();

      private:
        /// @brief  Ecriture d'un label de Block verticalement avec le MSB en haut
        /// @param[in]  number  Numéro du Block
        /// @param[in]  color   Couleur du label
        void writeLabel( uint8_t number, Color color);

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_LABEL_BLOCK_H_ */

/*EoF*/
