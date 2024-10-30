#ifndef MEM_H
#define MEM_H

#include "Mem.h"
#include "Heap.h"
#include "Type.h"
#include "iostream"
#include "cassert"

class Mem
{
public:
	static const unsigned int TotalSize = (50 * 1024);
	static const unsigned int HeapAlign = 16;
	static const unsigned int HeapAlignMask = HeapAlign - 1;
	static const unsigned int HeaderGuards = 128;

	enum class Guard
	{
		Type_A,
		Type_5,
		Type_None
	};

public:

	Mem(Guard type);

	Mem() = default;
	Mem(const Mem &) = delete;
	Mem &operator = (const Mem &) = delete;
	~Mem();

	// implement these functions
	void initialize();
	void *malloc(const unsigned int size);
	void free(void *const data);

	// helper functions
	Heap *GetHeap();
	void Print(int count);


	Free *FindAboveFreeBlock(Free *pFree) const;
	void PrivSetSecretPointer(Free *pFree) const;
	void PrivCoalesceAboveNodes(Free *pBlock1, Free *pBlock2);
	void PrivCoalesceBelowNodes(Free *pBlock1, Free *pBlock2);


private:
	// Useful in malloc and free
	Heap *poHeap;

	// Below: 
	// Not used in malloc, free, or initialize
	Guard type;
	void *poRawMem;
};

#endif 

// --- End of File ---