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
/// @file      SkeletonField.hpp
/// @brief     Main class for proxy fields
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_SKELETON_FIELD_HPP
#define ARA_COM_SKELETON_FIELD_HPP

#include "ara/com/ISkeletonField.hpp"

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
 * \brief Main class as a 'frontend' for \see ISkeletonField.
 *
 * The bridge pattern is used to enable access to field methods without a pointer
 * derefence, as required per AR API specification. The class template can be instantiated
 * with Boolean selectors (e.g. HasGetter) to configure which public methods are available.
 * 
 * \remark
 * @ID{[SWS_CM_00115]}
 * @ID{[SWS_CM_00117]}
 */
template<typename FieldType_T, bool HasGetter = true, bool HasSetter = true, bool HasNotifier = true>
class SkeletonField
{
    // Make the Skeleton Factory a friend class
    template<ara::com::NetworkBindingEnum NetworkBinding>
    friend class ::com::service_deployment::SkeletonFactory;

private:
    /**
     * \brief Definitions of conditional enablers for the specific method availabilities
     *
     * These helper functions provide a private API to define and check which subfunctions
     * are available under which conditions.
     *
     * \remark These functions need to come first in the class definition, because they need to be available
     * as default template arguments.
     */
    static inline constexpr bool HasAllocate()
    {
        return HasNotifier;
    }
    static inline constexpr bool HasRegisterGetHandler()
    {
        return HasGetter;
    }
    static inline constexpr bool HasRegisterSetHandler()
    {
        return HasSetter;
    }
    static inline constexpr bool HasUpdate()
    {
        return (HasNotifier || HasGetter);
    }

public:
    using FieldType               = FieldType_T;
    using SampleType              = FieldType;
    using ISkeletonFieldUniquePtr = UniquePtr<ISkeletonField<FieldType>>;

    /** \brief Default constructor */
    SkeletonField() = default;

    /** \brief Constructor for taking over concrete implementation of ISkeletonField */
    SkeletonField(ISkeletonFieldUniquePtr&& f_pImpl) : pImpl(std::move(f_pImpl))
    {
    }

    /**
     * \brief Redirection to the field implementation's \see RegisterGetHandler() method
     *
     * \remark This method only exists, if the field is configured with a getter.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasRegisterGetHandler(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> RegisterGetHandler(std::function<ara::core::Future<FieldType>()> getHandler)
    {
        return pImpl->RegisterGetHandler(getHandler);
    }

    /**
     * \brief Redirection to the field implementation's \see RegisterSetHandler() method
     *
     * \remark This method only exists, if the field is configured with a getter.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasRegisterSetHandler(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> RegisterSetHandler(
        std::function<ara::core::Future<FieldType>(const FieldType& value)> setHandler)
    {
        return pImpl->RegisterSetHandler(setHandler);
    }

    /**
     * \brief Redirection to the field implementation's \see Update() method
     *
     * \remark This method only exists, if the field is configured with a notifier.
     *
     * \remark
     * @ID{[SWS_CM_00120]}
     */
    template<bool Conditional = HasUpdate(), typename std::enable_if<Conditional == true>::type* = nullptr>
    ara::core::Result<void> Update(const FieldType& value)
    {
        return pImpl->Update(value);
    }

    /** \brief Redirection to the field implementation's \see checkFieldReady() method */
    ara::core::Result<void> checkFieldReady()
    {
        return pImpl->checkFieldReady();
    }

    /** \brief Redirection to the field implementation's \see Offer() method */
    ara::core::Result<void> Offer()
    {
        return pImpl->Offer();
    }

    /** \brief Redirection to the field implementation's \see StopOffer() method */
    void StopOffer()
    {
        pImpl->StopOffer();
    }

protected:
    ISkeletonFieldUniquePtr pImpl;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_SKELETON_FIELD_HPP
