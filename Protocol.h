#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

//PROTOCOL IDs
enum Id { LOGIN, LOGOFF, CREATE, JOIN, LEAVE, SEND,
    ERROR, ACK, ROOMSLIST, MSG, USERSLIST, OTHER };

class Protocol
{
private:
    Id id;

public:
    Protocol(): id(OTHER) {};
    Protocol(Id proto): id (proto) {};

    virtual ~Protocol() {};

    virtual std::string pack();

    void setId (Id proto) { id = proto; };
    Id getId() { return id; };
};

#endif // PROTOCOL_H
