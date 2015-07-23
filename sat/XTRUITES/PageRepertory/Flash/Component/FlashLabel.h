/**
 *  @file     FlashLabel.h
 *  @brief    Component à redéfinir destinée à l'afficher une liste de labels (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#ifndef _QB50_XTRUITES_RAM_LABEL_H_
#define _QB50_XTRUITES_RAM_LABEL_H_

#include "../../Component/Component.h"

namespace qb50
{
  namespace XTRUITES
  {

    /// @class  FlashLabel
    /// @brief  Component à redéfinir destinée à l'afficher une liste de labels
    class FlashLabel : public Component
    {

      public:
        /// @brief  Constructeur: défini la taille de la liste de label
        /// @param[in]  sizeListLabelVal  Nombre d'item dans la liste
        FlashLabel(uint8_t sizeListLabelVal = 0);

        /// @brief  Affiche tous les label désélectionné
        void onLoad( void );

        /// @brief  Sélectionne un label (Inverse les couleurs)
        /// @param[in]  number  Numéro du label sélectionné
        void select( uint8_t number );

        /// @brief  Déselectionne le dernier label sélectionné
        void deselect( void );

       private:
        /// @brief  Numéros du label cible
        unsigned char _currentNumber=0;

        /// @brief  Indique si le label cible est sélectionné
        bool _currentIsSelected = false;

        /// @brief  Taille de la liste de label
        unsigned char _sizeListLabel;

        /// @brief  Méthode d'écriture d'un label à redéfinir
        /// @param[in]  number  Numéro du label à afficher
        /// @param[in]  color   Couleur du label
        virtual void writeLabel( uint8_t /*number*/, Color /*color*/)=0;

    };

  } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_RAM_LABEL_H_ */


/*EoF*/
