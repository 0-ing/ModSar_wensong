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
/// @file      ISkeletonMethod.hpp
/// @brief     Interface class for method skeleton binding
/// @copyright Robert Bosch GmbH 2020
/// @author    huy7si
//=============================================================================

#ifndef ISKELETON_METHOD_HPP_INCLUDED
#define ISKELETON_METHOD_HPP_INCLUDED

#include "ara/com/types.h"
#include "ara/core/future.h"

namespace ara
{
namespace com
{
/**
 * \brief Template interface for fireforget method binding on skeleton side:
 *          The main purpose is the provision of a clean interface for the binding between
 *          non-generated and generated code. Furthermore, it enables the usage of different
 *          implementations on the transport path. It is supposed to be a pure interface to allow
 *          variations in the particular implementation.
 */
template<typename... TArgs>
class ISkeletonMethodFireForget
{
public:
    virtual ~ISkeletonMethodFireForget() = default;

    /**
     * \brief   Interface to register a user configured function, which will be provided as adaptive
     *          AUTOSAR method to the application. The registration is necessary to connect the non-
     *          generated code with the generated (configuration-dependent) code parts.
     */
    virtual void RegisterProcessingFunction(std::function<void(const TArgs...)>&& f_func) = 0;
};

/**
 * \brief Template interface for method binding on skeleton side:
 *          The main purpose is the provision of a clean interface for the binding between
 *          non-generated and generated code. Furthermore, it enables the usage of different
 *          implementations on the transport path. It is supposed to be a pure interface to allow
 *          variations in the particular implementation.
 */
template<typename MethodOutput_T, typename... TArgs>
class ISkeletonMethod
{
protected:
    /** @brief Method signature. */
    using Method = std::function<ara::core::Future<MethodOutput_T>(const TArgs...)>;

public:
    virtual ~ISkeletonMethod() = default;

    /**
     * \brief   Interface to register a user configured function, which will be provided as adaptive
     *          AUTOSAR method to the application. The registration is necessary to connect the non-
     *          generated code with the generated (configuration-dependent) code parts.
     */
    virtual void RegisterProcessingFunction(Method&& f_func)
        = 0;
};

} // namespace com
} // namespace ara

#endif
