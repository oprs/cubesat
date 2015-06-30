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
#include <map>

namespace qb50
{
    namespace XTRUITES
    {


        class Component;

        typedef std::map<std::string, Component*> component_collection_map_t;
        typedef std::pair<std::string, Component*> component_collection_pair_t;

        class ComponentCollection
        {

            public:
                ComponentCollection(Page* pageVal);
                ~ComponentCollection();

                Component* getComponentByName(std::string nameComponent);
                ComponentCollection& add(component_collection_pair_t item);
                ComponentCollection& setPage(Page* pageVal);
                Page* getPage();


                void loadAllComponents( void );
                void updateAllComponents( void );
                void unloadAllComponents( void );
                void keyPressAllComponents( unsigned char key );


            private:
                component_collection_map_t _collection;
                Page* _page= nullptr;

        };


    } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COMPONENT_COLLECTION_H_ */


/*EoF*/
