#include "Script.h"
#include <iostream>
#include <vector>
#include <Command.h>

Script::Script()
{
    //ctor
}

Script::~Script()
{
    //dtor
}
/*Initialization of a script by giving all the required informations */
Script::Script(int len, int startTime, int repeatTime, int nbreCmd/*, std::vector<Command> commands*/) : m_len(len), m_startTime(startTime), m_repeatTime(repeatTime)
{
    /*m_commands = commands; */
}

/* The idea of this method is to check if the Script created abide by KVD's rules.
For further informations, one can read the documentation provided by the KVD */
bool Script::checkScriptConformity()
{
    bool c_len = (m_len <= 254);
    bool c_startTime = (m_startTime <= (42949672965 -1)); // A revoir, nombre beaucoup trop grand!!
    bool c_repeatTime = (m_repeatTime <= (65536 - 1));
    bool c_nbreCmd = (m_nbreCmd <= 254);
    return (c_len & c_startTime & c_repeatTime & c_nbreCmd);
}

void Script::setLen(int len)
{
    m_len = len;
}

void Script::setStartTime(int startTime)
{
    m_startTime = startTime;
}

void Script::setRepeatTime(int repeatTime)
{
    m_repeatTime = repeatTime;
}

void Script::setNbreCmd(int nbreCmd)
{
    m_nbreCmd = nbreCmd;
}

void Script::setCommands(std::vector<Command> commands)
{
    m_commands = commands;//We may have to change it in the future, should we change the structure of commands (by giving the pointers instead of the commands).
}

int Script::getLen()
{
    return m_len;
}

int Script::getStartTime()
{
    return m_startTime;
}

int Script::getRepeatTime()
{
    return m_repeatTime;
}

int Script::getNbreCmd()
{
    return m_nbreCmd;
}

std::vector<Command> Script::getCommands()
{
    return m_commands;//We mau have to change it in the future, should we change the structure of commands (by giving the pointers instead of the commands).
}
