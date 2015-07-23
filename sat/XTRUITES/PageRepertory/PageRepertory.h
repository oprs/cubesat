/**
 *  @file     PageRepertory.h
 *  @brief    Répertoire de page (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  2.1
 *  @date     13/05/2015 - 24/07/2015
 */

#ifndef _QB50_XTRUITES_PAGE_REPERTORY_H_
#define _QB50_XTRUITES_PAGE_REPERTORY_H_

#include <string>
#include <map>

namespace qb50
{
  namespace XTRUITES
  {

    class Page;
    class Container;

    /// @brief  Type table de hachage association un nom à une page
    typedef std::map<std::string, Page*> page_repertory_map_t;

    /// @brief  Type d'item de table de hachage association un nom à une page
    typedef std::pair<std::string, Page*> page_repertory_item_t;


    /**
     *  @class    PageRepertory
     *  @brief    Factory de XTRUITES::Page
     *  @details  XTRUITES::PageRepertory instancie toutes les XTRUITES::Page puis les associent avec leur nom dans une table de hachage.<br />
     *            Ce qui permet de récuperer un pointeur avec un nom de page (PageRepertory::getPageByName)
     *            ou d'effectuer une navigation avec un nom de page (Page::pageNavigate)
     */
    class PageRepertory
    {

      public:

        /// @brief  Constructeur: initialise et répertorie toutes les XTRUITES::Page
        PageRepertory();

        /// @brief  Destructeur: supprime toutes les XTRUITES::Page
        ~PageRepertory();

        /// @brief  Obtient le page à partir de son nom
        Page* getPageByName(std::string name);

        /// @brief  Ajoute une page dans le répertoire
        PageRepertory& addPage(std::string name, Page* page);

        /// @brief  Définit le XTRUITES::Container associé
        PageRepertory& setContainer(Container* container);

        /// @brief  Obtient le XTRUITES::Container associé
        Container& getContainer();

      private:

        /// @brief  Table de hachage association un nom à une page
        page_repertory_map_t _repertory;

        /// @brief  XTRUITES::Container associé
        Container* _container;

    };


  }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_PAGE_REPERTORY_H_ */


/*EoF*/
