/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_SHMEM_LOANED_SAMPLE_PTR_HPP
#define PIPC_SHMEM_LOANED_SAMPLE_PTR_HPP

#include "LoanId.hpp"
#include "pipc/utils/UniquePtr.hpp"

namespace pipc
{
namespace loan
{
/**
 * @brief Loaned Sample Pointer.
 *
 * A loaned sample ptr represents access to a sample from the debitor's
 * perspective. It holds its assigned loan ID and triggers a function call
 * with it as argument upon destruction.
 */
template<typename T>
class LoanedSamplePtr : public utils::internal::UniquePtrBase<T, utils::Command_1<void*, void, LoanId>>
{
public:
    using TDeleter = utils::Command_1<void*, void, LoanId>;

private:
    using BaseClass = utils::internal::UniquePtrBase<T, TDeleter>;

public:
    /** @brief Default constructor. */
    constexpr LoanedSamplePtr() noexcept : BaseClass::UniquePtrBase(), loanId_()
    {
    }

    /** @brief Semantically equivalent to default constructor. */
    constexpr LoanedSamplePtr(std::nullptr_t) noexcept : BaseClass::UniquePtrBase(nullptr), loanId_()
    {
    }

    /** @brief Constructor with pointer and loan ID. */
    LoanedSamplePtr(T* ptr, const TDeleter& deleter, LoanId loanId) noexcept
        : BaseClass::UniquePtrBase(ptr, deleter), loanId_(loanId)
    {
    }

    /** @brief Copy constructor is deleted. */
    LoanedSamplePtr(const LoanedSamplePtr&) = delete;

    /** @brief Move operations are allowed. */
    LoanedSamplePtr(LoanedSamplePtr&& other) noexcept
        : BaseClass::UniquePtrBase(std::move(other)), loanId_(other.loanId_)
    {
    }

    /** @brief Reset upon destruction. */
    ~LoanedSamplePtr() noexcept
    {
        reset(nullptr);
    }

    /** @brief Default copy assignment operator is deleted. */
    LoanedSamplePtr& operator=(const LoanedSamplePtr&) = delete;

    /** @brief Assignment of nullptr_t. */
    LoanedSamplePtr& operator=(std::nullptr_t) noexcept
    {
        reset(nullptr);
        return *this;
    }

    /** @brief Move assignment operator. */
    LoanedSamplePtr& operator=(LoanedSamplePtr&& other) noexcept
    {
        if (this != &other)
        {
            reset(nullptr);
            BaseClass::operator=(std::move(other));
            loanId_            = other.loanId_;
        }
        return *this;
    }

    /** @brief Replace the managed object. */
    void reset(std::nullptr_t) noexcept
    {
        if (this->ptr_ != nullptr)
        {
            this->deleter_(loanId_);
            this->ptr_ = nullptr;
        }
    }

private:
    /** @brief The associated loan ID. */
    LoanId loanId_;
};

} // namespace loan
} // namespace pipc

#endif // PIPC_SHMEM_LOANED_SAMPLE_PTR_HPP
