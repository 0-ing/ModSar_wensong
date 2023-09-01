//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      Instance.hpp
/// @brief     Public header of the execution manager Instance Class
/// @copyright Robert Bosch GmbH  2018
/// @author    Arnaud Riess

#ifndef _LDR_INSTANCE_HPP_INCLUDED
#define _LDR_INSTANCE_HPP_INCLUDED

#include "ldr/Arguments.hpp"
#include "ldr/Defs.hpp"
#include "ldr/LoaderDependency.hpp"
#include "ldr/EnvVars.hpp"
#include "../inc/ldr/IAppInstanceFuncGroupRegistration.hpp"
#include "../inc/ldr/InstanceIf.hpp"
#include "utils/AppRole.hpp"
#include "utils/ApplicationInfo.hpp"
#include "utils/ExecInstanceAttr.hpp"
#include "utils/FuncGroupId.hpp"
#include "utils/FuncGroupStateId.hpp"
#include "utils/ResourceGroupId.hpp"
#include "utils/String.hpp"
#include "ldr/StateMachine.hpp"
#include "cfgldr/IConfigLoaderDriver.hpp"

#include <sys/types.h>

namespace exm
{
namespace ldr
{
/// @brief public class responsible to pass instance information to InstancePriv class
class Instance : public InstanceIf // Not covered: There is no explicit destructor. Only the deleting destructor is not covered. We don't use the heap.
{
public:
    Instance();
    
    virtual ~Instance(){}

    /// @brief No copy constructor needed.
    Instance(const Instance&) = delete;

    /// @brief No copy assignment operator needed.
    Instance& operator=(const Instance&) = delete;

    /// @brief Returns the mfe::Database id of this instance
    /// @return Database id of this instance
    id_t get_dbid() const { return dbid; }

    /// @brief sets the mfe::Database id of this instance
    /// @param[in]   id     Database ID
    void set_dbid(id_t id) { dbid = id; }

    /// @brief Initialise Instance
    /// @param[in] name_        Instance name
    /// @param[in] *path_       Path to executable
    /// @retval -1   error
    /// @retval 0    succesful
    int32_t init(const char* name_, const char* path_) override;

    /// @brief Return the path of an executable
    /// @return Path
    char* get_path() { return arguments.get_arg(0U); }

    /// @brief Returns the instance name of an Instance
    /// @return Instance name
    char* get_instance_name() { return instance_name; }

    /// @brief Setting Application reporting state
    /// @param[in] isReportingFlag  set to true if a process reports its Execution State to the ExM
    void reportsProcessState(bool isReportingFlag) override { appInfo.isReporting = isReportingFlag; };

    /// @brief Setting Application start and stop timeout
    /// @param startTimeout Start Timeout (in ms)
    /// @param stopTimeout  Stop Timeout (in ms)
    void setTimeout(uint32_t startTimeout, uint32_t stopTimeout) override;

    /// @brief Setting Application to OneShot application
    void setOneShot() override { appInfo.isOneShot = true; }

    /// @brief Setting Application role to EarlyProcess
    /// @brief DEPRECATED !! NOT TO BE USED!
    /// \deprecated
    void setRoleAsEarlyProcess() override { approle.Insert(utils::AppRole(utils::AppRole::EarlyProcess)); };

    /// @brief Setting Application role to SM
    void setRoleAsSM() override { approle.Insert(utils::AppRole(utils::AppRole::SM)); };

    /// @brief Setting Application role to PHM
    void setRoleAsPHM() override { approle.Insert(utils::AppRole(utils::AppRole::PHM)); };

    /// @brief Setting Application role to ECUCFG
    void setRoleAsECUCFG() override { approle.Insert(utils::AppRole(utils::AppRole::EcuCfg)); };

    /// @brief Checks if a dependency is already registered.
    /// @return Whether the dependency is already registered.
    bool does_dependency_exist(InstanceIf* instance) override;

    /// @brief Get dependency for an instance
    /// @param deps_idx Index of the dependency
    /// @return Reference to an existing Dependency object
    Dependency& get_dependency(uint32_t deps_idx) override;

    /// @brief Resets all relevant variables to their initial value
    void resetAllFields();

    ///   @brief Add dependency to an executable instance
    ///   @param  instance Pointer to an <B>already registered</B> Instance object.
    ///   @param  type = dependency type
    ///   @return  0 = success <BR>
    ///           -1 = failed
    ///
    ///   <B>Description</B>
    ///   - Appends the given instance to the list of dependencies for a particular instance.
    ///   - returns error code if list is full
    int8_t add_dependency(InstanceIf* instance, const Dependency::Type type) override;

