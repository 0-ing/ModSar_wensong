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
/// @file InstanceSpecCfg.hpp
/// @brief
/// @copyright Robert Bosch GmbH 2021
//=============================================================================
#ifndef COM_SERVICE_DEPLOYMENT_INSTANCE_SPEC_CFG_HPP
#define COM_SERVICE_DEPLOYMENT_INSTANCE_SPEC_CFG_HPP

#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/map.h"
#include "ara/core/result.h"
#include "ara/core/set.h"

namespace com
{
namespace config
{
/// @brief This class stores the information and offers a way to resolve ara::com::InstanceIdentifier's for a
/// given ara::meta::InstanceSpecifier.
class InstanceSpecCfg
{
public:
    /// @brief Getter for singleton instance of InstanceSpecCfg.
    static InstanceSpecCfg& get();

    /// @brief Maps a InstanceIdentifier to a InstanceSpecifier. This function should be called by the configuration
    /// component. If a InstanceSpecifier mapping already exists, it will map the InstanceIdentifier to the existing
    /// InstanceSpecifier
    /// @param f_specifier InstanceSpecifier to map
    /// @param f_identifier InstanceIdentifier to map
    void addSpecifierEntry(const ara::core::InstanceSpecifier& f_specifier,
                           const ara::com::InstanceIdentifier& f_identifier);

    /// @brief Check if the specifier is known and return all matching identifiers.
    /// @param f_specifier The key to search matching identifiers with.
    /// @return A container of ara::com::InstanceIdentifier's that are mapped to the given specifier.
    ara::core::Result<ara::com::InstanceIdentifierContainer> ResolveInstanceIDs(
        const ara::core::InstanceSpecifier& f_specifier) const;

private:
    /// @brief Construct an empty (no mapping configuration) instance specifier cfg object
    InstanceSpecCfg()
    {
    }

    ara::core::Map<ara::core::InstanceSpecifier, ara::core::Set<ara::com::InstanceIdentifier>>
        m_instanceMap; ///< The actual map containing the specifier <-> identifier mapping.
};
} // namespace config
} // namespace com

#endif // COM_SERVICE_DEPLOYMENT_INSTANCE_SPEC_CFG_HPP
