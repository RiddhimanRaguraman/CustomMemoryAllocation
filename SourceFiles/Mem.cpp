#include "Mem.h"

struct SecretPtr
{
    Free *pFree;
};

void Mem::initialize() {
    Free *pFree = nullptr;
    this->poHeap->SetPointers(pFree);
    this->poHeap->AddFreeNode(pFree);
    this->poHeap->SetNextFit(pFree);
    this->poHeap->AddFreeStats(pFree);
}


void *Mem::malloc(const unsigned int _size)
{
    assert(this->poHeap != nullptr);
    Used *pUsed = nullptr;
    Free *pFree = this->poHeap->pNextFit;
    Free *pStart = pFree;

    do {
        if (GET_ALLOC_SIZE(pFree->mData) >= _size)
            break;
        pFree = pFree->pNext;
        if (pFree == nullptr)
            pFree = this->poHeap->pFreeHead;
    } while (pFree != pStart);

    if (pFree != nullptr)
    {
        if (GET_ALLOC_SIZE(pFree->mData) >= _size + sizeof(Free))
        {
            unsigned int remainingSize = GET_ALLOC_SIZE(pFree->mData) - _size - sizeof(Free);
            Free *pNewFree = (Free *)((char *)pFree + _size + sizeof(Used));

            new (pNewFree) Free(remainingSize);
            PrivSetSecretPointer(pNewFree);

            SET_FREE(pNewFree->mData);
            SET_ALLOC_SIZE(pNewFree->mData, remainingSize);

            this->poHeap->RemoveFreeNode(pFree);
            this->poHeap->RemoveFreeStats(pFree);
            this->poHeap->AddFreeNode(pNewFree);
            this->poHeap->AddFreeStats(pNewFree);
            this->poHeap->SetNextFit(pNewFree);

            pUsed = new(pFree) Used(_size);
            SET_ABOVE_USED(pNewFree->mData);
        }
        else
        {
            this->poHeap->RemoveFreeNode(pFree);
            this->poHeap->RemoveFreeStats(pFree);
            this->poHeap->SetNextFit(this->poHeap->pFreeHead);
            pUsed = new(pFree) Used(GET_ALLOC_SIZE(pFree->mData));

            Free *pBelow = (Free *)((char *)pUsed + sizeof(Used) + _size);
            char *pHeapEnd = (char *)this->poHeap + Mem::TotalSize;
            if ((char *)pBelow < pHeapEnd)
                SET_ABOVE_USED(pBelow->mData);
        }
        this->poHeap->AddUsedNode(pUsed);
        this->poHeap->AddUsedStats(pUsed);
    }
    return pUsed + 1;
}

void Mem::free(void *const data) {
    assert(data);
    assert(this->poHeap);
    bool aboveFree = false;

    Used *pUsed = (Used *)data - 1;

    this->poHeap->RemoveUsedNode(pUsed);
    this->poHeap->RemoveUsedStats(pUsed);

    aboveFree = IS_ABOVE_FREE(pUsed->mData);

    Free *pFree = new(pUsed) Free(GET_ALLOC_SIZE(pUsed->mData));
    SET_FREE(pFree->mData);
    SET_ALLOC_SIZE(pFree->mData, GET_ALLOC_SIZE(pUsed->mData));
    this->poHeap->AddFreeStats(pFree);

    if (aboveFree) {
        Free *pAboveFreeBlock = this->FindAboveFreeBlock(pFree);
        if (pAboveFreeBlock != nullptr)
        {
            this->PrivCoalesceAboveNodes(pAboveFreeBlock, pFree);
            pFree = pAboveFreeBlock;
        }
        else
        {
            assert(false);
        }
    }
    else {
        this->poHeap->AddFreeNode(pFree);
    }
    Free *pNextFree = (Free *)((char *)pFree + sizeof(Free) + GET_ALLOC_SIZE(pFree->mData));
    char *pHeapEnd = (char *)this->poHeap + Mem::TotalSize;
    if ((char *)pNextFree < pHeapEnd && IS_FREE(pNextFree->mData))
        this->PrivCoalesceBelowNodes(pFree, pNextFree);

    if (this->poHeap->currNumFreeBlocks == 1)
        this->poHeap->SetNextFit(pFree);

    Free *pBelow = (Free *)((char *)pFree + sizeof(Free) + GET_ALLOC_SIZE(pFree->mData));
    if ((char *)pBelow < pHeapEnd)
        SET_ABOVE_FREE(pBelow->mData);

    PrivSetSecretPointer(pFree);
}

void Mem::PrivSetSecretPointer(Free *pFree) const
{
    SecretPtr *pSecret = (SecretPtr *)((char *)(pFree)+sizeof(Free) + GET_ALLOC_SIZE(pFree->mData) - 4);
    pSecret->pFree = pFree;
}

Free *Mem::FindAboveFreeBlock(Free *pFree) const
{
    SecretPtr *pSecret = reinterpret_cast<SecretPtr *>((char *)pFree - sizeof(SecretPtr));
    return pSecret->pFree;
}

void Mem::PrivCoalesceAboveNodes(Free *pBlock1, Free *pBlock2)
{
    if (pBlock1 == nullptr || pBlock2 == nullptr) return;

    char *endOfBlock1 = (char *)pBlock1 + sizeof(Free) + GET_ALLOC_SIZE(pBlock1->mData);

    if (endOfBlock1 == (char *)pBlock2) {
        unsigned int newSize = GET_ALLOC_SIZE(pBlock1->mData) + GET_ALLOC_SIZE(pBlock2->mData) + sizeof(Free);
        SET_ALLOC_SIZE(pBlock1->mData, newSize);

        this->poHeap->currNumFreeBlocks -= 1;
        this->poHeap->currFreeMem += sizeof(Free);
    }
}

void Mem::PrivCoalesceBelowNodes(Free *pBlock1, Free *pBlock2)
{
    if (pBlock1 == nullptr || pBlock2 == nullptr) return;

    char *endOfBlock1 = (char *)pBlock1 + sizeof(Free) + GET_ALLOC_SIZE(pBlock1->mData);

    if (endOfBlock1 == (char *)pBlock2) {
        unsigned int newSize = GET_ALLOC_SIZE(pBlock1->mData) + GET_ALLOC_SIZE(pBlock2->mData) + sizeof(Free);
        SET_ALLOC_SIZE(pBlock1->mData, newSize);

        this->poHeap->RemoveFreeNode(pBlock2);
        this->poHeap->currNumFreeBlocks -= 1;
        this->poHeap->currFreeMem += sizeof(Free);
    }
}

// --- End of File ---