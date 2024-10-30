#include "Mem.h"
#include "Heap.h"
#include "Type.h"
#include <cassert>
#include <cstdint>

#ifdef _DEBUG
#define HEAP_SET_BOTTOM_A_GUARDS do { \
    uintptr_t end = reinterpret_cast<uintptr_t>(poRawMem) + Mem::TotalSize; \
    unsigned int *pF = reinterpret_cast<unsigned int *>(end); \
    for (int i = 0; i < 30; ++i) { \
        *pF++ = 0xAAAAAAAA; \
    } \
} while(0)

#define HEAP_TEST_BOTTOM_A_GUARDS do { \
    uintptr_t end = reinterpret_cast<uintptr_t>(poRawMem) + Mem::TotalSize; \
    unsigned int *pF = reinterpret_cast<unsigned int *>(end); \
    for (int i = 0; i < 30; ++i) { \
        assert(*pF++ == 0xAAAAAAAA); \
    } \
} while(0)

#define HEAP_SET_BOTTOM_5_GUARDS do { \
    uintptr_t end = reinterpret_cast<uintptr_t>(poRawMem) + Mem::TotalSize; \
    unsigned int *pF = reinterpret_cast<unsigned int *>(end); \
    for (int i = 0; i < 30; ++i) { \
        *pF++ = 0x55555555; \
    } \
} while(0)

#define HEAP_TEST_BOTTOM_5_GUARDS do { \
    uintptr_t end = reinterpret_cast<uintptr_t>(poRawMem) + Mem::TotalSize; \
    unsigned int *pF = reinterpret_cast<unsigned int *>(end); \
    for (int i = 0; i < 30; ++i) { \
        assert(*pF++ == 0x55555555); \
    } \
} while(0)

#else
#define HEAP_SET_BOTTOM_A_GUARDS  
#define HEAP_TEST_BOTTOM_A_GUARDS  
#define HEAP_SET_BOTTOM_5_GUARDS  
#define HEAP_TEST_BOTTOM_5_GUARDS  
#endif

//#ifdef _DEBUG
//#define HEAP_SET_BOTTOM_A_GUARDS unsigned int *pF = (unsigned int *)((unsigned int)poRawMem + Mem::TotalSize); \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA;	\
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; \
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA;	\
//								*pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA; *pF++ = 0xAAAAAAAA;
//
//
//#define HEAP_TEST_BOTTOM_A_GUARDS	unsigned int *pF = (unsigned int *)((unsigned int)poRawMem + Mem::TotalSize); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA); \
//								assert(*pF++ == 0xAAAAAAAA); assert(*pF++ == 0xAAAAAAAA);
//
//#define HEAP_SET_BOTTOM_5_GUARDS unsigned int *pF = (unsigned int *)((unsigned int)poRawMem + Mem::TotalSize); \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555;	\
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; \
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555;	\
//								*pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555; *pF++ = 0x55555555;
//
//#define HEAP_TEST_BOTTOM_5_GUARDS	unsigned int *pF = (unsigned int *)((unsigned int)poRawMem + Mem::TotalSize); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555); \
//								assert(*pF++ == 0x55555555); assert(*pF++ == 0x55555555);
//
//#else
//#define HEAP_SET_BOTTOM_A_GUARDS  	
//#define HEAP_TEST_BOTTOM_A_GUARDS	
//#define HEAP_SET_BOTTOM_5_GUARDS  	
//#define HEAP_TEST_BOTTOM_5_GUARDS
//#endif

Mem::~Mem()
{
	// do not modify this function
	if (this->type == Guard::Type_A)
	{
		HEAP_TEST_BOTTOM_A_GUARDS;
	}
	else if (this->type == Guard::Type_5)
	{
		HEAP_TEST_BOTTOM_5_GUARDS;
	}
	else
	{
		// do nothing
	}
	_aligned_free(this->poRawMem);
}

Heap *Mem::GetHeap()
{
	return this->poHeap;
}

Mem::Mem(Guard _type)
{
	// now initialize it.
	this->poHeap = nullptr;
	this->poRawMem = nullptr;
	this->type = _type;

	// Do a land grab --- get the space for the entire heap
	// Since OS have Different Alignments... I forced it to 16 byte aligned
	poRawMem = _aligned_malloc(Mem::TotalSize + Mem::HeaderGuards, Mem::HeapAlign);

	// verify alloc worked
	assert(poRawMem != nullptr);

	if (this->type == Guard::Type_A)
	{
		HEAP_SET_BOTTOM_A_GUARDS;
	}
	else
	{
		HEAP_SET_BOTTOM_5_GUARDS;
	}

	// Guarantee alignemnt
	assert(((unsigned int)poRawMem & Mem::HeapAlignMask) == 0x0);

	Heap *p = new(poRawMem) Heap();
	assert(p);

	// update it
	this->poHeap = p;

}

void Mem::Print(int count)
{
	printf("\n------- Print %d -------------\n\n", count);

	printf("heapStart: 0x%p     \n", this->poHeap);
	printf("  heapEnd: 0x%p   \n\n", (void *)((unsigned int)this->poHeap + Mem::TotalSize));
	printf("pUsedHead: 0x%p     \n", this->poHeap->pUsedHead);
	printf("pFreeHead: 0x%p     \n", this->poHeap->pFreeHead);
	printf(" pNextFit: 0x%p   \n\n", this->poHeap->pNextFit);

	printf("Heap Hdr   s: %p  e: %p                            size: %zu \n", (void *)this->poHeap, (void *)(this->poHeap + 1), sizeof(Heap));


	unsigned int p = (unsigned int)(poHeap + 1);

	const char *typeHdr;
	const char *blocktype;

	while (p < ((unsigned int)poHeap + Mem::TotalSize))
	{
		Used *used = (Used *)p;
		if (IS_USED(used->mData))
		{
			typeHdr = "USED HDR ";
			blocktype = "USED     ";
		}
		else
		{
			typeHdr = "FREE HDR ";
			blocktype = "FREE     ";
		}

		unsigned int hdrStart = (unsigned int)used;
		unsigned int hdrEnd = (unsigned int)used + sizeof(Used);
		printf("%s  s: %p  e: %p  p: %p  n: %p  size: 0x%x    AF: %d \n",
			typeHdr,
			(void *)hdrStart,
			(void *)hdrEnd,
			used->pPrev,
			used->pNext,
			sizeof(Used),
			(IS_ABOVE_FREE(used->mData) && true));


		unsigned int blkStart = hdrEnd;
		unsigned int blkEnd = blkStart + GET_ALLOC_SIZE(used->mData);
		printf("%s  s: %p  e: %p                            size: 0x%x \n",
			blocktype,
			(void *)blkStart,
			(void *)blkEnd,
			GET_ALLOC_SIZE(used->mData));

		p = blkEnd;
	}
}
// --- End of File ---
