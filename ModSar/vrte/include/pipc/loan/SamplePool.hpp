/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SHMEM_SAMPLE_POOL_HPP
#define PIPC_SHMEM_SAMPLE_POOL_HPP

#include "AdjustStride.hpp"
#include "SamplePtr.hpp"
#include "pipc/Config.hpp"
#include "pipc/Logger.hpp"
#include "pipc/queue/MpScQueue.hpp"
#include "pipc/shmem/MappedPtr.hpp"
#include "pipc/stack/MpMcStack.hpp"
#include "pipc/utils/String.hpp"

namespace pipc
{
namespace loan
{
/**
 * @brief Memory Pool for loaned samples.
 *
 * A SamplePool is similar to an ObjectPool in its semantics,
 * but it serves different purposes:
 *
 * It consists of storage memory for the samples, which lies in shared memory
 * to be available for subscribers to read from. A free list of indices allows
 * O(1) allocation and deallocation of samples, but it is in private memory of
 * the creditor and managed exclusively by it.
 *
 * It returns SamplePtrs with a Sample Id upon allocation. This ID
 * corresponds to the storage slot of the sample, which can be used to get the
 * effective address of it in memory (and its associated loan entry).
 *
 * A stride can be provided in the constructor indicating how many bytes the type T
 * occupies between each storage slot.
 * If no stride is given, sizeof(T) is used as the stride value aligned with alignof(T).
 *
 * When specifying a stride other than the implicit sizeof(T),
 * the intended use case is to have something similar to
 * a bounded array of variable size that extends beyond its sizeof(T) limits by overwriting
 * subsequent memory to its own object footprint in memory:
 *
 * template<U>
 * struct BoundedArray {
 *
 *     BoundedArray(size_t size)
 *     ...
 *
 *     size_t length;
 *     uint8_t data[sizeof(U)*16];
 * }
 *
 * The bounded array could be used as BoundedArray(sizeof(U)*128) with writing data way beyond
 * the byte array `data` in memory presumably on a shared memory page.
 *
 * This class ensures that at least the type T (such as T=BoundedArray) uses a stride
 * that is a multiple of alignof(T) (in example alignof(BoundedArray)) and so each storage
 * slot address satifies the alignment requirement of T (such as T=BoundedArray), i.e. the storage slot
 * address is a multiple of alignof(T).
 *
 * If the stride given in the constructor of this class is not a multiple of alignof(T), the stride is
 * rounded up to the next multiple of alignof(T) and a debug message is issues that
 * the stride given in the constructor was overwritten by this class.
 *
 * Similarly, if a stride smaller than sizeof(T) is given in the constructor, the stride is set to at
 * least sizeof(T) by the samplepool class and a debug message is issued that the stride value was overwritten
 * by this class.
 *
 * @remark
 * Thread safety: Depends on the FIFO used for the SamplePool.
 * Per default MPSC, which allows single context allocations and concurrent
 * deallocations.
 *
 * @todo
 * As of know the shared memory is directly created by the publisher and
 * accessible by using a path name. This will need to be taken over by a daemon
 * if we want to restrict read access later.
 *
 * @todo
 * Better name for this??
 *
 * @todo
 * Check MPMC stack vs. FIFO.
 */
template<typename T, size_t NLength, typename TFifo = MpScQueue<SampleId, NLength>>
class SamplePool
{
    using Deleter = utils::Command_1<void*, ReturnVal, SampleId>;

public:
    /** @brief Default constructor. */
    SamplePool() : sampleStorage_(), freeList_(), stride_(sizeof(T))
    {
    }

    /** @brief Constructor with a custom stride. */
    SamplePool(size_t stride) : sampleStorage_(), freeList_(), stride_(stride)
    {
    }

    /** @brief RAII-create a sample pool for the given path name. */
    SamplePool(const utils::StringView& path) : freeList_()
    {
        // round up stride to next multiple of alignof(T) if necessary
        init(path, calcStride<T>());
    }

    /** @brief RAII-create a sample pool for the given path name. */
    SamplePool(const utils::StringView& path, size_t stride) : freeList_()
    {
        init(path, stride);
    }

    /** @brief Set the path of the SamplePool. */
    void setPath(utils::StringView& path)
    {
        sampleStorage_.setName(path);
    }

    /** @brief Initialize the sample pool with the path & stride. */
    void init(const utils::StringView& path, size_t stride = sizeof(T))
    {
        sampleStorage_.setName(path);

        stride_ = adjustStride<T>(stride, "SamplePool");
    }

    /** @brief Create the SamplePool in shmem. */
    void create()
    {
        // Sample storage is R/W for the publisher proc's uid, R-only for others
        // TODO: Open in read-only mode needs to be supported first
        bool success = (sampleStorage_.create(0666, stride_ * NLength) == 0UL);
        if (success)
        {
            for (SampleId i = 0; i < NLength; i++)
            {
                freeList_.try_push(i);
            }
        }
        else
        {
            PIPC_LOG_ERROR() << "SamplePool: Could not create " << sampleStorage_.getName() << std::endl;
        }
    }

    /** @brief Open an existing SamplePool in shmem. */
    void open()
    {
        PIPC_LOG_VERBOSE() << "Opening sample pool at path" << sampleStorage_.getName() << ", size "
                           << stride_ * NLength << std::endl;
        bool success = (sampleStorage_.open(stride_ * NLength) == 0UL);
        if (success)
        {
            for (SampleId i = 0; i < NLength; i++)
            {
                freeList_.try_push(i);
            }
        }
        else
        {
            PIPC_LOG_ERROR() << "SamplePool: Could not open " << sampleStorage_.getName() << std::endl;
        }
    }

    /** @brief Allocate a sample and return a pointer to it. */
    template<typename... Args>
    SamplePtr<T> allocate(Args&&... args)
    {
        SampleId sampleId;
        auto ret = freeList_.try_pop(sampleId);
        // We still have a slot
        // TODO: Get rid of the else path, SamplePool needs to be a friend of
        // SamplePtr
        if (ret == ReturnVal::kOk)
        {
            T* ptr = reinterpret_cast<T*>(reinterpret_cast<size_t>(sampleStorage_.get()) + sampleId * stride_);
            new (ptr) T(std::forward<Args>(args)...);
            // TODO: SamplePtr constructor with in-place construction of the deleter
            Deleter deleter{&TFifo::Try_push, &freeList_};
            return SamplePtr<T>{ptr, deleter, sampleId};
        }
        // No samples available
        else
        {
            return SamplePtr<T>{};
        }
    }

    /**
     * @brief Get the address of a sample based on its sample id.
     *
     * Internal method required to convert a Loan back to a SamplePtr.
     *
     * @todo
     * This is required because Loan doesn't store SamplePtrs.
     * Change Loan to store SamplePtrs, which can be released for reusage?
     * Then we still need to modify where the SamplePtr points to, though.
     */
    size_t getAddress(SampleId sampleId)
    {
        return reinterpret_cast<size_t>(sampleStorage_.get()) + sampleId * stride_;
    }

    /** @brief Return the capacity of the sample storage in Bytes. */
    size_t capacity() const
    {
        return stride_ * NLength;
    }

    /** @brief Return the current size of the pool (as no. of available samples). */
    size_t size() const
    {
        return freeList_.size();
    }

private:
    /** @brief The sample storage in shared memory. */
    shmem::Mapping sampleStorage_;
    /** @brief The free list. */
    TFifo freeList_;
    /** @brief The size per element. */
    size_t stride_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_SHMEM_SAMPLE_POOL_HPP
