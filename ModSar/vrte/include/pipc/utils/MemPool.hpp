#ifndef PIPC_UTILS_MEMPOOL_HPP
#define PIPC_UTILS_MEMPOOL_HPP

#include "pipc/queue/SpScQueue.hpp"

#include <cstddef>
#include <cstdint>

namespace pipc
{
namespace utils
{
/**
 * @brief MemPool for static storage allocation.
 *
 * The MemPool can allocate up to NLength chunks of memory of size NSize each.
 * It uses a FIFO with a free list for a O(1) allocation time. The type of FIFO
 * is a SPSC by default and can be adjusted with the TFifo parameter.
 */
template<size_t NSize, size_t NLength, size_t NAlign = 8U, typename TFifo = SpScQueue<uint16_t, NLength>>
class MemPool
{
public:
    /** @brief Constructor, which initializes the free list. */
    MemPool()
    {
        for (uint16_t i = 0; i < NLength; i++)
        {
            freeList_.try_push(i);
        }
    }

    /** @brief Allocate a chunk and return its address. */
    void* allocate()
    {
        uint16_t index;
        auto ret = freeList_.try_pop(index);
        return ((ret == ReturnVal::kOk) ? &storage_[index] : nullptr);
    }

    /** @brief Allocate a chunk and return its address & index of the slot. */
    void* allocate(uint16_t& index)
    {
        auto ret = freeList_.try_pop(index);
        return ((ret == ReturnVal::kOk) ? &storage_[index] : nullptr);
    }

    /** @brief Deallocate a chunk by address. */
    void deallocate(void* address)
    {
        size_t diff    = reinterpret_cast<size_t>(address) - reinterpret_cast<size_t>(storage_);
        size_t diffCmp = reinterpret_cast<size_t>(&storage_[1]) - reinterpret_cast<size_t>(&storage_[0]);
        uint16_t idx   = static_cast<uint16_t>(diff / diffCmp);
        deallocate(idx);
    }

    /** @brief Deallocate a chunk by index. */
    void deallocate(uint16_t index)
    {
        freeList_.try_push(index);
    }

    /** @brief Wrapper to call a deallocation. */
    static void Deallocate(MemPool* obj, void* address)
    {
        obj->deallocate(address);
    }

private:
    /** @brief The storage for all elements. */
    typename std::aligned_storage<NSize, NAlign>::type storage_[NLength];
    /** @brief The free list. */
    TFifo freeList_;
};

} // namespace utils
} // namespace pipc

#endif // PIPC_UTILS_MEMPOOL_HPP
