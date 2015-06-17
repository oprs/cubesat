/**
 *  @file       page.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_PAGE_H_
#define _QB50_XTRUITES_PAGE_H_


#include "textualInterface.h"


namespace qb50
{


    class XTRUITES;


    /**
     *  @class  XTRUITESPage
     *  @brief  Model de page pour XTRUITES
     */
    class XTRUITESPage
    {

        public:

            /**
             *  @brief      Constructeur: initialise la page en associant son nom et son interface
             *  @param[in]  _XTRUITESInterfaceVal: Référence de l'interface XTRUITES
             *  @param[in]  _nameVal: Nom de la page (pour la localisation dans XTRUITES)
             */
            XTRUITESPage(XTRUITES& _XTRUITESInterfaceVal, std::string _nameVal);

            /// @brief  Getter nom de la page (pour la localisation dans XTRUITES)
            std::string getName(void);

            /// @brief  Getter XTRUITES cible
            XTRUITES&    getInterface(void);

            /// @brief  Méthode de chargement de page
            virtual void load(void)=0;

            /// @brief  Méthode de déchargement de page
            virtual void unload(void)=0;

            /**
             *  @brief      Méthode callback lors de la réception d'un caractére
             *  @param[in]  key: Caractére reçu
             *  @return     Nombre d'événement apellé
             */
            virtual uint8_t  keypress(uint8_t /* key */)=0;

        private:

            /// @brief  Reference de XTRUITES cible
            XTRUITES&   _XTRUITESInterface;

            /// @brief  Nom de la page (pour la localisation dans XTRUITES cible)
            std::string _name;

    };


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_PAGE_H_ */


/*EoF*/
