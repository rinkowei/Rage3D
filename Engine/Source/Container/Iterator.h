#pragma once

namespace Engine
{
	namespace Container
	{
		// Random access iterator.
		template<typename T>
		struct Iterator
		{
			// Default constructor.
			constexpr Iterator() : Ptr(nullptr)
			{
				
			}

			// Construct with an object pointer.
			explicit constexpr Iterator(T* ptr) : Ptr(ptr)
			{

			}

			// Point to the object.
			constexpr T* operator->() const
			{
				return Ptr;
			}

			// Dereference the object.
			constexpr T& operator*() const
			{
				return *Ptr;
			}

			// Preincrease the pointer.
			constexpr Iterator<T>& operator++()
			{
				++Ptr;
				return *this;
			}

			// Postincrease the pointer.
			constexpr Iterator<T> operator++(int)
			{
				Iterator<T> it = *this;
				++Ptr;
				return it;
			}

			// Predecrease the pointer.
			constexpr Iterator<T>& operator--()
			{
				--Ptr;
				return *this;
			}

			// Postdecrease the pointer.
			constexpr Iterator<T> operator--(int)
			{
				Iterator<T> it = *this;
				--Ptr;
				return it;
			}

			// Add an offset to the pointer.
			constexpr Iterator<T>& operator+=(int value)
			{
				Ptr += value;
				return *this;
			}

			// Subtract an offset to the pointer.
			constexpr Iterator<T>& operator-=(int value)
			{
				Ptr -= value;
				return *this;
			}

			// Add an offset to the pointer.
			constexpr Iterator<T> operator+(int value) const 
			{ 
				return Iterator<T>(Ptr + value);
			}

			// Subtract an offset from the pointer.
			constexpr Iterator<T> operator-(int value) const 
			{ 
				return Iterator<T>(Ptr - value); 
			}

			// Calculate offset to another iterator.
			constexpr int operator-(const Iterator& rhs) const 
			{ 
				return reinterpret_cast<int>(Ptr - rhs.Ptr); 
			}

			// Equality with another iterator.
			constexpr bool operator==(const Iterator& rhs) const 
			{ 
				return Ptr == rhs.Ptr; 
			}

			// Inequality with another iterator.
			constexpr bool operator!=(const Iterator& rhs) const 
			{ 
				return Ptr != rhs.Ptr;
			}

			// Less than with another iterator.
			constexpr bool operator<(const Iterator& rhs) const 
			{ 
				return Ptr < rhs.Ptr;
			}

			// Greater than with another iterator.
			constexpr bool operator>(const Iterator& rhs) const 
			{ 
				return Ptr > rhs.Ptr; 
			}

			// Less than or equal with another iterator.
			constexpr bool operator<=(const Iterator& rhs) const 
			{ 
				return Ptr <= rhs.Ptr;
			}

			// Greater than or equal with another iterator.
			constexpr bool operator>=(const Iterator& rhs) const 
			{ 
				return Ptr >= rhs.Ptr; 
			}

			T* Ptr;
		};


		/// Random access const iterator.
		template<typename T> 
		struct ConstIterator
		{
			// Default constructor.
			constexpr ConstIterator() : Ptr(nullptr)
			{

			}

			// Construct with an object pointer.
			constexpr explicit ConstIterator(const T* ptr) : Ptr(ptr)
			{

			}

			// Construct from a non-const iterator.
			constexpr ConstIterator(const ConstIterator<T>& rhs): Ptr(rhs.Ptr)
			{

			}

			// Assign from a non-const iterator.
			constexpr ConstIterator<T>& operator=(const ConstIterator<T>& rhs)
			{
				Ptr = rhs.Ptr;
				return *this;
			}

			// Point to the object.
			constexpr const T* operator->() const 
			{ 
				return Ptr; 
			}

			// Dereference the object.
			constexpr const T& operator*() const 
			{
				return *Ptr;
			}

			// Preincrease the pointer.
			constexpr ConstIterator<T>& operator++()
			{
				++Ptr;
				return *this;
			}

			// Postincrease the pointer.
			constexpr ConstIterator<T> operator++(int)
			{
				ConstIterator<T> it = *this;
				++Ptr;
				return it;
			}

			// Predecrease the pointer.
			constexpr ConstIterator<T>& operator--()
			{
				--Ptr;
				return *this;
			}

			// Postdecrease the pointer.
			constexpr ConstIterator<T> operator--(int)
			{
				ConstIterator<T> it = *this;
				--Ptr;
				return it;
			}

			// Add an offset to the pointer.
			constexpr ConstIterator<T>& operator+=(int value)
			{
				Ptr += value;
				return *this;
			}

			// Subtract an offset from the pointer.
			constexpr ConstIterator<T>& operator-=(int value)
			{
				Ptr -= value;
				return *this;
			}

			// Add an offset to the pointer.
			constexpr ConstIterator<T> operator+(int value) const 
			{ 
				return ConstIterator<T>(Ptr + value); 
			}

			// Subtract an offset from the pointer.
			constexpr ConstIterator<T> operator-(int value) const 
			{ 
				return ConstIterator<T>(Ptr - value); 
			}

			// Calculate offset to another iterator.
			constexpr int operator-(const ConstIterator& rhs) const 
			{ 
				return reinterpret_cast<int>(Ptr - rhs.Ptr); 
			}

			// Equality with another iterator.
			constexpr bool operator==(const ConstIterator& rhs) const 
			{ 
				return Ptr == rhs.Ptr; 
			}

			// Inequality with another iterator.
			constexpr bool operator!=(const ConstIterator& rhs) const 
			{
				return Ptr != rhs.Ptr; 
			}

			// Less than with another iterator.
			constexpr bool operator<(const ConstIterator& rhs) const 
			{ 
				return Ptr < rhs.Ptr; 
			}

			// Greater than with another iterator.
			constexpr bool operator>(const ConstIterator& rhs) const 
			{ 
				return Ptr > rhs.Ptr; 
			}

			// Less than or equal with another iterator.
			constexpr bool operator<=(const ConstIterator& rhs) const 
			{ 
				return Ptr <= rhs.Ptr;
			}

			// Greater than or equal with another iterator.
			constexpr bool operator>=(const ConstIterator& rhs) const 
			{ 
				return Ptr >= rhs.Ptr; 
			}

			// Pointer.
			const T* Ptr;
		};
	}
}