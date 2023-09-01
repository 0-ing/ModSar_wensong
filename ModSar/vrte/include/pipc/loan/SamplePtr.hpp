/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SHMEM_SAMPLE_PTR_HPP
#define PIPC_SHMEM_SAMPLE_PTR_HPP

#include "LoanId.hpp"
#include "pipc/queue/internal/ReturnVal.hpp"
#include "pipc/utils/Command.hpp"
#include "pipc/utils/UniquePtr.hpp"

namespace pipc
{
namespace loan
{
/** @brief Forward declaration of Creditor. */
template<size_t NLoans>
class Creditor;

/**
 * @brief Pointer to a sample of a sample pool.
 *
 * A Sample Pointer is similar to a UniquePtr, but it additionally contains
 * a sample ID, which is equal to the index of the sample's slot index in its
 * SamplePool. The index can be used for O(1) restitutions in the loan
 * management logic as well as a O(1) reconstruction of the sample's
 * address at the receiver side.
 *
 * @todo
 * Currently a separate implementation, check if we can integrate Command_X into
 * UniquePtr.
 */
template<typename T>
class SamplePtr : public utils::internal::UniquePtrBase<T, utils::Command_1<void*, ReturnVal, SampleId>>
{
public:
    using Deleter = utils::Command_1<void*, ReturnVal, SampleId>;

private:
    using BaseClass = utils::internal::UniquePtrBase<T, Deleter>;
    template<size_t NLoans>
    friend class Creditor;

public:
    /** @brief Default constructor. */
    constexpr SamplePtr() noexcept : BaseClass::UniquePtrBase(), sampleId_()
    {
    }

    /** @brief Semantically equivalent to default constructor. */
    constexpr SamplePtr(std::nullptr_t) noexcept : BaseClass::UniquePtrBase(nullptr), sampleId_()
    {
    }

    /** @brief Constructor with the address and deleter information. */
    SamplePtr(T* ptr, const Deleter& deleter, SampleId sampleId) noexcept
        : BaseClass::UniquePtrBase(ptr, deleter), sampleId_(sampleId)
    {
    }

    /** @brief Copy constructor is deleted. */
    SamplePtr(const SamplePtr&) = delete;

    /** @brief Move operations are allowed. */
    SamplePtr(SamplePtr&& other) noexcept : BaseClass::UniquePtrBase(std::move(other)), sampleId_(other.sampleId_)
    {
    }

    /** @brief Reset upon destruction. */
    ~SamplePtr() noexcept
    {
        reset(nullptr);
    }

    /** @brief Default copy assignment operator is deleted. */
    SamplePtr& operator=(const SamplePtr&) = delete;

    /** @brief Assignment of nullptr_t. */
    SamplePtr& operator=(std::nullptr_t) noexcept
    {
        reset(nullptr);
        return *this;
    }

    /** @brief Move assignment operator. */
    SamplePtr& operator=(SamplePtr&& other) noexcept
    {
        if (this != &other)
        {
            reset(nullptr);
            BaseClass::operator=(std::move(other));
            sampleId_          = other.sampleId_;
        }

        return *this;
    }

    /**
     * @brief Convert the SamplePtr to a different type.
     *
     * @todo
     * Limit cast operator to T<->Placeholder, so we can't do a direct
     * T1<->T2?
     */
    template<typename U>
    constexpr operator SamplePtr<U>&()
    {
        return *reinterpret_cast<SamplePtr<U>*>(this);
    }

    /** @brief Return the sample ID. */
    SampleId getSampleId()
    {
        return sampleId_;
    }

    /** @brief Replace the managed object. */
    void reset(std::nullptr_t) noexcept
    {
        if (this->ptr_ != nullptr)
        {
            this->ptr_->~T();
            this->deleter_(sampleId_);
            this->ptr_ = nullptr;
        }
    }

    /**
     * @brief Return the pointer and invalidate this object.
     *
     * The deleter must be retrieved, so that proper deletion can still happen.
     */
    T* release(Deleter& deleter)
    {
        T* retVal  = this->ptr_;
        this->ptr_ = nullptr;
        deleter    = this->deleter_;
        return retVal;
    }

private:
    /** @brief Return the pointer and invalidate this object. */
    T* release()
    {
        T* retVal  = this->ptr_;
        this->ptr_ = nullptr;
        return retVal;
    }

    /** @brief Sample ID. */
    SampleId sampleId_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_SHMEM_SAMPLE_PTR_HPP
