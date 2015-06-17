/**
 *  @file       escapeSequences.cpp
 *  @brief      ANSI escape codes (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       11/05/2015 - 15/05/2015
 */

#include "escapeSequences.h"


using namespace qb50;


//Define static variable
uint8_t escapeSequences::currentBackground = XTRUITES_DEFAULT_BACKGROUND;
uint8_t escapeSequences::currentForeground = XTRUITES_DEFAULT_FOREGROUND;
uint8_t escapeSequences::xHome= 1;
uint8_t escapeSequences::yHome= 1;


void escapeSequences::setHomePosition(uint8_t x, uint8_t y)
{
    escapeSequences::xHome= x;
    escapeSequences::yHome= y;
}


void escapeSequences::moveCursorHome()
{
    //                      Move cursor          yHome-1 (because \n)
    escapeSequences::write("\033[%d;%dH\n", escapeSequences::yHome-1, escapeSequences::xHome);
}


void escapeSequences::moveCursor(uint8_t x, uint8_t y)
{
    escapeSequences::write("\033[%d;%df", y+1, x+1);
}


void escapeSequences::clearScreen()
{
    escapeSequences::write("\033[2J\r\n");
}


void escapeSequences::setBackground(uint8_t color, bool force)
{
    if( (color != escapeSequences::currentBackground) || force)
    {
        escapeSequences::write("\033[48;5;%dm", color);
        escapeSequences::currentBackground = color;
    }
}


void escapeSequences::setForeground(uint8_t color, bool force)
{
    if( (color != escapeSequences::currentForeground) || force)
    {
        escapeSequences::write("\033[38;5;%dm", color);
        escapeSequences::currentForeground = color;
    }
}


void escapeSequences::reversesColors()
{
    uint8_t background= escapeSequences::currentBackground;
    escapeSequences::setBackground(escapeSequences::currentForeground);
    escapeSequences::setForeground(background);
}


void escapeSequences::erasesEntireCurrentLine()
{
    escapeSequences::write("\033[2K");
}


void escapeSequences::resetAttributes()
{
    escapeSequences::write("\033[0m");
}


void escapeSequences::scrollScreen(uint8_t startRow, uint8_t endRow)
{
    escapeSequences::write("\033[%d;%dr", startRow, endRow);
}


// Disable macro definitions of conditional printf
#undef printf
    int escapeSequences::write(const char *format , ...)
    {
        va_list vl;
        va_start(vl, format);
        int n= vprintf(format, vl);
        va_end(vl);
        return n;
    }
// Enable macro definitions of conditional printf
#define  printf     cpprintf


/*EoF*/
