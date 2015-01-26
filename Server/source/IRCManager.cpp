#include "IRCManager.h"
#include "protocols/ListProtocol.h"

#include <algorithm>
#include <arpa/inet.h>

bool IRCManager::addUser(IUser *user)
{
    userSem.lockWriter();
    if (mUsers.find(user->getName()) == mUsers.end())
    {
        mUsers[user->getName()] = user;
        userSem.unlockWriter();
        user->sendAck();
        sendRoomList(user);

        printf("User %s has joined the server.\n", user->getName().c_str());
        return true;
    }
    userSem.unlockWriter();

    return false;
}

void IRCManager::removeUserFromRoom(IUser *user)
{
    if (!user->inRoom()) return;
    roomSem.lockWriter();
    std::unordered_map<std::string, IRoom*>::iterator it = mRooms.find(user->getRoom());

    if (it != mRooms.end())
    {
        IRoom *room = it->second;

        room->removeUser(user);
        printf("User %s has been removed from room %s.\n",
               user->getName().c_str(), room->getName().c_str());

        roomSem.unlockWriter();

        if (user->isAlive())
            user->sendAck();

        if (room->isEmpty())
        {
            removeRoom(room);
        } else {
        	if (user->isAlive())
        	{
            	user->sendAck();
            	sendRoomList(user);
        	}
        }
    } else {
        roomSem.unlockWriter();
    }
}

void IRCManager::removeUserFromRoom(std::string user)
{
    userSem.lockReader();
    std::unordered_map<std::string, IUser*>::iterator it = mUsers.find(user);
    userSem.unlockReader();
    if (it != mUsers.end())
    {
        IUser *user = it->second;
        removeUserFromRoom(user);
        if (user->isAlive())
        {
            sendRoomList(user);
        }
    }
}

void IRCManager::removeUser(IUser *user)
{
    if (user->inRoom())
        removeUserFromRoom(user);

    userSem.lockWriter();
    int rs = mUsers.erase(user->getName());
    if (rs > 0)
    {
        user->kill();
        printf("User %s has been removed (quantity: %d).\n", user->getName().c_str(), rs);
    }
    userSem.unlockWriter();
}

void IRCManager::removeUser(std::string user)
{
    userSem.lockReader();
    std::unordered_map<std::string, IUser*>::iterator it = mUsers.find(user);
    userSem.unlockReader();
    if (it != mUsers.end())
    {
        removeUser(it->second);
    }
}

std::string IRCManager::createRoom(std::string name)
{
    roomSem.lockWriter();
    if (mRooms.find(name) == mRooms.end())
    {
        IRoom *room = new Room(name);
        mRooms[name] = room;
        roomSem.unlockWriter();

        printf("Created room: %s.\n", name.c_str());
        sendRoomList();
        return name;
    }
    roomSem.unlockWriter();

    return "";
}

std::string IRCManager::addUserToRoom(IUser *user, std::string name)
{
    roomSem.lockWriter();
    std::unordered_map<std::string, IRoom*>::iterator it = mRooms.find(name);

    if (it != mRooms.end())
    {
        IRoom *room = it->second;
        user->sendAck();
        room->addUser(user);
        roomSem.unlockWriter();

        printf("User %s joined a room %s.\n", user->getName().c_str(), name.c_str());
        return name;
    }
    roomSem.unlockWriter();

    return "";
}

void IRCManager::removeRoom(std::string name)
{
    roomSem.lockWriter();
    std::unordered_map<std::string, IRoom*>::iterator room = mRooms.find(name);

    if (room != mRooms.end())
    {
        delete room->second;
        mRooms.erase(room);
        printf("Room %s has been removed.\n", name.c_str());
    }
    roomSem.unlockWriter();

    sendRoomList();
}

void IRCManager::removeRoom(IRoom *room)
{
    roomSem.lockWriter();
    mRooms.erase(room->getName());
    roomSem.unlockWriter();
    printf("Room %s has been removed.\n", room->getName().c_str());

    delete room;

    sendRoomList();
}

void IRCManager::broadcast(Message msg)
{
    userSem.lockReader();
    for (const auto &us : mUsers)
    {
        if (!us.second->inRoom())
            us.second->sendMsg(msg);
    }
    userSem.unlockReader();
}

void IRCManager::broadcastInRoom(Message msg, std::string name)
{
    roomSem.lockReader();
    std::unordered_map<std::string, IRoom*>::iterator it = mRooms.find(name);

    if (it != mRooms.end())
    {
        IRoom *room = it->second;
        room->broadcast(msg);
    }
    roomSem.unlockReader();
}

void IRCManager::sendRoomList(IUser *user)
{
    ListProtocol proto(ROOMSLIST);
    roomSem.lockReader();
    for (const auto &room : mRooms)
    {
        proto.addToList(room.first);
    }
    roomSem.unlockReader();

    Message msg;
    msg.packMsg(&proto);
    if (user == NULL)
        broadcast(msg);
    else
        user->sendMsg(msg);
}

std::string IRCManager::getUserList()
{
    userSem.lockReader();
    std::string users = "";
    for (const auto &user : mUsers)
    {
        std::string name = user.first;
        users += name + "\n";
    }
    userSem.unlockReader();
    return users;
}

std::string IRCManager::getUsersFromRoom(std::string name)
{
    std::string users;

    roomSem.lockReader();
    std::unordered_map<std::string, IRoom*>::iterator it = mRooms.find(name);
    if (it != mRooms.end())
    {
        IRoom *room = it->second;

        users = "";
        users = room->getUserList();
    }
    roomSem.unlockReader();
    return users;
}

std::string IRCManager::getRoomList()
{
    std::string rooms = "";
    for (const auto &room : mRooms)
    {
        std::string name = room.first;
        rooms += name + "\n";
    }
    return rooms;
}

bool IRCManager::validateIp(const std::string &ip)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
    return result != 0;
}
