#ifndef FREE_H
#define FREE_H

#include "Type.h"

class Used;

class Free
{
public:
    // ---------------------------------------------------------
    // Do not reorder, change or add data fields
    //     --> any changes to the data... 0 given to the assignment
    // You can add methods if you wish
    // ---------------------------------------------------------

    Free *pNext;              // next free Type
    Free *pPrev;              // prev free Type  
    unsigned int   mData;    // size (1-bit Type, 1-bit AboveFree, 30 bits memSize)

    // Methods
    Free() = default;
    Free(const Free &) = delete;
    Free &operator = (const Free &) = delete;
    ~Free() = default;
    Free(unsigned int FreeBlockSize);
    Free(Used &);
};

#endif 

// --- End of File ---
