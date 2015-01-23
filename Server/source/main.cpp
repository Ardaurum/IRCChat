#include "IRCManager.h"
#include "LoginHandler.h"

#include <iostream>
#include <string>
#include <string.h>
#include <pthread.h>
#include <limits.h>

using namespace std;

void *createLoginHandler(void *manager);

int main(int argc, char *argv[])
{
    pthread_t threadLogin;
    std::string command = "";
    std::string temp = "";
    long port = -1;

    printf("Welcome to simple IRC Server application!\n");
    IRCManager ircManager;

    printf("Configuring server.\n");
    printf("Please enter ip of the server:\n");
    printf("(enter 0 to use standard ip: 127.0.0.1)\n");
    do {
        cin >> temp;
        if (cin.good() && temp != "0" && ircManager.validateIp(temp))
        {
            ircManager.server = temp;
            break;
        }
        else if (temp != "0")
        {
            printf("Wrong ip!\n");
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (temp != "0");

    printf("Please enter port to use:\n");
    printf("(enter 0 to use standard port: 6667)\n");
    do {
        char *check;
        cin >> temp;
        port = strtol(temp.c_str(), &check, 10);
        if (*check == 0 && temp != "0" && port >= SHRT_MIN && port <= SHRT_MAX)
        {
            ircManager.service_port = port;
            break;
        }
        else if (temp != "0")
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            printf("Wrong port!\n");
            port = -1;
        }
    } while (temp != "0");

    if (pthread_create(&threadLogin, NULL, createLoginHandler, (void *) &ircManager) < 0)
    {
        perror("Cannot create thread!");
        return -1;
    }

    do
    {
        cin >> command;
        if (cin.bad())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        if (command == "-q")
            ircManager.closeServer();
        else if (command == "-u")
        {
            printf("Users list:\n");
            printf("%s", ircManager.getUserList().c_str());
        }
        else if (command == "-r")
        {
            printf("Rooms list:\n");
            printf("%s", ircManager.getRoomList().c_str());
        }
        else if (command == "-ur")
        {
            std::string roomName;
            cin >> roomName;
            printf("Rooms list for room %s:\n", roomName.c_str());
            printf("%s", ircManager.getUsersFromRoom(roomName).c_str());
        }
        else if (command == "-k")
        {
            std::string userName;
            cin >> userName;
            ircManager.removeUserFromRoom(userName);
        }
        else if (command == "-b")
        {
            std::string userName;
            cin >> userName;
            ircManager.removeUser(userName);
        }
        else
        {
            printf("Incorrect command!\n");
        }
    } while(!ircManager.serverClosed());

    printf("Wait for server to close.\n");
    pthread_join(threadLogin, NULL);

    printf("Goodbye\n");
    return 0;
}

void *createLoginHandler(void *manager)
{
    IRCManager *ircManager = (IRCManager*)manager;
    LoginHandler loginHandler(ircManager);
    if (loginHandler.configureSck())
    {
        loginHandler.run();
    }
    pthread_exit(0);
}
