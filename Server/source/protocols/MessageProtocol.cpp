#include "MessageProtocol.h"

#include <time.h>
#include <sys/time.h>

void MessageProtocol::init()
{
    struct timeval tv;
    time_t nowtime;
    struct tm *nowtm;
    char buf[64];

    gettimeofday(&tv, NULL);
    nowtime = tv.tv_sec;
    nowtm = localtime(&nowtime);
    strftime(buf, sizeof(buf), "%H:%M", nowtm);

    sTime = buf;
}

std::string MessageProtocol::pack()
{
    std::string res;
    res = Protocol::pack();
    res += '~' + sName;
    res += '~' + sTime;
    res += '~' + sContent;
    return res;
}
