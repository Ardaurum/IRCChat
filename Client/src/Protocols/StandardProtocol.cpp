#include "StandardProtocol.h"

std::string StandardProtocol::pack()
{
    std::string res;
    res = Protocol::pack();
    res += '~' + sContent;
    return res;
}
