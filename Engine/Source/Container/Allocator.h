#pragma once

#ifdef RAGE3D_IS_BUILDING
#include "Rage3D.h"
#else
#include <Rage3D/Rage3D.h>
#endif

#include <cstddef>

namespace Engine
{
	namespace Container
	{
		struct MemoryBlock;
		struct MemoryNode;

		// Allocator memory block.
		struct MemoryBlock
		{
			// Size of node.
			unsigned int mNodeSize;
			// count of nodes in this block.
			unsigned int mCapacity;
			// First free node.
			MemoryNode* mFreeNode;
			// Next allocator memory block.
			MemoryBlock* mNextBlock;
		};

		// Allocator memory node.
		struct MemoryNode
		{
			// Next free node.
			MemoryNode* mNextNode;
		};

		// Initialize a fixed-size allocator with the node size and initial capacity.
		RAGE3D_API MemoryBlock* AllocatorInitialize(unsigned int nodeSize, unsigned int initialCapacity = 1);

		// Uninitialize a fixed-size allocator. Frees all blocks in the chain.
		RAGE3D_API void AllocatorUninitialize(MemoryBlock* allocator);

		// Reserve a node. Creates a new block if necessary.
		RAGE3D_API void* AllocatorReserve(MemoryBlock* allocator);

		// Free a node. Does not free any blocks.
		RAGE3D_API void AllocatorFree(MemoryBlock* allocator, void* ptr);

		template<typename T>
		class Allocator
		{
		public:
			explicit Allocator(unsigned int initialCapacity = 0) :
				mMemoryBlock(nullptr)
			{
				if (initialCapacity)
					mMemoryBlock = AllocatorInitialize((unsigned int)sizeof(T), initialCapacity);
			}

			~Allocator()
			{
				AllocatorUninitialize(mMemoryBlock);
			}

			Allocator(const Allocator<T>& rhs) = delete;

			Allocator<T>& operator=(const Allocator<T>& rhs) = delete;

			T* Reserve()
			{
				if (!mMemoryBlock)
				{
					mMemoryBlock = AllocatorInitialize((unsigned int)sizeof(T));
				}
				auto* newObject = static_cast<T*>(AllocatorReserve(mMemoryBlock));
				new(newObject) T();

				return newObject;
			}

			T* Reserve(const T& object)
			{
				if (!mMemoryBlock)
					mMemoryBlock = AllocatorInitialize((unsigned int)sizeof(T));
				auto* newObject = static_cast<T*>(AllocatorReserve(mMemoryBlock));
				new(newObject) T(object);

				return newObject;
			}

			void Free(T* object)
			{
				(object)->~T();
				AllocatorFree(mMemoryBlock, object);
			}
		private:
			MemoryBlock* mMemoryBlock;
		};
	}
}


