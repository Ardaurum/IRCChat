#include "ListProtocol.h"

std::string ListProtocol::pack()
{
    std::string res;
    res = Protocol::pack();

    for (std::string &val : vList)
    {
        res += '~' + val;
    }

    return res;
}
