/**
 *  @file     Page.h
 *  @brief    Model de page (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  2.1
 *  @date     13/05/2015 - 24/07/2015
 */

#ifndef _QB50_XTRUITES_PAGE_H_
#define _QB50_XTRUITES_PAGE_H_

#include <string>

namespace qb50
{

  namespace XTRUITES
  {

    class Component;
    class PageRepertory;
    class ComponentCollection;

    /**
     *  @class    Page
     *  @brief    Model de page
     *  @details  Les pages de XTRUITES contiennent chacunes des méthodes appelé par les événements du
     *            XTRUITES::Container ainsi qu'une collection de XTRUITES::Component.
     *
     *            En dérivant cette classe, il est possible de redéfinir les événement (onLoad, onUpdate, onKeyPress, etc.)
     *
     *  @warning  N'oubliez pas de propager les événements aux XTRUITES::Component contenu dans la page avec les méthode
     *            Component::onLoad() ou _componentCollection->loadAllComponents() par exemple lorsque vous supplanter une méthode.
     */
    class Page
    {

      public:

        /// @brief  Constructeur: initialise le XTRUITES::ComponentCollection de la page
        Page();

        /// @brief  Destructeur: supprime le XTRUITES::ComponentCollection de la page
        virtual ~Page();

        /// @brief  Définit le nom de la page
        Page& setName(std::string nameVal);
        /// @brief  Obtient le nom de la page
        std::string getName();

        /// @brief  Définit le XTRUITES::PageRepertory dans lequelle la page est répertoriée
        Page& setRepertory(PageRepertory* pageRepertoryVal);

        /// @brief  Obtient le XTRUITES::PageRepertory dans lequelle la page est répertoriée <br />
        ///         Vous pouvez récuperer le XTRUITES::Container avec Page::getRepertory()->getContainer()
        PageRepertory& getRepertory();

        /// @brief  Obtient le XTRUITES::ComponentCollection qui comporte tous les XTRUITES::Component de la page
        /// @return XTRUITES::ComponentCollection de la page
        ComponentCollection& getCollection( void );

        /// @brief    Appelé lorsque le XTRUITES::Container applique le chargement de cette page
        /// @details  Cette méthode par défaut appele ComponentCollection::loadAllComponents
        ///           ce qui entraine le chargement de tous les components de la page
        virtual void onLoad( void );

        /// @brief    Appelé lorsque le XTRUITES::Container applique la mise à jour de cette page
        /// @details  Cette méthode par défaut appele ComponentCollection::updateAllComponents
        ///           ce qui entraine la mise à jour de tous les components de la page
        virtual void onUpdate( void );

        /// @brief    Appelé lorsque le XTRUITES::Container applique le déchargement de cette page
        /// @details  Cette méthode par défaut appele ComponentCollection::unloadAllComponents
        ///           ce qui entraine le déchargement de tous les components de la page
        virtual void onUnload( void );

        /// @brief    Appelé lorsque le XTRUITES::Container applique l'événement de touche reçus de cette page
        /// @details  Cette méthode par défaut appele ComponentCollection::keyPressAllComponents
        ///           ce qui entraine le déchargement de l'événement de touche reçus sur tous les components de la page
        virtual void onKeyPress( uint8_t key );

        /// @brief      Navigue vers la page spécifié
        /// @details    Si le nom n'est pas répertorié dans XTRUITES::PageRepertory
        ///             aucune navigation ne sera effectué
        /// @param[in]  name:   Nom de la page cible
        void pageNavigate( std::string name);

        /// @brief      Navigue vers la page spécifié
        /// @details    Si l'instance de page n'est pas répertorié dans XTRUITES::PageRepertory
        ///             aucune navigation ne sera effectué
        /// @param[in]  page:   Instance de page cible
        void pageNavigate( Page * page);

        /// @brief      Ajoute un XTRUITES::Component dans le XTRUITES::ComponentCollection de la page
        /// @param[in]  compenent: component à ajouter
        void addComponent( Component* compenent);

        /// @brief      Supprime un XTRUITES::Component dans le XTRUITES::ComponentCollection de la page
        /// @param[in]  compenent: component à supprimer
        void eraseComponent( Component* compenent);

      private:

        /// @brief      Nom de la page
        std::string _name= "";

        /// @brief      Répertoire de page dans lequelle la page est répertoriée
        PageRepertory* _pageRepertory;

        /// @brief      Collection de component associer à la page
        ComponentCollection* _componentCollection;

    };

  }

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_PAGE_H_ */

/*EoF*/
