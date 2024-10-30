#include "Free.h"
#include "Used.h"

Used::Used(Free &pfree)
	: pNext(nullptr),
	pPrev(nullptr),
	mData(pfree.mData)
{

}

Used::Used(unsigned int FreeBlockSize)
	: pNext(nullptr),
	pPrev(nullptr),
	mData(FreeBlockSize)
{
	SET_USED(this->mData);
	//SET_ABOVE_USED(this->mData);
}