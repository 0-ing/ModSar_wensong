#ifndef CONCURRENT_OBJECT_POOL_HPP
#define CONCURRENT_OBJECT_POOL_HPP

#include "MemPool.hpp"
#include "UniquePtr.hpp"

namespace pipc
{
namespace utils
{
/**
 * @brief A pool for managing objects, which returns smart pointers upon
 * allocation.
 *
 * This object pool contains storage for NLength objects and returns smart
 * pointers on allocation, which will trigger a deallocation at destruction.
 *
 * @todo:
 * We need a nice interface to support multiple FIFO types, SPSC is not
 * sufficient. Examples for different required FIFO types:
 * - Publisher pool: MPSC (one requester, but an idx push could happen
 *   simultaneuosly from two restitutes)
 * - Generic ObjectPool: MPMC (any thread could request an object or give it
 *   back at any time)
 */
template<typename T, size_t NLength, typename TFifo = SpScQueue<uint16_t, NLength>>
class ObjectPool
{
    using TMemPool = MemPool<sizeof(T), NLength, alignof(T), TFifo>;

public:
    /** @brief Allocate an object. */
    template<typename... Args>
    UniquePtr<T> allocate(Args&&... args)
    {
        auto ptr = memPool_.allocate();
        if (ptr)
        {
            new (ptr) T(std::forward<Args>(args)...);
        }
        return UniquePtr<T>{static_cast<T*>(ptr), &TMemPool::Deallocate, &memPool_};
    }

private:
    /** @brief The memory pool. */
    TMemPool memPool_;
};

} // namespace utils
} // namespace pipc

#endif // CONCURRENT_OBJECT_POOL_HPP
