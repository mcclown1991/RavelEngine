#pragma once
#include <map>

class MemoryManager {

	// Memory structure
private:
	struct _block {
		struct _block *next;
		struct _block *prev;
		size_t size;
		bool isFree;
		void* pool;
	};

	void* mempool;
	std::map<void*, _block*> vtable;

	_block* head;

	_block* CreateBlock(size_t size);
	_block* CreateBlock(_block *prev, size_t size);

public:
	MemoryManager();
	MemoryManager(size_t block_size);
	~MemoryManager();

	// call only if u have not init the manager
	void AllocateBlock(size_t block_size);

	template <typename T>
	T* alloc();

	typedef void Pool;
	
	Pool* alloc(size_t size);
	void dealloc(Pool* pool);
};

MemoryManager* Memory();

template<typename T>
inline T * MemoryManager::alloc()
{
	// search for free blocks
	_block* seg = head;
	bool found = false;
	size_t size = sizeof(T);
	while (seg) {
		if (seg->isFree) {
			// block is free, check block size
			if (seg->size >= size) {
				//enough space to use, break block for use
				found = true;
				break;
			}
		}
		else
			seg = seg->next;
	}

	if (!found) return nullptr;

	if (seg->size != size) {
		// break block here
		_block* block = CreateBlock(seg, seg->size - size);
		seg->size = size;
		block->next = seg->next;
		seg->next = block;
		//seg->isFree = false;
		block->pool = (char*)seg->pool + size;
		vtable[block->pool] = block;
	}

	T* obj = new (seg->pool) T();

	seg->isFree = false;
	return obj;
}
