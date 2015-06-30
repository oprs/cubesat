/**
 *  @file       textualInterface.h
 *  @brief      Gestion comportemental de l'interface (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */


#ifndef _QB50_TEXTUAL_INTERFACE_H_
#define _QB50_TEXTUAL_INTERFACE_H_

#include "FIFO_InputKey.hpp"

namespace qb50
{

    namespace XTRUITES
    {

        typedef enum
        {

            initialize,
            loadPage,
            updatePage,
            unloadPage,
            readKey

        } state_t;

        class OutputStreamChannel;
        class PageRepertory;
        class Page;

        /**
         *  @class      XTRUITES
         *  @brief      Gestion du comportement de l'interface utilisateur textuel
         *  @details    La class XTRUITES permet la gestion du comportement de l'interface utilisateur textuel
         *              Ce qui comprend:
         *              <ul>
         *                  <li>L'affichage du cadre de l'interface ainsi que la localisation</li>
         *                  <li>La gestion des évenements (caractére reçu)</li>
         *                  <li>Le chargement et déchargement de page</li>
         *                  <li>Les actions communes à toutes les pages comme par exemple: XTRUITES::refresh() et XTRUITES::quit()</li>
         *              </ul>
         */
        class Container
        {


            public:

                Container(OutputStreamChannel* streamChannelVal);

                void action();

                void transition();


                void pushKey(unsigned char key);


                state_t getState();

                PageRepertory* getRepertory( void );



            private:
                void _initialize();
                void _loadPage();
                void _updatePage();
                void _unloadPage();
                void _readKey();

                void displayLocation();
                void clearContent();

                state_t _state= initialize;
                PageRepertory* _pageRepertory= nullptr;
                Page* _currentPage= nullptr;
                Page* _nextPage= nullptr;

                FIFO_InputKey _inputKey;

                OutputStreamChannel* _streamChannel;

        };

    }


} /* namespace: qb50 */


#endif /* _QB50_TEXTUAL_INTERFACE_H_ */


/*EoF*/
