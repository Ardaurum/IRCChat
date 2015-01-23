#ifndef WRSEM_H
#define WRSEM_H

#include "semaphore.h"

class WRSem
{
private:
    sem_t m1, m2, m3, w, r;
    int readCount, writeCount;
public:
    WRSem();
    void lockReader();
    void unlockReader();
    void lockWriter();
    void unlockWriter();
};

#endif // WRSEM_H
