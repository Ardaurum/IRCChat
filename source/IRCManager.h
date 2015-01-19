#ifndef IRCMANAGER_H
#define IRCMANAGER_H

#include "Room.h"
#include "User.h"

#include <unordered_map>
#include <string>
#include <pthread.h>

class IRCManager
{
private:
    std::unordered_map<std::string, IRoom*> mRooms;
    std::unordered_map<std::string, IUser*> mUsers;
    bool bDone;

    WRSem userSem;
    WRSem roomSem;

public:
    std::string server = "127.0.0.1";
    short service_port = 6667;

    IRCManager(): bDone(false) {};
    void closeServer() { bDone = true; }
    bool serverClosed() { return bDone; }

    bool addUser(IUser *user);
    void removeUserFromRoom(IUser *user);
    void removeUserFromRoom(std::string user);
    void removeUser(IUser *user);
    void removeUser(std::string user);

    void broadcast(Message msg);
    void broadcastInRoom(Message msg, std::string name);

    std::string createRoom(std::string name);
    void removeRoom(std::string name);
    void removeRoom(IRoom *room);
    std::string addUserToRoom(IUser *user, std::string name);

    void sendRoomList(IUser *user = NULL);

    std::string getUserList();
    std::string getRoomList();
    std::string getUsersFromRoom(std::string name);

    bool validateIp(const std::string &ip);
};

#endif // IRCMANAGER_H
