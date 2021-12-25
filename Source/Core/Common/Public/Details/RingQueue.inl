#pragma once

namespace Lumen::Core
{
	template<typename T>
	RingQueue<T>::RingQueue(size_t size) : mCapacity(size)
	{
		mBuffer = (Element*)malloc(size * sizeof(Element));
	}

	template<typename T>
	RingQueue<T>::~RingQueue()
	{
		for (size_t i = mStart; i < mEnd; ++i)
			mBuffer[i % mCapacity].~Element();
		free(mBuffer);
	}

	template<typename T>
	void RingQueue<T>::ReAllocate()
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

	template<typename T>
	void RingQueue<T>::Reserve(size_t size)
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

	template<typename T>
	void RingQueue<T>::Push(const T& value)
	{
		if (mEnd - mStart >= mCapacity)
			ReAllocate();
		size_t cur = mEnd;
		new (mBuffer + cur % mCapacity)Element(value);
		mEnd++;
	}

	template<typename T>
	template<typename... Args>
	void RingQueue<T>::Emplace(Args... args)
	{
		if (mEnd - mStart >= mCapacity)
			ReAllocate();
		size_t cur = mEnd;
		mBuffer[cur % mCapacity].Emplace(std::forward<Args>(args)...);
		mEnd++;
	}

	template<typename T>
	T& RingQueue<T>::Front()
	{
		assert(mEnd - mStart);
		return mBuffer[mStart % mCapacity].item;
	}

	template<typename T>
	void RingQueue<T>::Pop()
	{
		assert(mEnd - mStart);
		mBuffer[mStart % mCapacity].~Element();
		mStart++;
	}

	template<typename T>
	void RingQueue<T>::Clear()
	{
		for (size_t i = mStart; i < mEnd; ++i)
			mBuffer[i % mCapacity].~Element();
		mStart = 0;
		mEnd = 0;
	}
}