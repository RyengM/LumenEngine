#pragma once

#include <vector>
#include <mutex>
#include <cassert>

namespace Lumen::Core
{
	template<typename T, size_t ChunkSize = 1024>
	struct MemoryChunk
	{
	public:
		MemoryChunk();
		~MemoryChunk();

		T* mBuffer;
		const size_t mCapacity = ChunkSize;
		MemoryChunk* next = nullptr;
	};

	template<typename T>
	class MemoryPool
	{
	public:
		MemoryPool();
		~MemoryPool();
		MemoryPool(MemoryPool&& pool);
		MemoryPool& operator=(MemoryPool&& pool);

		MemoryPool(MemoryPool&) = delete;
		MemoryPool& operator=(MemoryPool&) = delete;

		T* RequestElement();
		void ReturnElement(T* element);

	private:
		void ExpandPool();

	private:
		std::vector<T*> mFreeElements;
		MemoryChunk<T>* mChunkList;

		std::mutex mMutex;
	};
}

#include "Details/MemoryPool.inl"