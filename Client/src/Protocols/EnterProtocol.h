#ifndef ENTER_PROTOCOL_H
#define ENTER_PROTOCOL_H

#include "Protocol.h"

#include <string>

class EnterProtocol : public Protocol
{
private:
    std::string sName;
    std::string sPass;

public:
    EnterProtocol(): sName(""), sPass("") {};
    EnterProtocol(Id proto): Protocol(proto), sName(""), sPass("") {};
    EnterProtocol(Id proto, std::string name): Protocol(proto), sName(name), sPass("") {};
    EnterProtocol(Id proto, std::string name, std::string pass): Protocol(proto), sName(name), sPass(pass) {};

    std::string pack();

    void setName(std::string name) { sName = name; };
    std::string getName() { return sName; };

    void setPassword(std::string pass) { sPass = pass; };
    std::string getPassword() { return sPass; };
};

#endif // ENTER_PROTOCOL_H
