//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      SamplePtr.hpp
/// @brief     Class for Sample Pointers
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_SAMPLE_PTR_HPP
#define ARA_COM_SAMPLE_PTR_HPP

#include "ara/com/e2e/e2e_error_domain.h"
#include "pipc/loan/LoanedSamplePtr.hpp"

#include <functional> // needed for std::function

namespace ara
{
namespace com
{
namespace internal
{
/**
 * \brief Implementation for Sample Pointers used in ara::com.
 *
 * This class provides the SamplePtr implementation as required per AR specification.
 * It is in internal namespace, because we provide it with a const template parameter as public interface.
 *
 * \todo investigate how we can have the pipc::loan::SamplePtr as a member of the ara::com::SamplePtr
 *
 * \remark
 * @ID{[SWS_CM_00306]}
 * @ID{[SWS_CM_90420]}
 */
template<typename SampleType_T>
class SamplePtr : protected pipc::loan::LoanedSamplePtr<SampleType_T>
{
public:
    using SampleType         = SampleType_T;
    using ProfileCheckStatus = ara::com::e2e::ProfileCheckStatus;
    using PipcLoanedPtr      = pipc::loan::LoanedSamplePtr<SampleType>;
    using DeleteAction       = std::function<void()>;

    /// @brief Default constructor.
    constexpr SamplePtr() noexcept : PipcLoanedPtr()
    {
    }

    /// @brief Semantically equivalent to default constructor.
    constexpr SamplePtr(std::nullptr_t) noexcept : PipcLoanedPtr(nullptr)
    {
    }

    /// @brief Constructor with a PIPC LoanedPtr.
    inline SamplePtr(PipcLoanedPtr&& ptr, DeleteAction deleteAction = nullptr) noexcept
        : PipcLoanedPtr(std::forward<PipcLoanedPtr>(ptr)), deleteAction_(deleteAction)
    {
    }

    /// @brief Destructor
    ~SamplePtr()
    {
        Reset(nullptr);
    }

    /// @brief No copy operations.
    SamplePtr(const SamplePtr&) = delete;
    SamplePtr& operator=(const SamplePtr&) = delete;

    /// @brief Move operations are allowed.
    SamplePtr(SamplePtr&& other) noexcept
        : PipcLoanedPtr(std::move(other)),
          checkStatus_(other.checkStatus_),
          deleteAction_(std::move(other.deleteAction_))
    {
    }

    /// @brief Move assignment operator.
    SamplePtr& operator=(SamplePtr&& other) noexcept
    {
        if (this != &other)
        {
            Reset(nullptr);
            PipcLoanedPtr::operator=(std::move(other));
            checkStatus_           = other.checkStatus_;
            deleteAction_          = std::move(other.deleteAction_);
        }
        return *this;
    }

    /// @brief Assignment of nullptr_t.
    SamplePtr& operator=(std::nullptr_t) noexcept
    {
        Reset(nullptr);
        return *this;
    }

    /// @brief Dereference the stored pointer.
    using PipcLoanedPtr::operator*;
    using PipcLoanedPtr::operator->;

    /// @brief Check if the stored pointer is null.
    using PipcLoanedPtr::operator bool;

    /// @brief Swap the managed object.
    void Swap(SamplePtr<SampleType>& other) noexcept
    {
        std::swap(*this, other);
    }

    /// @brief Replace the managed object.
    void Reset(std::nullptr_t) noexcept
    {
        if (this->ptr_)
        {
            if (deleteAction_)
            {
                deleteAction_();
            }
        }
        checkStatus_ = ProfileCheckStatus::kCheckDisabled;
        PipcLoanedPtr::reset(nullptr);
    }

    /// @brief Return the stored object.
    constexpr SampleType* Get() const noexcept
    {
        return PipcLoanedPtr::get();
    }

    /**
     * @brief Return the e2e protection check result.
     *
     * @remark
     * @ID{[SWS_CM_90420]}
     */
    constexpr ProfileCheckStatus GetProfileCheckStatus() const noexcept
    {
        return checkStatus_;
    }

protected:
    /** @brief The ProfileCheckStatus of the sample. */
    ProfileCheckStatus checkStatus_{ProfileCheckStatus::kCheckDisabled};
    /**
     * @brief An optional action if the pointer is deleted.
     *
     * @remark
     * In some contexts like EventSubscriber we need an additional counter
     * to be able to report GetFreeSampleCount.
     * This is why we need an optional action to be triggered upon deletion.
     */
    DeleteAction deleteAction_{nullptr};
};

} // namespace internal
} // namespace com
} // namespace ara

#endif // ARA_COM_SAMPLE_PTR_HPP
