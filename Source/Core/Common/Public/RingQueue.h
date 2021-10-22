#pragma once
#include <type_traits>
#include <cassert>

namespace Lumen::Core
{
	// Lock free ring queue
	template<typename T>
	class RingQueue
	{
		struct Element
		{
			T item;
			Element() {};
			Element(const T& v) : item(v) {}

			template<typename... Args>
			void Emplace(Args&&... args) { new (&item)T(std::forward<Args>(args)...); }
		};

	private:
		// Auto expansion
		void ReAllocate();

	public:
		inline size_t Size() { return mEnd - mStart; }
		inline size_t Capacity() { return mCapacity; }

		RingQueue() = default;
		RingQueue(size_t size);
		~RingQueue();

		RingQueue(RingQueue&) = delete;
		RingQueue& operator=(RingQueue&) = delete;

		void Push(const T& value);
		template<typename... Args>
		void Emplace(Args... args);
		void Pop();
		T& Front();
		void Reserve(size_t size);		// Alloc a BIGGER space manualy
		void Clear();

		const Element* GetBuffer() const { return mBuffer; }

	private:
		size_t mStart = 0;
		size_t mEnd = 0;
		size_t mCapacity = 0;
		Element* mBuffer = nullptr;
	};
}

#include "Details/RingQueue.inl"