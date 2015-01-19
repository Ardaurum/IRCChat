#include "ErrorProtocol.h"

std::string ErrorProtocol::pack()
{
    std::string res;
    res = Protocol::pack();
    int err = static_cast<int>(error);
    res += '~' + std::to_string(err);
    res += '~' + sText;
    return res;
}

