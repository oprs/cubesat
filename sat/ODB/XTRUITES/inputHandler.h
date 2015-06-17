/**
 *  @file       inputHandler.h
 *  @brief      Gestion des touches de XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       11/05/2015 - 12/06/2015
 */

#ifndef _QB50_INPUT_HANDLER_H_
#define _QB50_INPUT_HANDLER_H_


#include "textualInterface.h"


namespace qb50
{


    /// @class      XTRUITESInputHandler
    /// @brief      Gestion des touches: permet de créer une liaison entre une touche du clavier et une lambda fonction
    class XTRUITESInputHandler
    {


        public:

            /**
             *  @brief      Constructeur: initialise en liant une touche à une lamda function
             *  @param[in]  _keyVal: Touche du clavier cible
             *  @param[in]  _handlerVal: Action appellé (lambda function)
             */
            XTRUITESInputHandler(uint8_t _keyVal, std::function<void()> _handlerVal);

            /// @brief  Setter touche
            XTRUITESInputHandler& setKey(uint8_t _keyVal);

            /// @brief  Getter touche
            uint8_t getKey();

            /**
             *  @brief Ecriture Handler
             *  @param[in] _handlerVal: Action à appeller (lambda function)
             *  @return    Reference XTRUITESInputHandler courrante
             */
            XTRUITESInputHandler& setHandler(std::function<void()> _handlerVal);

            /// @brief  Appelle le handler
            /// @return Reference XTRUITESInputHandler courrante
            XTRUITESInputHandler& launch();

        private:

            /// @brief  Touche cible
            uint8_t _key;

            /// @brief  Action (lambda function)
            std::function<void()> _handler;


    };


} /* namespace: qb50 */


#endif /* _QB50_INPUT_HANDLER_H_ */


/*EoF*/
