#include "Protocol.h"

std::string Protocol::pack()
{
    std::string res;
    int proto = static_cast<int>(id);
    res = std::to_string(proto);
    return res;
}
