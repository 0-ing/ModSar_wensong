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
/// @file      ISkeletonField.hpp
/// @brief     Interface class for skeleton fields
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_ISKELETON_FIELD_HPP
#define ARA_COM_ISKELETON_FIELD_HPP

#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/result.h"

namespace ara
{
namespace com
{
/**
 * \brief Template interface for all skeleton-side fields used in ara::com.
 *
 * This class is used as an interface for skeleton fields used in ara::com.
 * It provides all public interfaces as defined by AR.
 *
 * \remark
 * @ID{[SWS_CM_00128]}
 * @ID{[SWS_CM_00129]}
 */
template<typename FieldType_T>
class ISkeletonField
{
public:
    using FieldType  = FieldType_T;
    using SampleType = FieldType;
    template<typename T>
    using SampleAllocateePtr = ara::com::SampleAllocateePtr<T>;
    template<typename T>
    using Result = ara::core::Result<T, ComErrc>;

    virtual ~ISkeletonField() = default;

    /**
     * \brief Method to register a GetHandler.
     *
     * The GetHandler gets called whenever the Communication Management receives a Get request.
     *
     * \remark
     * @ID{[SWS_CM_00114]}
     */
    virtual ara::core::Result<void> RegisterGetHandler(std::function<ara::core::Future<FieldType>()> getHandler) = 0;

    /**
     * \brief Method to register a SetHandler.
     *
     * The SetHandler gets called whenever the Communication Management receives a Set request.
     *
     * \remark
     * @ID{[SWS_CM_00116]}
     */
    virtual ara::core::Result<void>
        RegisterSetHandler(std::function<ara::core::Future<FieldType>(const FieldType& value)> setHandler) = 0;

    /**
     * \brief Update function for the field.
     *
     * This method initiates the transmission of updated field data to the subscribers.
     * It also updates the field's internal value, if the field has a getter and no custom getter has been registered.
     *
     * \remark
     * @ID{[SWS_CM_00119]}
     * @ID{[SWS_CM_00162]}
     */
    virtual ara::core::Result<void> Update(const FieldType& value) = 0;

    /**
     * \brief Callback to check the field state in order to offer the service
     *
     * This callback gets called by the skeleton to check if the field is in a sane state
     * for offering the associated service
     *
     * \remark This is an internal callback function and shall not be called by the user.
     * @ID{[SWS_CM_00128]}
     * @ID{[SWS_CM_00129]}
     */
    virtual ara::core::Result<void> checkFieldReady() = 0;

    /**
     * \brief Callback for the field to offer the service.
     *
     * This callback gets called by the skeleton to start the field offering
     * with the associated service.This callback is performed after checking the field state
     * with checkFieldReady().
     *
     * \remark This is an internal callback function and shall not be called by the user.
     */
    virtual ara::core::Result<void> Offer() = 0;

    /**
     * \brief Callback for the field to stop offering the service.
     *
     * This callback gets called by the skeleton to stop the field offering
     * with the associated service.
     *
     * \remark This is an internal callback function and shall not be called by the user.
     */
    virtual void StopOffer() = 0;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_ISKELETON_FIELD_HPP
