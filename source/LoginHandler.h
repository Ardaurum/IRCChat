#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "IRCManager.h"
#include "Message.h"
#include "User.h"

class LoginHandler
{
private:
    IRCManager *ircManager;
    int sck;

    std::vector<pthread_t*> vThreads;

    static void *startUser(void *user);

public:
    LoginHandler(IRCManager *manager): ircManager(manager) {};
    bool configureSck();
    void run();
    void createUser(int clnsck);
};

#endif // LOGINHANDLER_H
