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
/// @file   InstanceIf.hpp
/// @brief  Definition of class InstanceIf
//=============================================================================

#ifndef _LDR_INSTANCEIF_HPP_
#define _LDR_INSTANCEIF_HPP_

#include <sched.h> // required by config for policy parameter in set_sched()
#include <sys/types.h>

#include "ldr/Arguments.hpp"
#include "ldr/Defs.hpp"
#include "ldr/LoaderDependency.hpp"
#include "ldr/EnvVars.hpp"
#include "utils/ExecInstanceAttr.hpp"
#include "utils/FuncGroupId.hpp"
#include "utils/FuncGroupStateId.hpp"
#include "utils/ProcessLimits.hpp"
#include "utils/ResourceGroupId.hpp"
#include "utils/StdReturnType.hpp"

namespace exm
{
namespace ldr
{
/// @brief abstract class responsible to pass instance information to InstancePriv class
/// @warning Do not create custom derivatives of this interface.
class InstanceIf
{
public:

    /// @brief default constructor
    InstanceIf() {}
    
    /// @brief destructor
    virtual ~InstanceIf() {} // Not covered: Deleting destructors of pure virtual base classes can not be called.
    
    /// @brief copy Constructor
    InstanceIf(const InstanceIf&) = delete;

    /// @brief Copy assignemt operator 
    InstanceIf& operator=(InstanceIf&)= delete;

    /// @brief initialize an instance
    /// @param[in] name_        Instance name
    /// @param[in] *path_       Path to executable
    /// @retval -1   error
    /// @retval 0    succesful
    virtual int32_t init(const char* name_, const char* path_) = 0;

    /// @brief Setting Application reporting state
    /// @param[in] isReportingFlag  true = process reports its Execution State to the ExM
    virtual void reportsProcessState(bool isReportingFlag) = 0;

    /// @brief Setting Application start and stop timeout
    /// @param[in] startTimeout Maximum time a process may take from being started to reporting RUNNING
    /// @param[in] stopTimeout  Maximum time a process may take from being stopped to reporting TERMINATING
    virtual void setTimeout(uint32_t startTimeout, uint32_t stopTimeout) = 0;

    /// @brief Setting Application to OneShot application
    virtual void setOneShot() = 0;

    /// @brief Setting Application role to EarlyProcess
    /// @brief DEPRECATED !! NPOT TO BE USED!!
    /// \deprecated
    virtual void setRoleAsEarlyProcess() = 0;

    /// @brief Setting Application role to SM
    virtual void setRoleAsSM() = 0;

    /// @brief Setting Application role to PHM
    virtual void setRoleAsPHM() = 0;

    /// @brief Setting Application role to ECUCFG
    virtual void setRoleAsECUCFG() = 0;

    ///   @brief Add dependency to an executable instance
    ///   @param[in]  instance Pointer to an <B>already registered</B> Instance object.
    ///   @param[in]  type = dependency type
    ///   @return  0 = success <BR>
    ///           -1 = failed
    ///
    ///   <B>Description</B>
    ///   - Appends the given instance to the list of dependencies for a particular instance.
    ///   - returns error code if list is full
    virtual int8_t add_dependency(InstanceIf* instance, const Dependency::Type type) = 0;

    /// @brief Register this element for a certain FG state.
    ///
    /// @traceid{SWS_EM_02254}@tracestatus{implemented}
    /// @uptrace{RS_EM_00101}
    ///
    /// Right now, only one FunctionGroup is allowed, so after one is set, only calls to the same group are allowed.
    /// @param[in] fgId    The FunctionGroup ID to register at.
    /// @param[in] stateId    The FG State ID to register .
    /// @return 0 on success, -1 on failure.
    virtual int32_t AddToFunctionGroupState(FuncGroupId fgId, FuncGroupStateId stateId) = 0;

    /// @brief Unregister this element for a certain FG state.
    ///
    /// Right now, only one FunctionGroup is allowed, so after one is set, only calls to the same group are allowed.
    /// @param[in] fgId    The FunctionGroup ID to unregistered from.
    /// @param[in] stateId    The FG State ID to unregister from.
    /// @return 0 on success, -1 on failure.
    virtual int32_t RemoveFromFunctionGroupState(FuncGroupId fgId, FuncGroupStateId stateId) = 0;

    /// @brief Sets the Resource Group for the according Process instance
    ///
    /// @param resGrpId    The Resource Grop ID to register at
    /// @return StdReturnType::OK on success, INVALID_ARGUMENTS on failures
    virtual StdReturnType SetResourceGroup(ResourceGroupId resGrpId) = 0;

    /// @brief Getting resGrpId
    /// @return resGrpId    The Resource Group ID for the Instance.
    virtual ResourceGroupId GetResourceGroupId() = 0;

    /// @brief Set uid and gid for the instance
    ///
    /// By default uid and gid will be initialized to zero, i.e. the exec instance will run with root permission.
    /// @param uid user id
    /// @param gid group id
    virtual void setCredentials(const uid_t uid, const gid_t gid) = 0;

    /// @brief Pushes a group to the supplementary group list of this process.
    ///
    /// @param gid group id
    /// @return StdReturnType::OK on success
    virtual StdReturnType pushSupplementaryGroup(const gid_t gid) = 0;

    /// @brief set the QNX type name for the security policy
    /// @param secpol_type_name_ Name of the QNX security policy type
    /// @return StdReturnType::OK on success
    virtual StdReturnType set_qnx_secpol_type(const char* secpol_type_name_) = 0;

    /// @brief Search for the uid attached to a user name (from /etc/passwd) and gid attached
    ///          to a group (from /etc/group) and set them for the instance
    ///
    /// @param p_user_name the user name for which to look up the uid
    /// @param p_group_name the group name for which to look up the gid
    /// @return 0 on success, -1 on failure
    virtual int32_t setCredentialsByName(const char* p_user_name, const char* p_group_name) = 0;

    /// @brief Sets a process limit
    /// @param[in] plimit Process limit to be set
    /// @return StdReturnType::OK on success
    virtual StdReturnType SetProcessLimit(const utils::ProcessLimit& plimit) = 0;

    virtual bool does_dependency_exist(InstanceIf* inst) = 0;

    /// @brief Get total number of dependencies of this executable instance
    /// @return Total number of dependencies of this executable instance

    virtual uint32_t get_dependency_cnt() = 0;

    /// @brief Get dependency for an instance
    /// @param deps_idx Index of the dependency
    /// @return Reference to an existing Dependency object

    virtual Dependency& get_dependency(uint32_t deps_idx) = 0;

    /// @brief Check the if the state of instance
    /// @return  true : if instance state is INSTALLED
    //           false: if instance state having other then INSTALLED
    virtual bool isInstalled() = 0;

    /// @brief Sets a execution error
    /// @param[in] executionError Process limit to be set
    /// @return StdReturnType::OK on success
    virtual StdReturnType SetProcessExecutionError(const uint32_t& executionError) = 0;

    Arguments arguments;              ///< Arguments object
    EnvVars envars;                   ///< Environment variable object
    utils::ExecInstanceAttr instattr; ///< Instance attibute object
};
} // namespace ldr
} // namespace exm

#endif /* header include protection */
