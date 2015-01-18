#include "Message.h"
#include "StandardProtocol.h"
#include "EnterProtocol.h"
#include "ListProtocol.h"
#include "MessageProtocol.h"
#include "ErrorProtocol.h"

#include <string.h>
#include <algorithm>

std::vector<char*> Message::splitMsg()
{
    char *temp;
    std::vector<char*> res;
    temp = strtok(buffer, "~");
    while(temp != NULL)
    {
        res.push_back(temp);
        temp = strtok(NULL, "~");
    }
    return res;
}

Id Message::getMsgId(char *msg)
{
    long val;
    char *temp;
    Id id;
    val = strtol(msg, &temp, 0);

    if (*temp != '\0')
    {
        printf("Wrong message identificator!\n");
        id = OTHER;
    }
    else
        id = static_cast<Id>(val);

    return id;
}

int Message::getMsgInt(char *msg)
{
    int i = atoi(msg);
    return i;
}

std::string Message::getMsgString(char *msg)
{
    std::string res = msg;
    return res;
}

void Message::clearBuffer()
{
    std::fill(std::begin(buffer), std::begin(buffer) + sizeof(buffer), 0);
}

char *Message::packMsg(Protocol *proto)
{
    std::string temp = proto->pack().c_str();
    temp += "~\n";
    strcpy(buffer, temp.c_str());
    return buffer;
}

Protocol *Message::unpackMsg()
{
    std::vector<char*> argv = splitMsg();
    argv.pop_back();
    Id id = getMsgId(argv[0]);
    Protocol *proto = NULL;

    switch(id)
    {
    case LOGIN:
    case CREATE:
    case JOIN:
        if (argv.size() < 2) return NULL;
        proto = new EnterProtocol(id, getMsgString(argv[1]));
        break;

    case LOGOFF:
    case LEAVE:
    case ACK:
        proto = new Protocol(id);
        break;

    case SEND:
        if (argv.size() < 2) return NULL;
        proto = new StandardProtocol(id, getMsgString(argv[1]));
        break;

    case ERROR:
        if (argv.size() < 3) return NULL;
        proto = new ErrorProtocol(id, getMsgInt(argv[1]), getMsgString(argv[2]));
        break;

    case ROOMSLIST:
    case USERSLIST:
        {
            if (argv.size() < 1) return NULL;

            std::vector<std::string> vList;
            for (unsigned int i = 1; i < argv.size(); i++)
            {
                vList.push_back(getMsgString(argv[i]));
            }
            proto = new ListProtocol(id, vList);
            break;
        }

    case MSG:
        if (argv.size() < 4) return NULL;
        proto = new MessageProtocol(id, getMsgString(argv[1]),
                                    getMsgString(argv[3]), getMsgString(argv[2]));
        break;

    case OTHER:
        return NULL;
        break;
    }

    return proto;
}
