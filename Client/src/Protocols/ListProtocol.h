#ifndef LIST_PROTOCOL_H
#define LIST_PROTOCOL_H

#include "Protocol.h"

#include <vector>
#include <string>

class ListProtocol : public Protocol
{
private:
    std::vector<std::string> vList;

public:
    ListProtocol() {};
    ListProtocol(Id id): Protocol(id) {};
    ListProtocol(Id id, std::vector<std::string> vec): Protocol(id), vList(vec) {};

    ~ListProtocol() { vList.clear(); };

    std::string pack();

    void addToList(std::string val) { vList.push_back(val); };
    std::string getList(int x) {
        if(x < 0 || x >= (int) vList.size())
            return NULL;
        else
            return vList[x];
    };
    int getSize() { return vList.size(); };
};

#endif // LIST_PROTOCOL_H
