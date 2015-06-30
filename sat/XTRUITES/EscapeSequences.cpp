/**
 *  @file       EscapeSequences.cpp
 *  @brief      ANSI escape codes (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       11/05/2015 - 15/05/2015
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "XTRUITES.h"
#include "EscapeSequences.h"
#include "OutputStream/OutputStream.h"
#include "OutputStream/OutputStreamChannel.h"


using namespace qb50::XTRUITES;


//Define static variable
uint8_t EscapeSequences::currentBackground = XTRUITES_DEFAULT_BACKGROUND;
uint8_t EscapeSequences::currentForeground = XTRUITES_DEFAULT_FOREGROUND;
uint8_t EscapeSequences::xHome= 1;
uint8_t EscapeSequences::yHome= 1;


void EscapeSequences::setHomePosition(uint8_t x, uint8_t y)
{
    EscapeSequences::xHome= x;
    EscapeSequences::yHome= y;
}


void EscapeSequences::moveCursorHome()
{
    //                      Move cursor          yHome-1 (because \n)
    EscapeSequences::write("\033[%d;%dH\n", EscapeSequences::yHome-1, EscapeSequences::xHome);
}

void EscapeSequences::moveCursor(Point* cursor)
{
    EscapeSequences::moveCursor(cursor->getX(), cursor->getY());
}

void EscapeSequences::moveCursor(uint8_t x, uint8_t y)
{
    EscapeSequences::write("\033[%d;%df", y+1, x+1);
}


void EscapeSequences::clearScreen()
{
    EscapeSequences::write("\033[2J\r\n");
}


void EscapeSequences::setBackground(uint8_t color, bool force)
{
    if( (color != EscapeSequences::currentBackground) || force)
    {
        EscapeSequences::write("\033[48;5;%dm", color);
        EscapeSequences::currentBackground = color;
    }
}


void EscapeSequences::setForeground(uint8_t color, bool force)
{
    if( (color != EscapeSequences::currentForeground) || force)
    {
        EscapeSequences::write("\033[38;5;%dm", color);
        EscapeSequences::currentForeground = color;
    }
}


void EscapeSequences::reversesColors()
{
    uint8_t background= EscapeSequences::currentBackground;
    EscapeSequences::setBackground(EscapeSequences::currentForeground);
    EscapeSequences::setForeground(background);
}


void EscapeSequences::erasesEntireCurrentLine()
{
    EscapeSequences::write("\033[2K");
}


void EscapeSequences::resetAttributes()
{
    EscapeSequences::write("\033[0m");
}


void EscapeSequences::scrollScreen(uint8_t startRow, uint8_t endRow)
{
    EscapeSequences::write("\033[%d;%dr", startRow, endRow);
}


int EscapeSequences::write(const char *format , ...)
{
    // Je n'ai pas trouvé mieux pour récuperer la taille total
    va_list args;
    va_start(args, format);
    int n= vsprintf (nullptr,format, args);
    va_end(args);

    // Allocation de mémoire
    char* buffer = (char*) malloc (sizeof(char) * n);

    va_start(args, format);
    n= vsprintf (buffer,format, args);
    va_end(args);

    OutputStreamUART3.getChannelByName("UART3_XTRUITES")->write( buffer, n);

    free(buffer);
    buffer = nullptr;

    return n;
}

void EscapeSequences::setColor(Color* color, bool force)
{
    setBackground(color->background, force);
    setForeground(color->foreground, force);
}

/*EoF*/
