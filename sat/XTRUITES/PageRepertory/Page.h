/**
 *  @file       page.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_PAGE_H_
#define _QB50_XTRUITES_PAGE_H_

#include <string>

namespace qb50
{

    namespace XTRUITES
    {
        class ComponentCollection;

        class PageRepertory;

        class Page
        {

            public:
                /// @brief  Constructeur: initialise la page en associant son nom et son interface
                Page(PageRepertory* pageRepertoryVal);

                virtual ~Page();

                Page& setName(std::string nameVal);

                Page& setRepertory(PageRepertory* pageRepertoryVal);

                /// @brief  Retourne le nom de la page
                std::string getName();

                /// @brief  Retourne le répertoire où ce trouve la page <br />
                ///         Vous pouvez récuperer le XTRUITES::Container avec Page::getRepertory()->getContainer()
                PageRepertory* getRepertory();


                ComponentCollection* getCollection( void );

                void onLoad( void );
                void onUpdate( void );
                void onUnload( void );
                void onKeyPress( uint8_t key );

            private:
                std::string _name= "";
                PageRepertory* _pageRepertory;

            protected:
                ComponentCollection* _componentCollection;

        };

    }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_PAGE_H_ */


/*EoF*/
