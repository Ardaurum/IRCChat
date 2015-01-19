#ifndef ROOM_H
#define ROOM_H

#include "IRoom.h"
#include "IUser.h"

#include <vector>

class Room : public IRoom
{
private:
    WRSem sem;

public:
    Room(std::string name): IRoom(name) {};

    void broadcast(Message msg);
    void removeUser(IUser *user);
    void removeUser(std::string user);

    void addUser(IUser *user);
    void sendUserList();
    std::string getUserList();
};

#endif // ROOM_H
