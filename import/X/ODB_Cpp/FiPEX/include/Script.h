#ifndef SCRIPT_H
#define SCRIPT_H
#include <iostream>
#include <vector>
#include <Command.h>

/*! The OBC shall contain scripts. It can implement up to 7 scripts in memory. Each of those scripts are instances of
*this very class. For the accurate definition of the way scripts are encrypted, one can refer to the specifications given by
*the VKI */

class Script
{
    public:
        Script();
        virtual ~Script();
        Script(int len, int starTime, int repeatTime, int nbreCmd/*, std::vector<Command> commands*/);
        bool checkScriptConformity();// We check whether the element is actually a script.
        void setLen(int len);
        void setStartTime(int StartTime);
        void setRepeatTime(int repeatTime);
        void setNbreCmd(int NbreCmd);
        void setCommands(std::vector<Command> commands);
        int getLen();
        int getStartTime();
        int getRepeatTime();
        int getNbreCmd();
        std::vector<Command> getCommands();

    protected:

    private:
        int m_len, m_startTime, m_repeatTime, m_nbreCmd;
        std::vector<Command> m_commands; // We rely on the Commands structure. We see a Script as a set of Commands

};

#endif // SCRIPT_H
