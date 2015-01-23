#ifndef ERROR_PROTOCOL_H
#define ERROR_PROTOCOL_H

#include "Protocol.h"

#include <string>

//Error types
enum ErrorType { LOGINUSER, CREATEROOM, JOINROOM, WRONGMSG, NOTLOGGED, NOROOM };

class ErrorProtocol : public Protocol
{
private:
    ErrorType error;
    std::string sText;

public:
    ErrorProtocol(): sText("") {};
    ErrorProtocol(Id proto): Protocol(proto), sText("") {};
    ErrorProtocol(Id proto, int err, std::string text): Protocol(proto), sText(text) { error = static_cast<ErrorType>(err); };

    std::string pack();

    void setError(ErrorType err) { error = err; };
    ErrorType getError() { return error; };

    void setText(std::string text) { sText = text; };
    std::string getText() { return sText; };
};

#endif // ERROR_PROTOCOL_H
