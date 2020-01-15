#pragma once

#ifdef RAGE3D_IS_BUILDING
#include "Rage3D.h"
#else
#include <Rage3D/Rage3D.h>
#endif

namespace Engine
{
	namespace Container
	{
		class HaseBase;
		class ListBase;
		class String;
		class VectorBase;

		template<typename T>
		__forceinline void Swap(T& first, T& second)
		{
			T temp = first;
			first = second;
			second = temp;
		}

		template<>
		RAGE3D_API void Swap<String>(String& first, String& second);

		template<>
		RAGE3D_API void Swap<VectorBase>(VectorBase& first, VectorBase& second);

		template<>
		RAGE3D_API void Swap<ListBase>(ListBase& first, ListBase& second);

		template<>
		RAGE3D_API void Swap<HaseBase>(HaseBase& first, HaseBase& second);
	}
}