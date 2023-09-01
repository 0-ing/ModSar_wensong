/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef COM_SD_SERVICE_HPP
#define COM_SD_SERVICE_HPP

#include "com/Types.hpp"

namespace com
{
namespace sd
{
/**
 * @brief Definition of a ServiceId used in the deployment.
 *
 * This data type is used for transmission of ServiceIds.
 *
 * @todo
 * Where to put this eventually?
 */
using ServiceId = uint64_t;

/**
 * @brief Definition of an InstanceId used in the deployment.
 *
 * This data type is used for transmission of InstanceIds.
 *
 * @todo
 * Where to put this eventually?
 */
using InstanceId = uint32_t;

/** @brief Special value for requesting all available Instance Ids. */
static constexpr InstanceId ALL_INSTANCE_IDS = 0xFFFFFFFFUL;

/** @brief Special value for requesting no available Instance Ids. */
static constexpr InstanceId NO_INSTANCE_IDS = 0xFFFFFFFFUL;

/** @brief A container of InstanceIds (not InstanceIdentifier).
 *
 * This container usees the data type used for transmission of InstanceIds.
 */
using InstanceIdContainer = ara::core::Vector<InstanceId>;

} // namespace sd
} // namespace com

#endif // COM_SD_SERVICE_HPP
