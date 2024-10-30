#include "Heap.h"
#include "Mem.h"

Heap::Heap()
    : pUsedHead(nullptr),
    pFreeHead(nullptr),
    pNextFit(nullptr),
    currNumUsedBlocks(0),
    currUsedMem(0),
    currNumFreeBlocks(0),
    currFreeMem(0),
    pad(0)
{
}

void Heap::AddFreeNode(Free *pFree)
{
    assert(pFree != nullptr);
    if (this->pFreeHead == nullptr) {
        this->pFreeHead = pFree;
        pFree->pNext = nullptr;
        pFree->pPrev = nullptr;
        this->pNextFit = pFree;
        return;
    }
    Free *pCurr = this->pFreeHead;
    Free *pPrevFree = nullptr;
    while (pCurr != nullptr && pCurr < pFree)
    {
        pPrevFree = pCurr;
        pCurr = pCurr->pNext;
    }
    pFree->pPrev = pPrevFree;
    pFree->pNext = pCurr;
    if (pPrevFree != nullptr) {
        pPrevFree->pNext = pFree;
    }
    else {
        this->pFreeHead = pFree;
    }
    if (pCurr != nullptr) {
        pCurr->pPrev = pFree;
    }
    if (pFree->pNext == nullptr) {
        this->pNextFit = pFree;
    }

}

void Heap::AddFreeStats(Free *pFree)
{
    assert(pFree != nullptr);
    this->currNumFreeBlocks += 1;
    this->currFreeMem += GET_ALLOC_SIZE(pFree->mData);
    SET_FREE(pFree->mData);
}

void Heap::RemoveFreeNode(Free *pFree)
{
    assert(pFree != nullptr);
    if (this->pFreeHead == pFree) {
        this->pFreeHead = pFree->pNext;
    }
    if (pFree->pPrev != nullptr) {
        pFree->pPrev->pNext = pFree->pNext;
    }
    if (pFree->pNext != nullptr) {
        pFree->pNext->pPrev = pFree->pPrev;
    }
    pFree->pNext = nullptr;
    pFree->pPrev = nullptr;
}

void Heap::RemoveFreeStats(const Free *pFree)
{
    assert(pFree != nullptr);
    this->currNumFreeBlocks -= 1;
    this->currFreeMem -= GET_ALLOC_SIZE(pFree->mData);
}

void Heap::SetNextFit(Free *pFree)
{
    this->pNextFit = pFree;
}

void Heap::AddUsedNode(Used *pUsed)
{
    assert(pUsed != nullptr);
    if (this->pUsedHead == nullptr) {
        this->pUsedHead = pUsed;
        pUsed->pNext = nullptr;
        pUsed->pPrev = nullptr;
    }
    else {
        pUsed->pNext = this->pUsedHead;
        this->pUsedHead->pPrev = pUsed;
        this->pUsedHead = pUsed;
        pUsed->pPrev = nullptr;
    }
}

void Heap::RemoveUsedNode(Used *pUsed)
{
    assert(pUsed != nullptr);

    if (this->pUsedHead == pUsed) {
        this->pUsedHead = pUsed->pNext; // Update head if necessary
    }

    // Only modify pPrev and pNext if they are valid
    if (pUsed->pPrev != nullptr) {
        pUsed->pPrev->pNext = pUsed->pNext; // Safe because pPrev is checked
    }

    if (pUsed->pNext != nullptr) {
        pUsed->pNext->pPrev = pUsed->pPrev; // Safe because pNext is checked
    }

    // Clean up the pointers
    pUsed->pNext = nullptr;
    pUsed->pPrev = nullptr;
}

void Heap::AddUsedStats(Used *pUsed)
{
    assert(pUsed != nullptr);
    this->currNumUsedBlocks += 1;
    this->currUsedMem += GET_ALLOC_SIZE(pUsed->mData);
    SET_USED(pUsed->mData);
}

void Heap::RemoveUsedStats(const Used *pUsed)
{
    assert(pUsed != nullptr);
    this->currNumUsedBlocks -= 1;
    this->currUsedMem -= GET_ALLOC_SIZE(pUsed->mData);
}

void Heap::SetPointers(Free *&pFree)
{
    // Starting Location
    Free *pB = (Free *)((char *)this + sizeof(Heap));  // Start of HDR
    Free *pC = (Free *)pB + 1;                          // End of HDR

    void *pHeapEnd = (void *)((char *)this + Mem::TotalSize); // Bottom Of Heap

    unsigned int FreeSize = (unsigned int)((char *)pHeapEnd - (char *)pC);

    pFree = new(pB) Free(FreeSize);
}


