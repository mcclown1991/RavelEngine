#include "cstdlib"
#include "MemoryManager.h"

MemoryManager* Memory()
{
	static MemoryManager s;
	return(&s);
}

std::size_t MemoryManager::Hash(void * address)
{
	return (size_t)(address);
}

MemoryManager::_block * MemoryManager::CreateBlock(size_t size)
{
	_block *node = new _block;
	node->next = nullptr;
	node->prev = nullptr;
	node->size = size;
	node->isFree = true;
	node->pool = nullptr;
	return node;
}

MemoryManager::_block * MemoryManager::CreateBlock(_block *prev, size_t size)
{
	_block *node = new _block;
	node->next = nullptr;
	node->prev = prev;
	node->size = size;
	node->isFree = true;
	node->pool = nullptr;
	return node;
}

MemoryManager::MemoryManager()
{
}

MemoryManager::MemoryManager(size_t block_size)
{
	mempool = malloc(block_size);
	head = CreateBlock(block_size);
	head->pool = mempool;
	vtable[Hash(head->pool)] = head;
}

MemoryManager::~MemoryManager()
{
	
}

void MemoryManager::AllocateBlock(size_t block_size)
{
	mempool = malloc(block_size);
	head = CreateBlock(block_size);
	head->pool = mempool;
	vtable[Hash(head->pool)] = head;
}

MemoryManager::Pool * MemoryManager::alloc(size_t size)
{
	// search for free blocks
	_block* seg = head;
	bool found = false;
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
		vtable[Hash(block->pool)] = block;
	}

	seg->isFree = false;
	return seg->pool;
}

void MemoryManager::dealloc(Pool * pool)
{
	_block* page = vtable[Hash(pool)];
	page->isFree = true;

	//do some cleaning
	//currently block will be lost...
	//try see if next is free
	if (page->next->isFree) {
		page->size += page->next->size;
		vtable.erase(Hash(page->next->pool));
		delete page->next;
	}
	//try see if parent is free
	if (page->prev->isFree) {
		//we combine them
		page->prev->size += page->size;
		//remove current address from map
		vtable.erase(Hash(pool));
		delete page;
	}
	
}
