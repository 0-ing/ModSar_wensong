//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      ResourceGroup.hpp
/// @brief     Declaration/Definition of ResourceGroup
/// @author    Jyothi Kuntegowda
//=============================================================================
#ifndef RESOURCEGROUP_HPP
#define RESOURCEGROUP_HPP

#include "utils/ResourceGroupId.hpp"
#include "utils/String.hpp"

namespace exm
{

namespace utils
{

/// @brief Container for Resource Group.
///
/// Stores ResourceGroupDefinitions
class ResourceGroup
{
public:
    /// @brief Constructor
    ResourceGroup();

    /// @brief Destructor
    virtual ~ResourceGroup() {};

    /// @brief copy constructor
    ResourceGroup(const ResourceGroup& other);

    /// @brief copy assignment operator
    ResourceGroup& operator=(const ResourceGroup& other);

    /// @brief Sets the Resource Group Name
    ///
    /// @param[in] GroupName = Resource Group name
    /// @return OK on success, GENERAL_ERROR on failures
    StdReturnType SetResourceGroupName(const char* const GroupName);

    /// @brief Sets the Resource Group budget details
    ///
    /// @param[in] mininum_guarantee = minimum guaranteed cpu time requested
    /// @param[in] maximum_budget The new name. Must be a NULL terminated string.
    void SetResourceBudget(uint8_t min_guarantee_param, uint8_t max_budget_param);

    /// @brief Check if the name of this group is equal to groupName.
    ///
    /// @param[in] groupName The name to compare with. Must be a NULL-terminated string!
    /// @return true if groupName equals the name of this ResourceGroup, false else.
    bool HasName(const char* const groupName) const;

    /// @brief Function to get min_guranteed budget of resource group
    /// @return  minimum guaranteed budget
    uint8_t getMinguarantee() const
    {
        return min_guarantee;
    }

    /// @brief Function to get max_budget of resource group
    /// @return maximum budget
    uint8_t getMaxbudget() const
    {
        return max_budget;
    }

    /// @brief Function to get name of resource group
    /// @return resGrp name
    const utils::String<utils::RESOURCE_GROUP_NAME_SIZE>& getResGrpName() const
    {
        return resGrpName;
    }

    /// @brief Function to get ResourceGroupId of resource group
    /// @return ResourceGroupId
    ResourceGroupId getResourceGroupId() const
    {
        return resGrpId;
    }

    /// @brief Function to set ResourceGroupId of resource group
    /// @return void
    void SetResourceGroupId(ResourceGroupId rgroupid);

private:
    utils::String<utils::RESOURCE_GROUP_NAME_SIZE> resGrpName; ///< String name of the Resource Group
    ResourceGroupId resGrpId;                                  ///< ID of the Resource Group.
    uint8_t min_guarantee;                                     ///< Minimum guaranteed budget for the resource Group.
    uint8_t max_budget;                                        ///< Maximum budget allocated for resource Group.
};

} // namespace utils
} // namespace exm

#endif
