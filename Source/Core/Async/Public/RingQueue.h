#pragma once
#include <type_traits>
#include <cassert>

namespace Lumen::Core
{
	template<typename T>
	class RingQueue
	{
		struct Element
		{
			T item;
			Element() {};
			Element(const T& v) : item(v) {}

			template<typename... Args>
			void Emplace(Args&&... args)
			{
				new (&item)T(std::forward<Args>(args)...);
			}
		};

	private:
		// Auto expansion
		void ReAllocate()
		{
			size_t newCapacity;
			if (mCapacity == 0) newCapacity = 1;
			else if (mCapacity <= 128) newCapacity = mCapacity * 2;
			else newCapacity = (size_t)(mCapacity * 1.5);
			Element* newBuffer = (Element*)malloc(newCapacity * sizeof(Element));
			for (size_t i = mStart; i < mEnd; ++i)
			{
				new (newBuffer + i - mStart)Element(mBuffer[i % mCapacity]);
				mBuffer[i % mCapacity].~Element();
			}
			mEnd -= mStart;
			mStart = 0;
			free(mBuffer);
			mBuffer = newBuffer;
			mCapacity = newCapacity;
		}

	public:
		inline size_t Size() { return mEnd - mStart; }
		inline size_t Capacity() { return mCapacity; }

		RingQueue() {}

		RingQueue(size_t size) : mCapacity(size)
		{
			mBuffer = (Element*)malloc(size * sizeof(Element));
		}

		~RingQueue()
		{
			for (size_t i = mStart; i < mEnd; ++i)
				mBuffer[i % mCapacity].~Element();
			free(mBuffer);
		}

		// Alloc a BIGGER space manualy
		void Reserve(size_t size)
		{
			assert(size > mEnd - mStart);
			Element* newBuffer = (Element*)malloc(size * sizeof(Element));
			for (size_t i = mStart; i < mEnd; ++i)
			{
				new (newBuffer + i - mStart)Element(mBuffer[i % mCapacity]);
				mBuffer[i % mCapacity].~Element();
			}
			mEnd -= mStart;
			mStart = 0;
			free(mBuffer);
			mBuffer = newBuffer;
			mCapacity = size;
		}

		void Push(const T& value)
		{
			if (mEnd - mStart >= mCapacity)
				ReAllocate();
			size_t cur = mEnd++;
			new (mBuffer + cur % mCapacity)Element(value);
		}

		template<typename... Args>
		void Emplace(Args... args)
		{
			if (mEnd - mStart >= mCapacity)
				ReAllocate();
			size_t cur = mEnd++;
			mBuffer[cur % mCapacity].Emplace(std::forward<Args>(args)...);
		}

		T Front()
		{
			assert(mEnd - mStart);
			return mBuffer[mStart % mCapacity].item;
		}

		void Pop()
		{
			assert(mEnd - mStart);
			mBuffer[mStart % mCapacity].~Element();
			mStart++;
		}

		void Clear()
		{
			for (size_t i = mStart; i < mEnd; ++i)
				mBuffer[i % mCapacity].~Element();
			mStart = 0;
			mEnd = 0;
		}

		const Element* GetBuffer() const { return mBuffer; }

	private:
		size_t mStart = 0;
		size_t mEnd = 0;
		size_t mCapacity = 0;
		Element* mBuffer = nullptr;
	};
}