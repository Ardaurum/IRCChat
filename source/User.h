#ifndef USER_H
#define USER_H

#include "IUser.h"
#include "IRCManager.h"
#include "IRoom.h"
#include "protocols/Protocol.h"
#include "protocols/ListProtocol.h"
#include "protocols/ErrorProtocol.h"
#include "Message.h"

class User : public IUser
{
private:
    IRCManager *ircManager;

    void login(Protocol *ptr);
    void createRoom(Protocol *ptr);
    void joinRoom(Protocol *ptr);
    void logoff();
    void leave();
    void broadcast(Protocol *ptr);
    void parseError(Protocol *ptr);

    void sendRoomsList();
    void sendUsersList();
    void parseToList(ListProtocol &proto, std::string from);

public:
    User(int sck, IRCManager *manager): IUser(sck), ircManager(manager) {};
    ~User();

    void run();

    void sendMsg(Message msg);
    void sendError(ErrorType err, std::string content);
    void sendAck();
};

#endif // USER_H
