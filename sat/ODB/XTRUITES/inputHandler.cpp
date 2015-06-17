/**
 *  @file       inputHandler.cpp
 *  @brief      Gestion des touches de XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       11/05/2015 - 12/06/2015
 */

#include "inputHandler.h"


using namespace qb50;
using namespace std;


XTRUITESInputHandler::XTRUITESInputHandler(uint8_t _keyVal, std::function<void ()> _handlerVal)
{
    _key= _keyVal;
    _handler= _handlerVal;
}


XTRUITESInputHandler& XTRUITESInputHandler::setHandler(std::function<void ()> _handlerVal)
{
    _handler= _handlerVal;
    return *this;
}


XTRUITESInputHandler& XTRUITESInputHandler::setKey(uint8_t _keyVal)
{
    _key= _keyVal;
    return *this;
}


uint8_t XTRUITESInputHandler::getKey()
{
    return _key;
}


XTRUITESInputHandler& XTRUITESInputHandler::launch()
{
    _handler();
    return *this;
}


/*EoF*/
