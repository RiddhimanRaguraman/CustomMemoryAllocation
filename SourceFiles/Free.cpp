#include "Used.h"
#include "Free.h"
#include "Type.h"


Free::Free(unsigned int FreeBlockSize)
	: pNext(nullptr),
	pPrev(nullptr),
	mData(FreeBlockSize)
{
	//SET_ABOVE_USED(this->mData);
}

Free::Free(Used &rUsed)
	: pNext(nullptr),
	pPrev(nullptr),
	mData(rUsed.mData)
{
	//SET_ABOVE_USED(this->mData);
}
