#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>

#include <string_view>
#include "RavelLogger.h"
using namespace std::string_view_literals;

class MemoryManager {

	// Memory structure
private:

	//Profilling used
	struct Profile {
		std::vector<std::string> blocks;
	}profile;

	struct _block {
		struct _block *next;
		struct _block *prev;
		size_t size;
		bool isFree;
		void* pool;
	};

	void* mempool;
	std::unordered_map<size_t, _block*> vtable;

	std::size_t Hash(void* address);

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
#ifdef _DEBUG
	std::cout << "MEMORY MANAGER : Allocating " << size << "bytes" << std::endl;
	std::string typeName = typeid(T).name();
	std::string log{ std::string{"Memory::Creating block of type "} + typeid(T).name() };
	
#endif
	while (seg) {
		if (seg->isFree) {
			// block is free, check block size
			if (seg->size >= size) {
				//enough space to use, break block for use
				found = true;
				break;
			}
			seg = seg->next;
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
		vtable[Hash(block->pool)] = block;
	}

	T* obj = new (seg->pool) T();

#ifdef _DEBUG
	std::stringstream address;
	address << &seg->pool;
	log.append(std::string{ std::string{ " address : " }  + address.str()});
	RLogger()->DebugLog(std::string_view{ log });
#endif

	seg->isFree = false;
	return obj;
}
