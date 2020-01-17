#include "Allocator.h"
#include "../DebugNew.h"

namespace Engine
{
	namespace Container
	{
		MemoryBlock* AllocatorReserveBlock(MemoryBlock* block, unsigned int nodeSize, unsigned int capacity)
		{
			if (!capacity)
				capacity = 1;

			auto* blockPtr = new unsigned char[sizeof(MemoryBlock) + capacity * (sizeof(MemoryBlock) + nodeSize)];
			auto* newBlock = reinterpret_cast<MemoryBlock*>(blockPtr);
			newBlock->mNodeSize = nodeSize;
			newBlock->mCapacity = capacity;
			newBlock->mFreeNode = nullptr;
			newBlock->mNextBlock = nullptr;

			if (!block)
			{
				block = newBlock;
			}
			else
			{
				newBlock->mNextBlock = block->mNextBlock;
				block->mNextBlock = newBlock;
			}

			unsigned char* nodePtr = blockPtr + sizeof(MemoryBlock);
			auto* firstNewNode = reinterpret_cast<MemoryNode*>(nodePtr);

			for (unsigned int i = 0; i < capacity - 1; ++i)
			{
				auto* newNode = reinterpret_cast<MemoryNode*>(nodePtr);
				newNode->mNextNode = reinterpret_cast<MemoryNode*>(nodePtr + sizeof(MemoryNode) + nodeSize);
				nodePtr += sizeof(MemoryNode) + nodeSize;
			}
			// i == capacity - 1
			{
				auto* newNode = reinterpret_cast<MemoryNode*>(nodePtr);
				newNode->mNextNode = nullptr;
			}

			block->mFreeNode = firstNewNode;

			return newBlock;
		}

		MemoryBlock* AllocatorInitialize(unsigned int nodeSize, unsigned int initialCapacity)
		{
			MemoryBlock* block = AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
			return block;
		}

		void AllocatorUninitialize(MemoryBlock* block)
		{
			while (block)
			{
				MemoryBlock* next = block->mNextBlock;
				delete[] reinterpret_cast<unsigned char*>(block);
				block = next;
			}
		}

		void* AllocatorReserve(MemoryBlock* block)
		{
			if (!block)
				return nullptr;

			if (!block->mFreeNode)
			{
				// Free nodes have been exhausted. Allocate a new larger block
				unsigned newCapacity = (block->mCapacity + 1) >> 1u;
				AllocatorReserveBlock(block, block->mNodeSize, newCapacity);
				block->mCapacity += newCapacity;
			}

			// We should have new free node(s) chained
			MemoryNode* freeNode = block->mFreeNode;
			void* ptr = (reinterpret_cast<unsigned char*>(freeNode)) + sizeof(MemoryNode);
			block->mFreeNode = freeNode->mNextNode;
			freeNode->mNextNode = nullptr;

			return ptr;
		}

		void AllocatorFree(MemoryBlock* block, void* ptr)
		{
			if (!block || !ptr)
				return;

			auto* dataPtr = static_cast<unsigned char*>(ptr);
			auto* node = reinterpret_cast<MemoryNode*>(dataPtr - sizeof(MemoryNode));

			// Chain the node back to free nodes
			node->mNextNode = block->mFreeNode;
			block->mFreeNode = node;
		}
	}
}