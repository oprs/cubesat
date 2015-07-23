/**
 *  @file     FlashLabel.cpp
 *  @brief    Component à redéfinir destinée à l'afficher une liste de labels (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "../../Component/Color.h"
#include "FlashLabel.h"

using namespace qb50::XTRUITES;

FlashLabel::FlashLabel(uint8_t sizeListLabelVal) : _sizeListLabel(sizeListLabelVal)
{
}

void FlashLabel::onLoad( void )
{
    for(unsigned char number=0; number < _sizeListLabel; number++)
    {
        writeLabel( number, getColor());
    }
}


void FlashLabel::select( uint8_t number )
{
    if(_currentNumber != number || (_currentNumber == number && !_currentIsSelected))
    {
        deselect();
        Color color= getColor();

        color.invert();
        writeLabel( number, color);

        _currentNumber= number;
        _currentIsSelected= true;
    }

}

void FlashLabel::deselect( void )
{
    if(_currentIsSelected)
    {
        writeLabel( _currentNumber, getColor());
        _currentIsSelected= false;
    }
}

/*EoF*/
