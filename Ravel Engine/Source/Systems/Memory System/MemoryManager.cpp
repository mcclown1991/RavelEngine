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

	profile.blocks.push_back(std::string("Created block"));

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

	profile.blocks.push_back(std::string("Created block"));

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
	_block* temp;
	vtable.clear();
	

	while (head) {
		temp = head;
		head = head->next;
#ifdef _DEBUG
		std::stringstream address;
		address << temp->pool;
		std::string log{ std::string{"Memory::Deleting address "} + address.str() };
		RLogger()->DebugLog(std::string_view{ log });
#endif
		delete temp;
		temp = nullptr;
		profile.blocks.push_back(std::string("Deleted block"));
	}
	
	free(mempool);
	mempool = nullptr;

	for (auto st : profile.blocks) {
		//std::cout << st.c_str() << std::endl;
	}
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
#ifdef _DEBUG
	std::cout << "MEMORY MANAGER : Allocating " << size << "bytes" << std::endl;
#endif
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

	size_t tableId = Hash(pool);
	_block* page = vtable[tableId];
	page->isFree = true;

#ifdef _DEBUG
	std::cout << "MEMORY MANAGER : Deallocating " << page->size << "bytes" << std::endl;
#endif

	//do some cleaning
	//currently block will be lost...
	//try see if next is free
	if ((page->next != nullptr) && page->next->isFree) {
		page->size += page->next->size;
		vtable.erase(tableId);
		_block* temp = page->next;
		if (page->next->next != nullptr) {
			page->next = page->next->next;
			page->next->prev = page;
			delete temp;
		}
	
		profile.blocks.push_back(std::string("Deleted block"));
#ifdef _DEBUG
		std::stringstream address;
		address << &page->pool;
		std::string log{ std::string{"Memory::Deleting address "} + address.str() };
		RLogger()->DebugLog(std::string_view{ log });
#endif
	}
	//try see if parent is free
	if ((page->prev != nullptr) && page->prev->isFree) {
		//we combine them
		page->prev->size += page->size;
		//remove current address from map
		vtable.erase(tableId);
#ifdef _DEBUG
		std::stringstream address;
		address << &page->pool;
		std::string log{ std::string{"Memory::Deleting address "} + address.str() };
		RLogger()->DebugLog(std::string_view{ log });
#endif
		page->prev->next = page->next;
		if (page->next != nullptr) {
			page->next->prev = page->prev;
			delete page;
		}

		profile.blocks.push_back(std::string("Deleted block"));


	}
}
