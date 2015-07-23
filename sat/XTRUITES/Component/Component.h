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
#include <vector>

#include "ComponentCollection.h"

namespace qb50
{

    namespace XTRUITES
    {
        class ComponentCollection;

        class Component;

        class Component
        {

            public:
                /// @brief  Constructeur: initialise la page en associant son nom et son interface
                Component();

                virtual ~Component();

                /// @brief  Retourne le répertoire où ce trouve la page <br />
                ///         Vous pouvez récuperer le XTRUITES::Container avec Page::getRepertory()->getContainer()
                ComponentCollection&  getCollection();
                Component& setCollection(ComponentCollection* collection);

                virtual void onLoad( void );
                virtual void onUpdate( void );
                virtual void onUnload( void );
                virtual void onKeyPress( uint8_t key );

                void onLoadChildren( void );
                void onUpdateChildren( void );
                void onUnloadChildren( void );
                void onKeyPressChildren( uint8_t key );


                Component& setParent(Component* parentVal);
                Component& getParent( void );
                bool hasParent( void );

                Component& addChildren(Component* componentVal);

                bool hasChildren( void );


                Rectangle&  getRegion( void );
                Component&  setRegion( const Rectangle& regionVal);
                Point&      getLocation( void );
                Component&  setLocation( const Point& locationVal);
                Color&      getColor( void );
                Component&  setColor( const Color& colorVal);
                Size&       getSize( void );
                Component&  setSize( const Size& sizeVal);

                std::vector<Component*> getChildrenCollection( void );

            private:
                std::vector<Component*> _childrenCollection;

                ComponentCollection* _componentCollection;

                Rectangle _region;
                Color _color;

                Component* _parent= nullptr;
        };

    }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COMPONENT_H_ */


/*EoF*/
