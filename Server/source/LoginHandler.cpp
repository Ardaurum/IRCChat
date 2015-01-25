#include "LoginHandler.h"
#include "Message.h"

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

bool LoginHandler::configureSck()
{
    struct sockaddr_in sck_addr;

    bzero(&sck_addr, sizeof(sck_addr));
    sck_addr.sin_family = AF_INET;
    inet_aton(ircManager->server.c_str(), &sck_addr.sin_addr);
    sck_addr.sin_port = htons(ircManager->service_port);

    if ((sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Cannot configure socket for login handler!");
        ircManager->closeServer();
        return false;
    }

    int opt = 1;
    setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(sck, (struct sockaddr*) &sck_addr, sizeof(sck_addr)) < 0)
    {
        perror("Cannot bind socket!");
        ircManager->closeServer();
        return false;
    }

    if (listen(sck, 64) < 0)
    {
        perror("Cannot listen!");
        ircManager->closeServer();
        return false;
    }

    if (fcntl(sck, F_SETFL, fcntl(sck, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        perror("Cannot change the socket to non-blocking mode!");
        ircManager->closeServer();
        return false;
    }

    printf("Server configured. Ip: %s, port: %hd!\n",
           ircManager->server.c_str(), ircManager->service_port);
    return true;
}

void LoginHandler::run()
{
    int clnsck, clnlen;
    struct sockaddr_in cln_addr;

    clnlen = sizeof(struct sockaddr_in);

    do
    {
        if ((clnsck = accept(sck, (struct sockaddr*) &cln_addr, (socklen_t*) &clnlen)) >= 0)
        {
            if (fcntl(clnsck, F_SETFL, fcntl(clnsck, F_GETFL, 0) | O_NONBLOCK) >= 0)
            {
                printf("User connected to the socket!\n");
                createUser(clnsck);
            }
        }

        for (int i = vThreads.size() - 1; i >= 0; i--)
        {
            if (pthread_kill(*vThreads[i], 0) < 0)
            {
                free(vThreads[i]);
                vThreads.erase(vThreads.begin() + i);
            }
        }
    } while (!ircManager->serverClosed());

    for (pthread_t *ptrThread : vThreads)
    {
        pthread_join(*ptrThread, NULL);
        free(ptrThread);
    }

    close(sck);
}

void LoginHandler::createUser(int clnsck)
{
    User *user = new User(clnsck, ircManager);

    pthread_t *ptrThread = (pthread_t*) malloc(sizeof(pthread_t));

    if (pthread_create(ptrThread, NULL, startUser, (void *) user) < 0)
    {
        perror("Cannot create thread!");
        free(ptrThread);
    }
    else
    {
        vThreads.push_back(ptrThread);
    }
}

void *LoginHandler::startUser(void *user)
{
    User *us = (User*)user;
    us->run();
    delete us;
    pthread_exit(0);
}
