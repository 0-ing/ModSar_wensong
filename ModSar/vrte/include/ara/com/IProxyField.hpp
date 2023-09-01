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
/// @file      IProxyField.hpp
/// @brief     Interface class for proxy fields
/// @copyright Robert Bosch GmbH 2021
/// @author    crg2fe
//=============================================================================

#ifndef ARA_COM_IPROXY_FIELD_HPP
#define ARA_COM_IPROXY_FIELD_HPP

#include "IProxyEvent.hpp"
#include "ara/core/promise.h"

namespace ara
{
namespace com
{
/** \brief Forward declaration to make ProxyField a friend class of this interface. */
template<typename FieldType_T, bool HasGetter, bool HasSetter, bool HasNotifier>
class ProxyField;

/**
 * \brief Template interface for all proxy-side fields used in ara::com.
 *
 * This class is used as an interface for proxy fields used in ara::com.
 * It provides all public interfaces as defined by AR.
 *
 * \remark The interface IProxyField is an extension of IProxyEvent, as it provides all of the
 * methods from IProxyEvent plus additional methods.
 */
template<typename FieldType_T>
class IProxyField : public IProxyEvent<FieldType_T>
{
public:
    /** \brief Declarations for readability and forwarding to derived classes */
    using FieldType   = FieldType_T;
    using IProxyEvent = ara::com::IProxyEvent<FieldType>;
    using typename IProxyEvent::ComErrc;
    using typename IProxyEvent::SamplePointer;
    using typename IProxyEvent::SMState;
    using typename IProxyEvent::SubscriptionState;

    virtual ~IProxyField() = default;

    /**
     * \brief Method to get the value of a field.
     *
     * \remark
     * @ID{[SWS_CM_00112]}
     */
    virtual ara::core::Future<FieldType> Get() = 0;

    /**
     * \brief Method to set the value of a field.
     *
     * \remark
     * @ID{[SWS_CM_00113]}
     */
    virtual ara::core::Future<FieldType> Set(const FieldType& value) = 0;
};

} // namespace com
} // namespace ara

#endif // ARA_COM_IPROXY_FIELD_HPP
