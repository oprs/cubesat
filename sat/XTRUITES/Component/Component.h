/**
 *  @file       page.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_COMPONENT_H_
#define _QB50_XTRUITES_COMPONENT_H_

#include "Rectangle.h"
#include "Color.h"
#include <string>
#include <map>

namespace qb50
{

    namespace XTRUITES
    {
        class ComponentCollection;

        class Component;

        typedef std::map<std::string, Component*> component_children_map_t;
        typedef std::pair<std::string, Component*> component_children_pair_t;

        class Component
        {

            public:
                /// @brief  Constructeur: initialise la page en associant son nom et son interface
                Component();

                virtual ~Component();

                Component& setName(std::string nameVal);

                Component& setCollection(ComponentCollection* componentCollectionVal);

                /// @brief  Retourne le nom de la page
                std::string getName( void );

                /// @brief  Retourne le répertoire où ce trouve la page <br />
                ///         Vous pouvez récuperer le XTRUITES::Container avec Page::getRepertory()->getContainer()
                ComponentCollection* getCollection();

                virtual void onLoad( void )=0;
                virtual void onUpdate( void )=0;
                virtual void onUnload( void )=0;
                virtual void onKeyPress( uint8_t key )=0;

                Component& setParent(Component*);
                Component* getParent( void );
                bool hasParent( void );

                Component& addChildren(component_children_pair_t item);
                Component& addChildren(Component* childrenVal);

                bool hasChildren( void );
                Component* getChildrenByName( std::string nameChildren );

                Rectangle* region= nullptr;

                Rectangle* getRegion();
                Component& setRegion( Rectangle* regionVal );
                Component& setRegion( Point* locationVal, Size* sizeVal );
                Component& setRegion( unsigned char xVal, unsigned char yVal, unsigned char widthVal, unsigned char heightVal );

                Color* color= nullptr;

                Color* getColor( void );
                Component& setColor( Color* color );
                Component& setColor( unsigned char background, unsigned char foreground );


                ComponentCollection* _componentCollection= nullptr;
                component_children_map_t _childrenCollection;

            private:
                std::string _name= "";
                Component* _parent= nullptr;

        };

    }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COMPONENT_H_ */


/*EoF*/
