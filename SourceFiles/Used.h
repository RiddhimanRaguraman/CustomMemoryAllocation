#pragma once
#ifndef USED_H
#define USED_H

#include "Type.h"

class Free;

class Used
{
public:

    Used *pNext;              // next free Type
    Used *pPrev;              // prev free Type  
    unsigned int   mData;    // size (1-bit Type, 1-bit AboveFree, 30 bits memSize)

    Used() = default;
    Used(const Used &) = delete;
    Used &operator = (const Used &) = delete;
    ~Used() = default;
    Used(Free &);
    Used(unsigned int);
};

#endif 

// --- End of File ---

