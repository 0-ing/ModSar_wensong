//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file   ILoaderControl.hpp
/// @brief  Definition of class ILoaderControl
//=============================================================================

#ifndef _ILOADERCONTROL_HPP_
#define _ILOADERCONTROL_HPP_

#include "ldr/ILoaderRegistrar.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/ISecurityPolicy.hpp"

namespace exm {
namespace ldr {

/// @brief interface between LDR and ExMConfig
///
/// This interface is called by LDR component to load the configuration of ExM
class ILoaderControl {
public:
    /// @brief destructor
    virtual ~ILoaderControl() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief start the registration of processes
    /// @param[in] reg = reference to realization of interface ILoaderRegistrar
    /// @return StdReturnType
    /// @retval OK = loading success
    /// @retval GENERAL_ERROR = loading failed
    virtual StdReturnType start(ILoaderRegistrar& reg) = 0;
    
    /// @brief join function
    /// @return StdReturnType
    /// @retval OK = joining success
    /// @retval GENERAL_ERROR = joining failed
    virtual StdReturnType join() = 0;
    
    /// @brief cancel function
    /// @return StdReturnType
    /// @retval OK = cancelling success
    /// @retval GENERAL_ERROR = cancelling failed
    virtual StdReturnType cancel() = 0;

    /// @brief Get the scheduling policy and priority
    /// @param[in] sch_policy = reference to the scheduling policy
    /// @param[in] sch_param = reference to the scheduling priority
    /// @return StdReturnType
    /// @retval OK = cancelling success
    /// @retval NOT_APPLICABLE = Don't change the scheduling
    /// @retval GENERAL_ERROR = Getting the scheduling policy and priority failed
    virtual StdReturnType get_em_sched(Integer& sch_policy, sched_param& sch_param) = 0;

    /// @brief Get a pointer to the utils::ISecurityPolicy interface realization.
    /// @return Interface realization. It may be a nullptr if it is not available.
    virtual utils::ISecurityPolicy* getISecurityPolicy() = 0;
};

} /* namespace */
} /* namespace */

#endif /* header include protection */
