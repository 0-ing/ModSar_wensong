#ifndef COM_TYPES_HPP
#define COM_TYPES_HPP

#include "ara/com/com_error_domain.h"
#include "ara/com/types.h"
#include "ara/core/promise.h"

/**
 * @brief Using directives & other central types.
 *
 * These using directives are meant to make our code in the com
 * namespace more readable:
 * We use lots of the ara::com types in our interfaces, with
 * the using directives we don't have to keep mentioning the
 * full namespaces.
 *
 * @remark
 * Although this is not meant to be done for user code,
 * with this mechanism we import the names only into our own
 * vendor-specific namespace.
 */

namespace com
{
using ComErrc = ara::com::ComErrc;

template<typename T>
using Result = ara::core::Result<T>;

/**
 * @brief Identifier for a triggered FindService request.
 *
 * This identifier is needed to later cancel the FindService request.
 */
using FindServiceId = uint16_t;

template<typename T>
using Promise = ara::core::Promise<T>;

template<typename T>
using Future = ara::core::Future<T>;

using FindServiceHandle = ara::com::FindServiceHandle;

using InstanceIdentifier = ara::com::InstanceIdentifier;

using InstanceIdentifierContainer = ara::com::InstanceIdentifierContainer;

using InstanceSpecifier = ara::core::InstanceSpecifier;

using NetworkBindingEnum = ara::com::NetworkBindingEnum;

using DeploymentType = ara::com::DeploymentType;

/**
 * @brief Definition of a Service Handle.
 *
 * A generic service handle definition, which we can use to create any Proxy
 * within our middleware.
 *
 * @remark
 * {SWS_CM_00312}
 *
 * @remark
 * We require a generic definition, as our SD Runtime has a map of FindServiceHandlers
 * with template type 'HandleType'.
 * ServiceHandle is basically the same as an InstanceIdentifier, but makes its
 * protected method public, so a deployment type can be set when constructing
 * a ServiceHandle/InstanceIdentifier from the Runtime.
 */
// using ServiceHandle = InstanceIdentifier;
class ServiceHandle : public InstanceIdentifier
{
public:
    /** @brief Constructor with an id and a deployment type. */
    ServiceHandle(uint32_t id, ara::com::DeploymentType deploymentType)
        : InstanceIdentifier(id, deploymentType)
    {
        static_assert(sizeof(ServiceHandle) == sizeof(InstanceIdentifier),
                      "Mem layout of ServiceHandle must match InstanceIdentifier.");
    }

    /**
     * @brief Get the underlying InstanceId.
     */
    const ara::com::InstanceIdentifier& GetInstanceId() const
    {
        return *this;
    }
};

/**
 * @brief Definition of a generic ServiceHandleContainer.
 */
using ServiceHandleContainer = ara::com::ServiceHandleContainer<ServiceHandle>;

/**
 * @brief Definition of a generic FindServiceHandler.
 */
using FindServiceHandler = ara::com::FindServiceHandler<ServiceHandle>;

template<typename T>
using UniquePtr = ara::com::UniquePtr<T>;

} // namespace com

#endif // COM_TYPES_HPP
