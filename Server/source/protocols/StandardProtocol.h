#ifndef STANDARD_PROTOCOL_H
#define STANDARD_PROTOCOL_H

#include "Protocol.h"

class StandardProtocol : public Protocol
{
private:
    std::string sContent;

public:
    StandardProtocol(): sContent("") {};
    StandardProtocol(Id proto): Protocol(proto), sContent("") {};
    StandardProtocol(Id proto, std::string content):
        Protocol(proto), sContent(content) {};

    ~StandardProtocol() {};

    std::string pack();

    void setContent(std::string content) { sContent = content; };
    std::string getContent() { return sContent; };
};

#endif // STANDARD_PROTOCOL_H
