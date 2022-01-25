#pragma once

namespace Lumen::Core
{
    template<typename T, size_t ChunkSize>
    MemoryChunk<T, ChunkSize>::MemoryChunk()
    {
        mBuffer = (T*)malloc(ChunkSize * sizeof(T));
    }

    template<typename T, size_t ChunkSize>
    MemoryChunk<T, ChunkSize>::~MemoryChunk()
    {
        free(mBuffer);
    }

    template<typename T>
    MemoryPool<T>::MemoryPool()
    {
        mChunkList = new MemoryChunk<T>();
        for (int i = 0; i < mChunkList->mCapacity; i++)
            mFreeElements.emplace_back(mChunkList->mBuffer + i);
    }

    template<typename T>
    MemoryPool<T>::~MemoryPool()
    {
        while (mChunkList->next)
        {
            MemoryChunk<T>* nxt = mChunkList->next;
            delete mChunkList;
            mChunkList = nxt;
        }
        delete mChunkList;
    }

    template<typename T>
    MemoryPool<T>::MemoryPool(MemoryPool&& pool)
    {
        // TODO
    }

    template<typename T>
    MemoryPool<T>& MemoryPool<T>::operator=(MemoryPool&& pool)
    {
        // TODO
    }

    template<typename T>
    void MemoryPool<T>::ExpandPool()
    {
        MemoryChunk<T>* newChunk = new MemoryChunk<T>();
        MemoryChunk<T>* chunk = mChunkList;
        while (chunk->next) chunk = chunk->next;
        chunk->next = newChunk;
        for (int i = 0; i < newChunk->mCapacity; i++)
            mFreeElements.emplace_back(newChunk->mBuffer + i);
    }

    template<typename T>
    T* MemoryPool<T>::RequestElement()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        if (mFreeElements.empty()) ExpandPool();
        T* elementAddress = mFreeElements.back();
        mFreeElements.pop_back();
        return elementAddress;
    }

    template<typename T>
    void MemoryPool<T>::ReturnElement(T* element)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mFreeElements.push_back(element);
    }
}