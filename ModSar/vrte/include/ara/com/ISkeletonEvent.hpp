//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      ISkeletonEvent.hpp
/// @brief     Interface class for skeleton events
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_ISKELETON_EVENT_HPP
#define ARA_COM_ISKELETON_EVENT_HPP

#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"

namespace ara
{
namespace com
{
/**
 * \brief Template interface for all skeleton-side events used in ara::com
 *
 * This class is used as an interface for skeleton events used in ara::com.
 * It provides all public interfaces as defined by AR.
 */
template<typename SampleType_T>
class ISkeletonEvent
{
public:
    using SampleType = SampleType_T;
    template<typename T>
    using SampleAllocateePtr = ara::com::SampleAllocateePtr<T>;

    ISkeletonEvent() = default;

    /** \brief No copy operations allowed */
    ISkeletonEvent(const ISkeletonEvent&) = delete;
    ISkeletonEvent& operator=(const ISkeletonEvent&) = delete;

    /** \brief No move operations allowed */
    ISkeletonEvent(const ISkeletonEvent&&) = delete;
    ISkeletonEvent& operator=(const ISkeletonEvent&&) = delete;

    virtual ~ISkeletonEvent() = default;

    /**
     * \brief Send method where the application is responsible for the data.
     *
     * Sends the given data over the binding. After sending data you can
     * reuse data. The underlying stack is copying the data into its own
     * buffer.
     *
     * \param data The data to be sent over the binding.
     *
     * \remark
     * @ID{[SWS_CM_00162]}
     */
    virtual ara::core::Result<void> Send(const SampleType& data) = 0;

    /**
     * \brief Send method where Communication Management is responsible for the data.

     * Send the given data over the binding. After sending data you
     * loose ownership and can’t access the data through
     * the SampleAllocateePtr anymore.
     *
     * \param data The data to be sent over the binding.
     *
     * \remark
     * @ID{[SWS_CM_90437]}
     *
     */
    virtual ara::core::Result<void> Send(SampleAllocateePtr<SampleType> data) = 0;

    /**
     * \brief Allocate data for event transfer.
     *
     * Allocates memory for one sample,
     * which can be used to send it via the binding.
     *
     * \remark Allocate() is especially useful, if data is explicitly
     * prepared for sending and no further processing is required afterwards.
     *
     * \return A std::unique_ptr-alike construct to a memory buffer with
     * memory space for a sample.
     *
     * \remark
     * @ID{[SWS_CM_90438]}
     */
    virtual ara::core::Result<ara::com::SampleAllocateePtr<SampleType>> Allocate() = 0;

    /**
     * \brief Callback for the event to offer the service.
     *
     * This callback gets called by the skeleton to prepare the event for
     * offering the associated service and verify a sane state of the event.
     *
     * \remark This is an internal callback function and shall not be called by the user.
     */
    virtual ara::core::Result<void> Offer() = 0;

    /**
     * \brief Callback for the event to stop offering the service.
     *
     * This callback gets called by the skeleton to stop the event offering
     * with the associated service.
     *
     * \remark This is an internal callback function and shall not be called by the user.
     */
    virtual void StopOffer() = 0;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_ISKELETON_EVENT_HPP
