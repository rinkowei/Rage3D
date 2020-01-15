#pragma once

#ifdef RAGE3D_IS_BUILDING
#include "Rage3D.h"
#else
#include <Rage3D/Rage3D.h>
#endif

#include "../Container/Iterator.h"
#include "../Container/Swap.h"

namespace Engine
{
	namespace Container
	{
		class RAGE3D_API VectorBase
		{
		public:
			VectorBase() noexcept :
				Size(0),
				Capacity(0),
				Buffer(nullptr)
			{

			}

			void Swap(VectorBase& rhs)
			{
				Container::Swap(Size, rhs.Size);
				Container::Swap(Capacity, rhs.Capacity);
				Container::Swap(Buffer, rhs.Buffer);
			}
		protected:
			unsigned int Size;

			unsigned int Capacity;

			unsigned char* Buffer;

			static unsigned char* AllocateBuffer(unsigned int size);
		};
	}
}