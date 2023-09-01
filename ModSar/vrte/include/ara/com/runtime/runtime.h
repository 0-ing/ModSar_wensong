/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef ARA_COM_RUNTIME_RUNTIME_H
#define ARA_COM_RUNTIME_RUNTIME_H

#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"
#include "ara/core/vector.h"

namespace ara
{
namespace com
{
/** @brief Forward declaration of InstanceIdentifier. */
class InstanceIdentifier;

/** @brief Forward declaration of InstanceIdentifierContainer. */
using InstanceIdentifierContainer = ara::core::Vector<InstanceIdentifier>;

namespace runtime
{
/**
 * @brief Translate the InstanceSpecifier to a list of InstanceIds.
 *
 * @remark
 * {SWS_CM_00118}
 */
ara::core::Result<ara::com::InstanceIdentifierContainer> ResolveInstanceIDs(ara::core::InstanceSpecifier modelName);

} // namespace runtime
} // namespace com
} // namespace ara

#endif // ARA_COM_RUNTIME_RUNTIME_H
