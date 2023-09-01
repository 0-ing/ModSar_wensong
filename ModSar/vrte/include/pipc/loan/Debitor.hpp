/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_LOAN_DEBITOR_HPP
#define PIPC_LOAN_DEBITOR_HPP

#include "AdjustStride.hpp"
#include "LoanId.hpp"
#include "LoanedSamplePtr.hpp"
#include "pipc/shmem/MappedPtr.hpp"
#include "pipc/utils/Expect.hpp"

namespace pipc
{
namespace loan
{
/**
 * @brief Debitor class for receiving loans.
 *
 * The debitor knows where to find the associated creditor's sample pointers in
 * shared memory. It can receive loan IDs and convert them to loaned sample
 * pointers for the user to work with.
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
 */
template<typename T, size_t NLength>
class Debitor
{
    using TDeleter = typename LoanedSamplePtr<T>::TDeleter;
    static_assert(sizeof(T) >= alignof(T), "Check again what the compiler gives for sizeof and alignof..");

public:
    /** @brief Default constructor. */
    Debitor() : sampleStorage_(), stride_(calcStride<T>())
    {
    }

    /** @brief Constructor with the given path and a default stride. */
    Debitor(const utils::StringView& path)
    {
        // stride is at least sizeof(T) and then aligned to alignof(T)
        init(path, calcStride<T>());
    }

    /** @brief Constructor with the given path and a custom stride. */
    Debitor(const utils::StringView& path, size_t stride)
    {
        init(path, stride);
    }

    /** @brief Init the Debitor with the given path name & optional stride. */
    void init(const utils::StringView& path, size_t stride = sizeof(T))
    {
        stride_ = adjustStride<T>(stride, "Debitor");
        sampleStorage_.setName(path);
    }

    /**
     * @brief Open the sample storage.
     *
     * @return True if opening was successful, false if not.
     */
    bool openSampleStorage()
    {
        // TODO:
        // A subscriber should open the sample storage only in read only mode,
        // but the mmap fails with errno 13 in O_RDONLY
        PIPC_LOG_VERBOSE() << "Opening sample storage at path" << sampleStorage_.getName() << ", size "
                         << stride_ * NLength << std::endl;
        auto ret = sampleStorage_.open(stride_ * NLength);
        return (ret == 0);
    }

    /** @brief Convert a Loan Id to a loaned sample pointer. */
    LoanedSamplePtr<T> getSamplePtr(LoanId loanId, const TDeleter& deleter)
    {
        return LoanedSamplePtr<T>{reinterpret_cast<T*>(getRawPtr(loanId)), deleter, loanId};
    }

    /** @brief Convert a Loan Id to a raw sample pointer. */
    T* getRawPtr(LoanId loanId)
    {
        size_t address = reinterpret_cast<size_t>(sampleStorage_.get());
        size_t idx     = loanId.getSampleId();
        if (EXPECT_UNLIKELY(!address || (idx >= NLength)))
        {
            return nullptr;
        }
        address += idx * stride_;
        return reinterpret_cast<T*>(address);
    }

private:
    /** @brief The sample storage in shared memory. */
    shmem::Mapping sampleStorage_;
    /** @brief The offset per slot in the sample storage. */
    size_t stride_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_LOAN_DEBITOR_HPP
