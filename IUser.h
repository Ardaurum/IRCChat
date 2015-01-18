#ifndef IUSER_H
#define IUSER_H

#include "Message.h"
#include "ErrorProtocol.h"

#include <string>
#include <unistd.h>

class IRCManager;
class Room;

class IUser
{
protected:
    std::string sName;
    std::string room;
    int iSck;

    bool exists;

    clock_t lastAlive;

public:
    IUser(int sck): room(""), iSck(sck), exists(true) {};

    virtual ~IUser() {};

    virtual void run() = 0;

    virtual void sendMsg(Message msg) = 0;
    virtual void sendError(ErrorType err, std::string content) = 0;
    virtual void sendAck() = 0;

    void setName(std::string name) { sName = name; };
    std::string getName() { return sName; };

    bool inRoom() { return room != ""; };

    int getSck() { return iSck; };
};

#endif // IUSER_H