    /// @brief Get total number of dependencies of this executable instance
    /// @return Total number of dependencies of this executable instance
    uint32_t get_dependency_cnt() override { return dependencies_cnt; }

    /// @brief Get total number of resolvers for an instance
    /// @return Total number of resolvers for an instance
    uint32_t get_resolver_cnt() { return resolver_cnt; }

    /// @brief Get the type of a specific resolver
    /// @param[in] idx Index of the resolver
    /// @param[out] type Type of the dependency (output parameter)
    /// @return 0 for success
    /// @return -1 fir failure
    int8_t get_resolver_type(uint32_t idx, Dependency::Type& type);

    /// @brief Get the id of a specific resolver
    /// @param[in] idx Index of the resolver
    /// @return id of the resolver, or mfe::INVALID_ID for failure.
    id_t get_resolver_id(uint32_t idx);

    /// @brief Get the current startup config name used
    /// @return a char pointer to the startup configuration name
    char* get_current_startupconfigname(){ return const_cast<char*>(currentStartupConfigurationName.AsStr()); }

    /// @brief Register this element for a certain FG state.
    ///
    /// Right now, only one FunctionGroup is allowed, so after one is set, only calls to the same
    /// group are allowed.
    /// @param[in] fgId    The FunctionGroup ID to register at.
    /// @param[in] stateId    The FG State ID to register .
    /// @return 0 on success, -1 on failure.
    int32_t AddToFunctionGroupState(FuncGroupId fgId, FuncGroupStateId stateId) override;

    /// @brief Unregister this element for a certain FG state.
    ///
    /// Right now, only one FunctionGroup is allowed, so after one is set, only calls to the same group are allowed.
    /// @param[in] fgId    The FunctionGroup ID to unregistered from.
    /// @param[in] stateId    The FG State ID to unregister from.
    /// @return 0 on success, -1 on failure.
    int32_t RemoveFromFunctionGroupState(FuncGroupId fgId, FuncGroupStateId stateId) override;

    /// @brief Call used during installation to register remembered FG states in MFE.
    ///
    /// Not being registered at any FG State is NOT an error.
    /// @param[in] fgRegister Pointer to the register to work on.
    /// @return 0 on success, -1 on failure.
    int32_t RegisterFgStates(IAppInstanceFuncGroupRegistration* fgRegister);

    /// @brief Call used during uninstallation from FG states in MFE.
    /// @param[in] fgRegister Pointer to the register to work on.
    /// @return 0 on success, -1 on failure.
    int32_t UnregisterFgStates(IAppInstanceFuncGroupRegistration* fgRegister);

    /// @brief Getter for registeredFuncGroup
    /// @return FunctionGroup ID
    FuncGroupId GetRegisteredFuncGroup();

    /// @brief Set uid and gid for the instance
    /// @param uid user id
    /// @param gid group id
    void setCredentials(const uid_t uid, const gid_t gid) override;

    /// @brief set the QNX type name for the security policy
    /// @param secpol_type_name_ Name of the QNX security policy type
    /// @return StdReturnType::OK on success
    StdReturnType set_qnx_secpol_type(const char* secpol_type_name_) override;

    /// @brief Sets the Resource Group for the according Process instance
    /// @param resGrpId    The Resource Grop ID to register at
    /// @return StdReturnType::OK on success , GENERAL_ERROR on failure
    StdReturnType SetResourceGroup(ResourceGroupId resGrpId) override;

    /// @brief Getting resGrpId
    /// @return resGrpId    The Resource Group ID for the Instance.
    ResourceGroupId GetResourceGroupId() override;

    /// @brief Search for the uid attached to a user name (from /etc/passwd) and gid attached
    ///          to a group (from /etc/group) and set them for the instance
    /// @param p_user_name the user name for which to look up the uid
    /// @param p_group_name the group name for which to look up the gid
    /// @return 0 on success, -1 on failure
    int32_t setCredentialsByName(const char* p_user_name, const char* p_group_name) override;

    /// @brief Pushes a group to the supplementary group list of this process.
    /// @param gid group id
    /// @return StdReturnType::OK on success
    StdReturnType pushSupplementaryGroup(const gid_t gid) override;

    /// @brief Sets a process limit
    /// @param[in] plimit Process limit to be set
    /// @return StdReturnType::OK on success
    StdReturnType SetProcessLimit(const utils::ProcessLimit& plimit) override;

