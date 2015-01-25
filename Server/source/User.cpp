#include "User.h"
#include "protocols/EnterProtocol.h"
#include "protocols/StandardProtocol.h"
#include "protocols/MessageProtocol.h"

#include <string.h>
#include <sstream>

User::~User()
{
    ircManager->removeUser(this);
    close(iSck);
}

void User::run()
{
    int received;
    Message msg;
    while (!ircManager->serverClosed() && exists)
    {
        if ((received = read(iSck, msg.getBuffer(), MAXSIZE)) > 0)
        {
            Protocol *temp = msg.unpackMsg();
            if (temp == NULL)
            {
                sendError(WRONGMSG, "Wrong message protocol!");
                continue;
            }

            switch(temp->getId())
            {
            case LOGIN:
                login(temp);
                break;

            case CREATE:
                createRoom(temp);
                break;

            case JOIN:
                joinRoom(temp);
                break;

            case LOGOFF:
                logoff();
                break;

            case LEAVE:
                leave();
                break;

            case SEND:
                broadcast(temp);
                break;

            case ERROR:
                parseError(temp);
                break;

            default:
                sendError(WRONGMSG, "Wrong message!");
                printf("Wrong message!\n");
                break;
            }

            delete temp;
            msg.clearBuffer();
        }

        if (received == 0)
        {
            logoff();
        }
    }

    if (exists)
        logoff();
}

void User::login(Protocol *ptr)
{
    EnterProtocol *proto = dynamic_cast<EnterProtocol*>(ptr);
    sName = proto->getName();
    if (!ircManager->addUser(this))
    {
        sendError(LOGINUSER, "User name already in use!");
        sName = "";
    }
}

void User::createRoom(Protocol *ptr)
{
    if (sName == "")
    {
        sendError(NOTLOGGED, "User is not logged in!");
        return;
    }

    EnterProtocol *proto = dynamic_cast<EnterProtocol*>(ptr);
    room = ircManager->createRoom(proto->getName());
    if (room == "")
        sendError(CREATEROOM, "Couldn't create room! Room name already in use!");
    else
        ircManager->addUserToRoom(this, room);
}

void User::joinRoom(Protocol *ptr)
{
    if (sName == "")
    {
        sendError(NOTLOGGED, "User is not logged in!");
        return;
    }

    EnterProtocol *proto = dynamic_cast<EnterProtocol*>(ptr);
    room = ircManager->addUserToRoom(this, proto->getName());
    if (room == "")
        sendError(JOINROOM, "Room doesn't exist!");
}

void User::logoff()
{
    exists = false;
}

void User::leave()
{
    if (room != "")
    {
        ircManager->removeUserFromRoom(this);
        room = "";
    }
}

void User::broadcast(Protocol *ptr)
{
    if (sName == "")
    {
        sendError(NOTLOGGED, "User is not logged in!");
        return;
    }
    if (room == "")
        sendError(NOROOM, "User is not in a room!");

    StandardProtocol *proto = dynamic_cast<StandardProtocol*>(ptr);
    MessageProtocol msgProto(MSG, sName, proto->getContent());
    Message msg;
    msg.packMsg(&msgProto);
    ircManager->broadcastInRoom(msg, room);
}

void User::parseError(Protocol *ptr)
{
    ErrorProtocol *proto = dynamic_cast<ErrorProtocol*>(ptr);
    printf("User %s send an error message: %s\n", sName.c_str(), proto->getText().c_str());
}

void User::sendMsg(Message msg)
{
    if (write(iSck, msg.getBuffer(), strlen(msg.getBuffer())) < 0)
    {
        perror("Cannot write to user!");
        printf("Cannot write to user nick: %s, on port: %d.\n", sName.c_str(), iSck);
    }
    msg.clearBuffer();
}

void User::sendError(ErrorType err, std::string content)
{
    ErrorProtocol proto(ERROR, err, content);
    Message msg;
    msg.packMsg(&proto);
    sendMsg(msg);
}

void User::sendAck()
{
    Protocol proto(ACK);
    Message msg;
    msg.packMsg(&proto);
    sendMsg(msg);
}
