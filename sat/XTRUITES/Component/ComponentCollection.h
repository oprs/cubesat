/**
 *  @file       ComponentCollection.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_COMPONENT_COLLECTION_H_
#define _QB50_XTRUITES_COMPONENT_COLLECTION_H_

#include <string>
#include <vector>

namespace qb50
{
    namespace XTRUITES
    {

        class Component;

        class ComponentCollection
        {

            public:
                ComponentCollection(Page* pageVal);

                ~ComponentCollection();

                ComponentCollection& addComponent(Component* component);
                ComponentCollection& setPage(Page* pageVal);
                Page& getPage();

                void loadAllComponents( void );
                void updateAllComponents( void );
                void unloadAllComponents( void );
                void keyPressAllComponents( unsigned char key );

                ComponentCollection& eraseComponent(Component* component);

            private:
                std::vector<Component*> _collection;
                Page* _page= nullptr;

        };


    } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COMPONENT_COLLECTION_H_ */


/*EoF*/
