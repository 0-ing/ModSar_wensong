//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      ExecInstanceAttr.hpp
/// @brief     class to hold instance attributes
/// @copyright Robert Bosch GmbH  2018
/// @author

#ifndef UTILS_EXECINSTANCEATTR_HPP_INCLUDED
#define UTILS_EXECINSTANCEATTR_HPP_INCLUDED

#include "utils/Credentials.hpp"
#include "utils/NumCores.hpp"
#include "utils/PrimaryConfig.hpp"
#include "utils/ProcessLimits.hpp"
#include "utils/ResourceGroupId.hpp"
#include "utils/SchedulingParameters.hpp"
#include "utils/StdReturnType.hpp"
#include "utils/String.hpp"
#include "utils/Try.hpp"

namespace exm
{
namespace utils
{

/// @class    ExecInstanceAttr
/// @brief    Class to hold instance attributes
class ExecInstanceAttr
{

public:
    /// @brief destructor
    virtual ~ExecInstanceAttr() {} // Not covered: Only the deleting destructor is not covered. We don't use the heap.

    /// @brief constructor
    ExecInstanceAttr(void)
        : cpumask(NumCores().ToMask()), schedulingParam(), credentials(), qnx_secpol_type_name(), registeredResourceGroup(ResourceGroupId::MACHINE_RESOURCEGROUP_ID), plimits() {}

    /// @brief Copy constructor
    ExecInstanceAttr(const ExecInstanceAttr& execInsattr):cpumask(), schedulingParam(), credentials(), qnx_secpol_type_name(), registeredResourceGroup(), plimits()
    {
        *this = execInsattr;
    }

    /// @brief Copy assignment operator
    ExecInstanceAttr& operator=(const ExecInstanceAttr& other)
    {
        if (this != &other)
        {
            this->cpumask = other.cpumask;
            this->schedulingParam = other.schedulingParam;
            this->credentials = other.credentials;
            this->qnx_secpol_type_name = other.qnx_secpol_type_name;
            this->registeredResourceGroup = other.registeredResourceGroup;
            this->plimits = other.plimits;
        }

        return *this;
    }

    /// @brief set the cpu affinity
    /// @param mask : the cpu mask
    /// @return StdReturnType
    /// @attention this feature is only supported for QNX
    StdReturnType set_cpumask(uint32_t const mask)
    {
        TRY(NumCores().ValidateMask(mask));
        cpumask = mask;
        return StdReturnType::OK;
    }

    /// @brief get the cpu affinity settings
    /// @return cpu affinity settings
    uint32_t get_cpumask() const { return cpumask; }

    /// @brief set the scheduling policy and priority
    /// @param policy the scheduling policy
    /// @param priority the scheduling priority
    /// @return OK : policy and priority are set
    ///         INVALID_ARGUMENTS : arguments invalid
    StdReturnType set_sched(Integer const policy, Integer const priority)
    {
        return schedulingParam.Set_SchedulingParameters(policy, priority);
    }

    /// @brief Sets the default scheduling policy and priority.
    /// This will overtake the calling thread policy and priority.
    StdReturnType set_sched_default()
    {
        return schedulingParam.SetDefault();
    }

    /// @brief Passes the scheduling policy and priority
    /// @param[in] schedulingParam_ Reference to the SchedulingParameters object
    void get_SchedulingParameters(SchedulingParameters& schedulingParam_) const
    {
        schedulingParam_ = schedulingParam;
    }

    /// @brief Get the UID
    /// @return UID
    uid_t get_uid() const { return credentials.getUid(); }

    /// @brief Get the GID
    /// @return GID
    gid_t get_gid() const { return credentials.getGid(); }

    /// @brief Get the number of supplementary groups
    /// @return Number of supplementary groups
    uint32_t get_ngroups() const { return credentials.getNgroups(); }

    /// @brief Get the list of supplementary groups
    /// @return List of supplementary groups
    Credentials::Groups& get_glist()
    {
        return credentials.getGlist();
    }

    /// @brief Set the UID and GID
    /// @param uid_ UID
    /// @param gid_ GID
    void set_credentials(const uid_t uid_, const gid_t gid_) { credentials.setCredentials(uid_, gid_); }

    /// @brief Set the UID, GID, number of supplementary groups and the list supplementary groups
    /// @param uid_ UID
    /// @param gid_ GID
    /// @param ngroups_ number of supplementary groups
    /// @param[in] glist_ list of supplementary groups
    /// @return StdReturnType::OK if the credentials were set successfully, else StdReturnType::GENERAL_ERROR
    StdReturnType set_credentials(const uid_t uid_, const gid_t gid_, Integer ngroups_, const gid_t* const glist_)
    {
        return credentials.setCredentials(uid_, gid_, ngroups_, glist_);
    }

    StdReturnType push_supplementary_group(const gid_t suppl_grp_id)
    {
        return credentials.push_suppl_group(suppl_grp_id);
    }
    /// @brief get the QNX type name for the security policy
    /// @return The QNX type name for the security policy
    utils::String<MAXSIZE_SECPOL_TYPE_NAME> const& get_qnx_secpol_type_name() const
    {
        return qnx_secpol_type_name;
    }

    /// @brief set the QNX type name for the security policy
    /// @param secpol_type_name_ The QNX type name for the security policy
    /// @return StdReturnType::OK on success
    StdReturnType set_qnx_secpol_type(const char* secpol_type_name_) { return qnx_secpol_type_name.TrySetNonEmptyStr(secpol_type_name_); }

    /// @brief Setting Resource Group to resGrpId
    /// @param[in] resGrpId    The Resource Group ID for the Instance.
    /// @return StdReturnType::OK on success, INVALID_ARGUMENTS on failure
    StdReturnType SetResourceGroup(ResourceGroupId resGrpId)
    {
        if (ResourceGroupId::INVALID == resGrpId)
        {
            return StdReturnType::INVALID_ARGUMENTS;
        }

        registeredResourceGroup = resGrpId;
        return StdReturnType::OK;
    }

    /// @brief Getting resGrpId
    /// @return resGrpId    The Resource Group ID for the Instance.
    ResourceGroupId GetResourceGroupId() { return registeredResourceGroup; }

    /// @brief Sets a process limit
    /// @param[in] plimit Process limit
    /// @return StdReturnType::OK on success
    StdReturnType SetProcessLimit(const ProcessLimit& plimit) { return plimits.PushLimit(plimit); }

    /// @brief Gets the process limits
    /// @return Const reference to process limits
    const utils::ProcessLimits& GetProcessLimits() { return plimits; }

private:
    /// @brief cpu mask
    uint32_t cpumask;

    /// @brief Scheduling parameters
    SchedulingParameters schedulingParam;

    /// @brief Credentials
    Credentials credentials;

    /// @brief qnx type name. If null, then no type is configured.
    String<MAXSIZE_SECPOL_TYPE_NAME> qnx_secpol_type_name;

    ResourceGroupId registeredResourceGroup; ///< The Resource GroupId.

    ProcessLimits plimits; ///< The process limits
};                         // class ExecInstanceAttr

} // namespace utils
} // namespace exm

#endif
