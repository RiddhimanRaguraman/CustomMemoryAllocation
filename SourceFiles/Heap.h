#ifndef HEAP_H
#define HEAP_H

#include "Used.h"
#include "Free.h"

class Heap
{
public:
    Heap();
    Heap(const Heap &) = delete;
    Heap &operator =(const Heap &) = delete;
    ~Heap() = default;

    void AddFreeNode(Free *pFree);
    void AddFreeStats(Free *pFree);
    void RemoveFreeNode(Free *pFree);
    void RemoveFreeStats(const Free *pFree);
    void RemoveUsedNode(Used *pUsed);
    void RemoveUsedStats(const Used *pUsed);
    void AddUsedNode(Used *pUsed);
    void SetPointers(Free *&pFree);
    void AddUsedStats(Used *pUsed);
    void SetNextFit(Free *pFree);

public:
    // allocation links
    Used *pUsedHead;
    Free *pFreeHead;

    // Next fit allocation strategy
    Free *pNextFit;

    unsigned int    currNumUsedBlocks;   // number of current used allocations
    unsigned int    currUsedMem;         // current size of the total used memory

    unsigned int    currNumFreeBlocks;   // number of current free blocks
    unsigned int    currFreeMem;         // current size of the total free memory

    unsigned int    pad;
};

#endif 
