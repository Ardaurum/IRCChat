#ifndef IROOM_H
#define IROOM_H

#include "Message.h"
#include "IUser.h"
#include "WRSem.h"

#include <string>
#include <unistd.h>
#include <unordered_map>

class IRoom
{
protected:
    std::string sName;
    std::unordered_map<std::string, IUser*> mUsers;
    bool emptyRoom;

public:
    IRoom(std::string name): sName(name), emptyRoom(false) {};

    virtual ~IRoom() {};

    virtual void broadcast(Message msg) = 0;
    virtual void removeUser(IUser *user) = 0;

    std::string getName() { return sName; };

    virtual void addUser(IUser *user) = 0;

    virtual void sendUserList() = 0;
    virtual std::string getUserList() = 0;

    bool isEmpty() { return emptyRoom; };
};

#endif // IROOM_H
