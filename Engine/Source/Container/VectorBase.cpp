#include "VectorBase.h"
#include "../DebugNew.h"

namespace Engine
{
	namespace Container
	{
		unsigned char* VectorBase::AllocateBuffer(unsigned int size)
		{
			return new unsigned char[size];
		}
	}
}