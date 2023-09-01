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
/// @file      SkeletonMethod.hpp
/// @brief     Interface class for skeleton method
/// @copyright Robert Bosch GmbH 2020
/// @author    huy7si
//=============================================================================

#ifndef SKELETON_METHOD_HPP_INCLUDED
#define SKELETON_METHOD_HPP_INCLUDED

#include "ara/com/ISkeletonMethod.hpp"

#include <memory>

/** \brief Forward declaration of the SkeletonFactory class */
namespace com
{
namespace service_deployment
{
template<ara::com::NetworkBindingEnum Binding>
class SkeletonFactory;

} // namespace service_deployment
} // namespace com

namespace ara
{
namespace com
{
/**
 * \brief Class for fireforget method binding on skeleton side, which is also responsible for the lifetime of the
 *underlying objects.
 **/
template<typename... TArgs>
class SkeletonMethodFireForget : public ISkeletonMethodFireForget<TArgs...>
{
    // Make all Skeleton Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::SkeletonFactory;

public:
    /** \brief Default constructor */
    SkeletonMethodFireForget() = default;

    SkeletonMethodFireForget(UniquePtr<ISkeletonMethodFireForget<TArgs...>>&& iPtr) : pImpl(std::move(iPtr))
    {
    }

    /**
     * \brief   Interface to register a user configured function
     **/
    void RegisterProcessingFunction(std::function<void(const TArgs...)>&& f_func) override
    {
        pImpl->RegisterProcessingFunction(std::move(f_func));
    }

private:
    UniquePtr<ISkeletonMethodFireForget<TArgs...>> pImpl;
};

/**
 * \brief Class for method binding on skeleton side, which is also responsible for the lifetime of the underlying objects.
 **/
template<typename MethodOutput_T, typename... TArgs>
class SkeletonMethod : public ISkeletonMethod<MethodOutput_T, TArgs...>
{
    // Make all Skeleton Factories friend classes
    template<NetworkBindingEnum Binding>
    friend class ::com::service_deployment::SkeletonFactory;

public:
    /** \brief Default constructor */
    SkeletonMethod() = default;

    SkeletonMethod(UniquePtr<ISkeletonMethod<MethodOutput_T, TArgs...>>&& iPtr) : pImpl(std::move(iPtr))
    {
    }

    /**
     * \brief   Interface to register a user configured function
     **/
    void RegisterProcessingFunction(std::function<ara::core::Future<MethodOutput_T>(const TArgs...)>&& f_func) override
    {
        pImpl->RegisterProcessingFunction(std::move(f_func));
    }

private:
    UniquePtr<ISkeletonMethod<MethodOutput_T, TArgs...>> pImpl;
};
} // namespace com
} // namespace ara

#endif // SKELETON_METHOD_HPP_INCLUDED
