#pragma once

namespace Lumen::Core
{
    template<typename T>
    void TBuffer::PushBack(const T& val)
    {
        void* ptr = GetWritePointer(sizeof(T), alignof(T));
        new(ptr)T(val);
    }

    template<typename T>
    T& TBuffer::GetByPosition(size_t& pos)
    {
        void* ptr = GetReadPointer(pos, sizeof(T), alignof(T));
        return *reinterpret_cast<T*>(ptr);
    }
}