    /// @brief Setting the current startup configuration
    /// @param[in] configurations Configuration to be set as current startup configuration
    /// @return StdReturnType::OK on success
    StdReturnType SetCurrentStartupConfiguration(cfgldr::IConfigLoaderDriver::ShortName configurations);

    /// @brief Setting the current function group state for the aplication
    /// @param[in]   fgstate       ID of the Function Group State
    /// @return StdReturnType
    StdReturnType SetCurrentState(FuncGroupStateId state);

    /// @brief Get the current function group state id where the instance was
    /// @return The function group state id
    FuncGroupStateId GetStateId();

    /// @brief Adding a startup configuration to the configuration list
    /// @param[in]   configuration       Configuration to be added
    /// @return StdReturnType
    StdReturnType AddStartupConfiguration(cfgldr::IConfigLoaderDriver::PStartupConfiguration& configuration);

    /// @brief Retrieve the current startup configuration name that the application is using from the state name
    /// @param[in]    fgState               Name of the Function Group State
    /// @param[out]   configurationName     Configuration name
    /// @return StdReturnType
    StdReturnType GetStartupConfigurationNameFromState(cfgldr::IConfigLoaderDriver::ShortName state, cfgldr::IConfigLoaderDriver::ShortName& configurationName);

    /// @brief Retrieve the number of restart attempts
    /// @return uint32_t
    uint32_t GetNumberOfRestartAttempts();

    /// @brief Sets the number of restart attempts
    /// @param[in]    value     The amount of restart attempts
    void SetNumberOfRestartAttempts(uint32_t value);

    /// @brief Check the if the state of instance
    /// @return  true : if instance state is INSTALLED
    //           false: if instance state having other then INSTALLED
    bool isInstalled() override;

    /// @brief Sets a execution error
    /// @param[in] executionError Process limit to be set
    /// @return StdReturnType::OK on success
    StdReturnType SetProcessExecutionError(const uint32_t& executionError) override;

    utils::ApplicationInfo appInfo; ///< App info of this ApplicationInstance.
    utils::AppRole approle;         ///< Role of this ApplicationInstance.
    ldr::StateMachine state_machine; ///< State Machine of the instance

private:
    id_t dbid;                                     ///< Contains the id of this instance, which is actually its index in the
                                                   ///< mfe::Database array
    char instance_name[INSTANCE_NAME_SIZE + 1U];    ///< Instance Name
    Dependency dependency_array[DEPENDENCY_MAX];   ///< Array of dependencies of an instance
    Dependency::Type resolver_types[RESOLVER_MAX]; ///< Type of the resolver
    id_t resolvers[RESOLVER_MAX];                  ///< Array of resolvers
    uint32_t dependencies_cnt;                     ///< Number of dependencies actually set for an instance
    uint32_t resolver_cnt;                         ///< Number of resolvers
    FuncGroupId registeredFuncGroup;               ///< The Function Group which handles this Instance.
    FuncGroupStateId
        registeredStates[MAX_FG_STATES_PER_APPLICATION]; ///< The FG States at which this instance
                                                         ///< is registered.
    uint32_t registeredStatesCount;                      ///< Number of FG States actually set for an instance.

    FuncGroupStateId currentState; ///< Current function group state id
    cfgldr::IConfigLoaderDriver::ShortName currentStartupConfigurationName; ///< Current startup configuration
    cfgldr::IConfigLoaderDriver::PStartupConfigurations startupConfigurations; ///< Array with all the startup configurations for this application

    ///   @brief Add a resolver to an executable instance
    ///   @param  ins_id Id of the executable instance that resolves this executable instance.
    ///   @param  type Dependency Type
    ///   @return  0 = success <BR>
    ///           -1 = failed
    int8_t add_resolver(id_t ins_id, Dependency::Type type);


    static constexpr uint32_t NAME_SIZE = 512U;

    bool IsFgStateRegistered(const FuncGroupStateId stateId, int32_t* index=nullptr);

    StdReturnType addEnVar(const char* key, const char* value);
    StdReturnType stdSetCredentials(const char* p_user_name, const char* p_group_name);
    static StdReturnType translateUserName(const utils::String<NAME_SIZE>& user_name, uid_t& uid);
    static StdReturnType translateGroupName(const utils::String<NAME_SIZE>& group_name, gid_t& gid);
    static StdReturnType stdGetGroupList(const utils::String<NAME_SIZE>& user_name, const gid_t& gid, gid_t* groupList, Integer& ngroups);
};
} // namespace ldr
} // namespace exm
#endif
