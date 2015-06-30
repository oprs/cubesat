/**
 *  @file       page.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_PAGE_REPERTORY_H_
#define _QB50_XTRUITES_PAGE_REPERTORY_H_


#include <string>
#include <map>
#include "unistd.h"


namespace qb50
{
    namespace XTRUITES
    {


        class Page;
        class Container;

        typedef std::map<std::string, Page*> page_repertory_map_t;
        typedef std::pair<std::string, Page*> page_repertory_item_t;

        class PageRepertory
        {

            public:
                PageRepertory(Container* containerVal);
                ~PageRepertory();

                Page* getPageByName(std::string namePage);
                PageRepertory& add(page_repertory_item_t item);
                PageRepertory& setContainer(Container* containerVal);
                Container* getContainer();

            private:
                page_repertory_map_t _repertory;
                Container* _container;

        };


    }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_PAGE_REPERTORY_H_ */


/*EoF*/
