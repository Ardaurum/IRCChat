#include "EnterProtocol.h"

std::string EnterProtocol::pack()
{
    std::string res;
    res = Protocol::pack();
    res += '~' + sName;
    if (sPass != "") res += '~' + sPass;
    return res;
}
