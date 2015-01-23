#include "Room.h"
#include "protocols/ListProtocol.h"

#include <algorithm>

void Room::broadcast(Message msg)
{
    sem.lockReader();
    for (const auto &user : mUsers)
    {
        user.second->sendMsg(msg);
    }
    sem.unlockReader();
}

void Room::removeUser(IUser *user)
{
    removeUser(user->getName());
}

void Room::removeUser(std::string user)
{
    sem.lockWriter();
    mUsers.erase(user);
    sem.unlockWriter();

    sem.lockReader();
    int usersCount = mUsers.size();
    sem.unlockReader();

    if (usersCount == 0)
        emptyRoom = true;
    else
        sendUserList();
}

void Room::sendUserList()
{
    ListProtocol proto(USERSLIST);
    sem.lockReader();
    for (const auto &user : mUsers)
    {
        proto.addToList(user.first);
    }
    sem.unlockReader();

    Message msg;
    msg.packMsg(&proto);
    broadcast(msg);
}

void Room::addUser(IUser *user)
{
    sem.lockWriter();
    mUsers[user->getName()] = user;
    sem.unlockWriter();

    sendUserList();
}

std::string Room::getUserList()
{
    std::string users;
    sem.lockReader();
    for (const auto &user : mUsers)
    {
        std::string name = user.first;
        users += name + "\n";
    }
    sem.unlockReader();
    return users;
}
