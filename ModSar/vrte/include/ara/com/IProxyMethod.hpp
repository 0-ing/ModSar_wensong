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
/// @file      IProxyMethod.hpp
/// @brief     Interface class for method proxy binding
/// @copyright Robert Bosch GmbH 2020
/// @author    huy7si
//=============================================================================

#ifndef IPROXY_METHOD_HPP_INCLUDED
#define IPROXY_METHOD_HPP_INCLUDED

#include "ara/com/e2e/e2e_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/future.h"

namespace ara
{
namespace com
{

/**
 * \brief Template interface for method binding on proxy side:
 *          The main purpose is the provision of a clean AUTOSAR conformant interface. Furthermore, it
 *          enables the usage of different implementations on the transport path. It is supposed to be
 *          a pure interface to allow variations in the particular implementation.
 */
template<typename MethodOutput_T, typename... TArgs>
class IProxyMethod
{
public:
    using SMState = ara::com::e2e::SMState;

    virtual ~IProxyMethod() = default;

    /**
     * \brief   The () operator is the main interface to the application for method calls. As decribed
     *          in the adaptive AUTOSAR specification, the method call should look like a conventional
     *          method call on application side and shall return an ara::core::Future object wrapping
     *          the dedicated output type.
     * \remark
     * @ID{[SWS_CM_00196]}
     */
    virtual ara::core::Future<MethodOutput_T> operator()(const TArgs... args) = 0;

    /**
     * \brief Get the current state of the E2E State Machine
     *
     * \return State of the E2E State Machine
     *
     * \remark
     * @ID{[SWS_CM_90482]}
     * @ID{[SWS_CM_90483]}
     * @ID{[SWS_CM_90484]}
     */
    virtual SMState GetSMState() const = 0;
};

/**
 * \brief Interface specialization for void input
 */
template<typename MethodOutput_T>
class IProxyMethod<MethodOutput_T, void>
{
public:
    using SMState = ara::com::e2e::SMState;

    virtual ~IProxyMethod() = default;

    /**
     * \brief   The () operator is the main interface to the application for method calls. As described
     *          in the adaptive AUTOSAR specification, the method call should look like a conventional
     *          method call on application side and shall return an ara::core::Future object wrapping
     *          the dedicated output type.
     * \remark
     * @ID{[SWS_CM_00196]}
     */
    virtual ara::core::Future<MethodOutput_T> operator()() = 0;

    /**
     * \brief Get the current state of the E2E State Machine
     *
     * \return State of the E2E State Machine
     *
     * \remark
     * @ID{[SWS_CM_90482]}
     * @ID{[SWS_CM_90483]}
     * @ID{[SWS_CM_90484]}
     */
    virtual SMState GetSMState() const = 0;
};


} // namespace com
} // namespace ara

#endif // IPROXY_METHOD_HPP_INCLUDED
