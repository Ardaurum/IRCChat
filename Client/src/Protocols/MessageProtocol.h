#ifndef MESSAGE_PROTOCOL_H
#define MESSAGE_PROTOCOL_H

#include "Protocol.h"

#include <string>

class MessageProtocol : public Protocol
{
private:
    std::string sName;
    std::string sTime;
    std::string sContent;

    void init();

public:
    MessageProtocol(): sName(""), sContent("") { init(); };
    MessageProtocol(Id proto): Protocol(proto), sName(""), sContent("") { init(); };
    MessageProtocol(Id proto, std::string name, std::string content):
        Protocol(proto), sName(name), sContent(content) { init(); };
    MessageProtocol(Id proto, std::string name, std::string content, std::string time):
        Protocol(proto), sName(name), sTime(time), sContent(content) {};

    ~MessageProtocol() {};

    std::string pack();

    void setContent(std::string content) { sContent = content; };
    std::string getContent() { return sContent; };

    void setName(std::string name) { sName = name; };
    std::string getName() { return sName; };

    std::string getTime() { return sTime; };
};

#endif // MESSAGE_PROTOCOL_H
