#include "WRSem.h"

WRSem::WRSem()
{
    sem_init(&m1, 0, 1);
    sem_init(&m2, 0, 1);
    sem_init(&m3, 0, 1);
    sem_init(&w, 0, 1);
    sem_init(&r, 0, 1);
}

void WRSem::lockReader()
{
    sem_wait(&m3);
    sem_wait(&r);
    sem_wait(&m1);
    readCount++;
    if (readCount == 1)
        sem_wait(&w);
    sem_post(&m1);
    sem_post(&r);
    sem_post(&m3);
}

void WRSem::unlockReader()
{
    sem_wait(&m1);
    readCount--;
    if (readCount == 0)
        sem_post(&w);
    sem_post(&m1);
}

void WRSem::lockWriter()
{
    sem_wait(&m2);
    writeCount++;
    if (writeCount == 1)
        sem_wait(&r);
    sem_post(&m2);
}

void WRSem::unlockWriter()
{
    sem_wait(&m2);
    writeCount--;
    if (writeCount == 0)
        sem_post(&r);
    sem_post(&m2);
}
