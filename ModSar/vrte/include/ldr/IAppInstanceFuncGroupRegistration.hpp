//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      IAppInstanceFuncGroupRegistration.hpp
/// @brief     Declaration/Definition of IAppInstanceFuncGroupRegistration
/// @author    baetz
//=============================================================================
#ifndef LDR_IAPPINSTANCEFUNCGROUPREGISTRATION_HPP_
#define LDR_IAPPINSTANCEFUNCGROUPREGISTRATION_HPP_

#include "utils/FuncGroupId.hpp"
#include "utils/FuncGroupStateId.hpp"
#include "utils/AppInstId.hpp"
#include "utils/StdReturnType.hpp"

namespace exm {

namespace ldr {

/// @brief Interface to register an Application Instance at a certain FG State.
class IAppInstanceFuncGroupRegistration {
public:
    /// @brief Virtual destructor for interface.
    virtual ~IAppInstanceFuncGroupRegistration() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.

    /// @brief Add an application reference to an existing Function Group and Function Group State.
    /// @param[in] fgId         ID of the function group to which the application shall be added.
    /// @param[in] state        ID of the state to which the application shall be added.
    /// @param[in] application  ID of the application to add.
    /// @return OK on success, any other code indicates an error.
    virtual StdReturnType AddApplicationToState(FuncGroupId fgId,
            FuncGroupStateId state, AppInstId application) = 0;

    /// @brief Remove an application reference from a FunctionGroupState
    /// @param[in] fgId         ID of the function group from which the application shall be removed from.
    /// @param[in] state        ID of the state from which the application shall be removed from.
    /// @param[in] application  ID of the application to remove.
    /// @return OK on success, any other code indicates an error.
    virtual StdReturnType RemoveApplicationFromState(FuncGroupId fgId,
            FuncGroupStateId state, AppInstId application) = 0;
};

}  // namespace ldr

}  // namespace exm

#endif // IAPPINSTANCEFUNCGROUPREGISTRATION_HPP_
