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
/// @file      SkeletonEvent.hpp
/// @brief     Front end class for skeleton events
/// @copyright Robert Bosch GmbH 2020
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_SKELETON_EVENT_HPP
#define ARA_COM_SKELETON_EVENT_HPP

#include "ara/com/ISkeletonEvent.hpp"

/** \brief Forward declaration of the SkeletonFactory class */
namespace com
{
namespace service_deployment
{
template<ara::com::NetworkBindingEnum NetworkBinding>
class SkeletonFactory;

} // namespace service_deployment
} // namespace com

namespace ara
{
namespace com
{
/**
 * \brief Front end class for \see ISkeletonEvent.
 *
 * The bridge pattern is used to enable access to event methods without a pointer
 * derefence, as required per AR API specification.
 *
 */
template<typename SampleType_T>
class SkeletonEvent : public ISkeletonEvent<SampleType_T>
{
    // Make the Skeleton Factory a friend class
    template<ara::com::NetworkBindingEnum NetworkBinding>
    friend class ::com::service_deployment::SkeletonFactory;

public:
    using SampleType          = SampleType_T;
    using ParentTypeUniquePtr = UniquePtr<ISkeletonEvent<SampleType>>;

    /** \brief Default constructor */
    SkeletonEvent() = default;

    /** \brief Constructor for taking over concrete implementation of ISkeletonEvent */
    SkeletonEvent(ParentTypeUniquePtr&& f_pImpl) : pImpl(std::move(f_pImpl))
    {
    }

    /** \brief Redirection to the event implementation's \see Send() method */
    ara::core::Result<void> Send(const SampleType& data)
    {
        return pImpl->Send(data);
    }

    /** \brief Redirection to the event implementation's \see Send() method */
    ara::core::Result<void> Send(ara::com::SampleAllocateePtr<SampleType> data)
    {
        return pImpl->Send(std::move(data));
    }

    /** \brief Redirection to the event implementation's \see Allocate() method */
    ara::core::Result<ara::com::SampleAllocateePtr<SampleType>> Allocate()
    {
        return pImpl->Allocate();
    }

    /** \brief Redirection to the event implementation's \see Offer() method */
    ara::core::Result<void> Offer()
    {
        return pImpl->Offer();
    }

    /** \brief Redirection to the event implementation's \see StopOffer() method */
    void StopOffer()
    {
        pImpl->StopOffer();
    }

protected:
    ParentTypeUniquePtr pImpl;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_SKELETON_EVENT_HPP
