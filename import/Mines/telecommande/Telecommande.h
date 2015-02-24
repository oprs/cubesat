#ifndef TELECOMMANDE_H
#define TELECOMMANDE_H

class Telecommande
{
	public:
        Telecommande();
        virtual ~Telecommande();
        Telecommande(string messageAX25)
        bool checkReceiver()

    private:
        int receiveTime;
        string sender;
        string receiver;
        string typeCmd;
        string fstParameter;
        string scdParameter;
};
