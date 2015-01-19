#ifndef MESSAGE_H
#define MESSAGE_H

#include "protocols/Protocol.h"

#include <vector>

#define MAXSIZE 1024

class Message
{
private:
    char buffer[MAXSIZE];

    std::vector<char*> splitMsg();
    Id getMsgId(char *msg);
    int getMsgInt(char *msg);
    std::string getMsgString(char *msg);

public:
    char *packMsg(Protocol *proto);
    Protocol *unpackMsg();

    char *getBuffer() { return buffer; };
    void clearBuffer();
};

#endif // MESSAGE_H
