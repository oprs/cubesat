/**
 *  @file     textualInterface.h
 *  @brief    Gestion comportemental de l'interface (En-tête)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.9
 *  @date     11/05/2015 - 12/06/2015
 */

#ifndef _QB50_TEXTUAL_INTERFACE_H_
#define _QB50_TEXTUAL_INTERFACE_H_

#include <string>

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

    } Container_state_t;

    class PageRepertory;
    class Page;
    class FIFO_InputKey;
    class OutputStreamChannel;

    /**
     *  @class    Container
     *  @brief    Gestion du comportement de l'interface utilisateur textuel
     *  @details  La class Container permet la gestion du comportement de l'interface utilisateur textuel
     *        Ce qui comprend:
     *        <ul>
     *          <li>L'affichage du cadre de l'interface ainsi que la localisation (nom de page en bas à gauche)</li>
     *          <li>La gestion des évenements (onLoad, onUnload, onUpdate, onKeyPress)</li>
     *          <li>La procédure de navigation entre les pages</li>
     *          <li>Les actions communes à toutes les pages comme le rafraîchissement de page</li>
     *        </ul>
     */
    class Container
    {

      public:

        Container(OutputStreamChannel& streamChannel, FIFO_InputKey& inputKey);

        ~Container();

        /// @brief Action de l'état courrant
        void action();

        /// @brief Transition d'état
        void transition();

        /// @brief Ajoute une touche dans la file d'attente
        void pushKey(unsigned char key);

        /// @brief Retroune l'état courrant
        Container_state_t getState();

        /// @brief Retroune le répertoire de pages
        PageRepertory& getRepertory( void );

        /// @brief Retroune le canal d'émission
        OutputStreamChannel& getStreamChannel( void );

        /// @brief Change la page suivante
        void setNextPage(Page* nextPageVal);

      private:
        /// @brief Page courrante
        Page* _currentPage;
        /// @brief Page suivante
        Page* _nextPage;

        /// @brief Répertoire de page
        PageRepertory* _pageRepertory;

        /// @brief Canal d'émission
        OutputStreamChannel& _streamChannel;

        /// @brief File d'attente des touches préssés
        FIFO_InputKey& _inputKey;

        /// @brief Action à l'état d'initialisation
        void _initialize();

        /// @brief Action à l'état chargement de la page courrante
        void _loadPage();

        /// @brief Action à l'état mise à jour de la page courrante
        void _updatePage();

        /// @brief Action à l'état déchargement de la page courrante
        void _unloadPage();

        /// @brief Action à l'état lecture des caractére reçus
        void _readKey();

        /// @brief Affiche la localisation dans l'interface
        void displayLocation();

        /// @brief Nettoye le contenu de l'écran (préserve le cadre)
        void clearContent();

        /// @brief Ecrit un séparateur dans la pied de page
        void writeSeparator(unsigned char line);

        /// @brief Ecrit le titre du cadre
        void writeTitle(const char* title);

        /// @brief Ecrit le cadre
        void writeBoxing();

        /// @brief Ecrit tous les raccoursis
        /// @param[in]  x: Position horizontal de 0 (à gauche) à XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH (à droite)
        /// @param[in]  y: Position vertical de 0 (en haut) à XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT (en bas)
        void writeShortcutKeys(unsigned char x, unsigned char y);

        /// @brief Etat de conteneur
        Container_state_t _state= initialize;

    };

  }


} /* namespace: qb50 */


#endif /* _QB50_TEXTUAL_INTERFACE_H_ */


/*EoF*/
