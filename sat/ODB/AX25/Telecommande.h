#ifndef TELECOMMANDE_H
#define TELECOMMANDE_H

#include <stdlib.h>

namespace qb50 {

    class Telecommande
    {
        public:
            Telecommande();
            virtual ~Telecommande();
            bool checkSender();
            bool checkReceiver();
            bool checkCmd();
            bool checkWorth();
            int giveReceiveTime();
            int getReceiveTime();
            char* getSender();
            char* getReceiver();
            char* getTypeCmd();
            char* getFstParameter();
            char* getScdParameter();
            void read(char* x);
            void charToTelecommande();

        private:
            int receiveTime;
            char sender[5];
            char receiver[9];
            char typeCmd[3];
            char fstParameter[3];
            char scdParameter[3];
            size_t buf;
            char* adresseReference;
    };
}
#endif
