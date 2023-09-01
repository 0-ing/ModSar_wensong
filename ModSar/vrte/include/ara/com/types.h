/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef ARA_COM_TYPES_H
#define ARA_COM_TYPES_H

//#include "ara/core/string_view.h"

#include "ara/com/SamplePtr.hpp"
#include "ara/com/runtime/runtime.h"
#include "ara/core/future.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/vector.h"
#include "pipc/loan/SamplePtr.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

#include <queue>

namespace ara
{
namespace com
{
/** @brief Forward declaration of InstanceIdentifier. */
class InstanceIdentifier;

/**
 * @brief This string identifies ANY, which is useful for FindService calls.
 *
 * It is used for both IPC and SOME/IP deployments.
 */
static constexpr char AnyStringID[] = "65535";

enum class SerializationTechnologyEnum
{
    SIGNAL_BASED = 0,
    SOME_IP
};

enum class TransportLayerProtocolEnum
{
    TCP = 0,
    UDP
};

enum class NetworkBindingEnum : uint8_t
{
    UNKNOWN = 0,
    IPC,
    SOME_IP
};

/**
 * @brief Specification of a deployment type.
 *
 * Deployment type is the definition from the configuration point of view,
 * while network binding is used in the COM spec.
 * Not sure which term is more universal...
 */
using DeploymentType = NetworkBindingEnum;

} // namespace com
} // namespace ara

namespace com
{
/**
 * @brief Set the deployment type of an InstanceIdentifier.
 *
 * Currently called internally by generated Proxy & Skeleton code, because only they know
 * if the instanceIdentifier is meant for Ipc or SomeIp deployment.
 *
 * @remark
 * Defined outside of ara::com as it shall not be a public interface (even though it is anyway, just in com::).
 */
void SetDeploymentType(ara::com::InstanceIdentifier& instanceIdentifier, ara::com::DeploymentType deploymentType);
} // namespace com

namespace ara
{
namespace com
{
/**
 * @brief Identifier of a certain instance of a service.
 *
 * This is needed to distinguish between different instances of exactly the same
 * service in the system.
 * Only contains instance information. Does NOT contain a fully qualified
 * name, which also contains service type information.
 *
 * @note The implementation might be changed by product vendor.
 * Only the Autosar Adaptive API must be preserved.
 *
 * @remark
 * @ID{[SWS_CM_00302]}
 *
 * @todo
 * As per specification of COM & TPS, eventually we will need ALL information about a Service Instance
 * included in here:
 *
 * - instanceId (some integer)
 * - deployment info (Ipc|SomeIp|Dds...)
 *
 * Currently the constructor string is not used in that way, values look like "42" or "myInstance".
 * As the instanceId does not include the deployment info yet, we need to insert this information from the
 * generated Proxy/Skeleton code. Only the generated code knows whether Ipc or Some/Ip deployments have been generated.
 */
class InstanceIdentifier
{
    /** @brief Allow access to this class' private members. */
    friend void ::com::SetDeploymentType(ara::com::InstanceIdentifier& instanceIdentifier,
                                         ara::com::DeploymentType deploymentType);

public:
    /**
     * @brief User-side constructor with input string.
     *
     * At the time of creation, the deployment type is unknown.
     * The middleware will add deployment information from the config if it is supposed to use such an identifier,
     * using the setDeploymentType method.
     * If this function is not called, id, idString and deployment type are not properly set.
     * However, comparison with both properly initialized and other user-constructed IDs is possible.
     * See the description of operator== .
     *
     * @todo: Proper handling of deployment types, IDs and configuration is required to get this straight.
     */
    InstanceIdentifier(ara::core::StringView serializedFormat)
        : idString_(serializedFormat.data(), serializedFormat.size()), id_(0U), deploymentType_(DeploymentType::UNKNOWN)
    {
    }

    /**
     * @brief Constructor with input string as string literal.
     *
     * This constructor is needed, if a string literal is given indirectly as constructor arg for InstanceIdentifier.
     *
     * @todo
     * Discuss this, should be supported by ara core string view or not?
     *
     * @tparam N
     */
    template<size_t N>
    InstanceIdentifier(const char (&serializedFormat)[N])
        : idString_(serializedFormat), id_(0U), deploymentType_(DeploymentType::UNKNOWN)
    {
    }

    /**
     * @brief Create class as per ar21-11 specification
     *
     * @param serializedFormat The input string as a serialized instance identifier format. See ctor for details.
     * @return ara::core::Result<InstanceIdentifier> The valid instanceId or ComErrc::kInvalidInstanceIdentifierString .
     */
    static ara::core::Result<InstanceIdentifier> Create(ara::core::StringView serializedFormat);

protected:
    /**
     * @brief Direct initialization with an integer and a deployment type.
     *
     * @remark
     * Internal constructor used by the middleware.
     */
    InstanceIdentifier(uint32_t id, DeploymentType deploymentType = DeploymentType::IPC)
        : idString_(), id_(id), deploymentType_(deploymentType)
    {
        if (deploymentType == DeploymentType::IPC)
        {
            idString_.append("[IPC]");
        }
        else if (deploymentType == DeploymentType::SOME_IP)
        {
            idString_.append("[SOMEIP]");
        }
        else
        {
            // Explicitly setting the deployment type to UNKNOWN makes no sense.
            // However, it stays compatible as long as idString_ represents the original ID as string.
        }
        idString_.append(std::to_string(id));
    }

public:
    /**
     * @brief Equal operator
     *
     * To allow users to compare self-created instance IDs with those coming from the middleware, this operator
     * implements some heuristics for comparison with unknown deployment types.
     * @param other The value to compare with
     * @return true In case this and other are the same, even if one DeploymentType is set to UNKNONW.
     * @return false If deployment type and ID don't match.
     */
    bool operator==(const InstanceIdentifier& other) const;

    /** @brief Unequal operator. */
    bool operator!=(const InstanceIdentifier& other) const;

    /** @brief Smaller operator. */
    bool operator<(const InstanceIdentifier& other) const;

    /** @brief Copy assignment. */
    InstanceIdentifier& operator=(const InstanceIdentifier& other) = default;

    /** @brief Copy constructor. */
    InstanceIdentifier(const InstanceIdentifier& other) = default;

    /** @brief Return the string representation of the instanceId. */
    ara::core::StringView ToString() const;

    /** \brief Static instance providing instance wildcard semantics. */
    static const InstanceIdentifier Any;

    operator std::string() const;

    /** @brief Get the configured deployment type. */
    DeploymentType getDeploymentType() const
    {
        return deploymentType_;
    }

    /**
     * @brief Get the underlying id_ value.
     *
     * @remark
     * Used internally by the middleware.
     */
    operator uint32_t() const
    {
        return id_;
    }

protected:
    /**
     * @brief The (legacy) string value.
     *
     * @remark
     * We have to keep this as long as users don't directly deliver the right serialized string view in all cases.
     */
    std::string idString_;

    /** @brief The instance id. */
    uint32_t id_;
    /** @brief The deployment type of the instance. */
    DeploymentType deploymentType_;
};

using InstanceIdentifierContainer = ara::core::Vector<InstanceIdentifier>;

/**
 * \brief Currently we take a simple string as Service identifier of
 * a given service.
 * Might be changed...
 */
using ServiceIdentifier = std::string;
/**
 * \brief Currently we take a simple string as Version identifier of
 * a given service.
 * Might be changed...
 */
using ServiceVersion = std::string;

/**
 * @brief Handle for a triggered FindService request.
 *
 * This handle is needed to later cancel the FindService request.
 *
 * @note This implementation might be changed by product vendor.
 */
union FindServiceHandle
{
    /** @brief Default constructor. */
    FindServiceHandle() : fullHandle()
    {
    }

    /** @brief Constructor with a binding and an id. */
    constexpr FindServiceHandle(NetworkBindingEnum binding, uint16_t id) : fields(binding, id)
    {
    }

    /** @brief Conversion to uint32. */
    operator uint32_t() const
    {
        return fullHandle;
    }

    /**
     * @brief Return the binding of the handle.
     *
     * @return NetworkBindingEnum
     */
    NetworkBindingEnum binding() const
    {
        return static_cast<NetworkBindingEnum>(fields.binding);
    }

    /**
     * @brief Return the id of the handle.
     *
     * @return uint16_t
     */
    uint16_t id() const
    {
        return fields.id;
    }

    /**
     * @brief Representation as separate fields per Id.
     *
     * @todo
     * How portable is this? What about endianness?
     */
    struct Fields
    {
        /** @brief Constructor with binding & id. */
        constexpr Fields(NetworkBindingEnum binding, uint16_t id) : binding(static_cast<uint32_t>(binding)), id(id)
        {
        }

        /** @brief The binding of the handle. */
        uint32_t binding : 8;
        /** @brief The id of the handle. */
        uint32_t id : 16;
    } fields;

    /** @brief Representation as a uint32_t. */
    uint32_t fullHandle;
};

/**
 * Container for a list of service handles.
 *
 * \see ara::com::FindService
 *
 * \note This implementation might be changed by product vendor.
 * At least the container implementation must be compliant to C++11
 * containers according to: http://en.cppreference.com/w/cpp/concept/Container
 *
 * * \remark
 * @ID{[SWS_CM_00383]}
 */
template<typename HandleType>
using ServiceHandleContainer = ara::core::Vector<HandleType>;

/**
 * \brief Function wrapper for handler, that gets called in case service availability
 * for services, which have been searched for via FindService() has changed.
 *
 * \remark
 * @ID{[SWS_CM_00383]}
 */
template<typename HandleType>
using FindServiceHandler = std::function<void(ServiceHandleContainer<HandleType>, FindServiceHandle)>;

//-------------------------Events---------------------------------------------

/**
 * \brief Definition of update policy for Events.
 *
 * \note Should be provided by platform vendor exactly like this.
 */
enum class EventCacheUpdatePolicy
{
    /**
     * With this policy new available events are
     * put in the cache by each call of Update. If they do not fit in the cache,
     * older entries (oldest first) are displaced. With this policy the
     * following applies: If the cache has been filled with a certain amount of
     * events, the amount can only remain constant (if no new event has arrived)
     * or get bigger with upcoming Update calls (if new events have been
     * arrived).
     */
    kLastN,
    /**
     * With this policy in each update the
     * cache gets cleared and then filled with the newest arrived events. Even
     * if NO event has arrived since the last call to Update, the cache gets
     * cleared/emptied.
     */
    kNewestN
};

/**
 * \brief Receive handler method, which is semantically a void(void) function.
 *
 * \note This implementation might be changed by product vendor.
 *
 * \remark
 * @ID{[SWS_CM_00309]}
 */
using EventReceiveHandler = std::function<void(void)>;

/**
 * \brief Function representing a Filter Function provided by the programmer.
 *
 * \return true if to accept/keep the sample in the Update() call.
 */
template<typename SampleType>
using FilterFunction = std::function<bool(const SampleType&)>;

/**
 * \brief Definition of the subscription state of an Event.
 *
 * \remark
 * @ID{[SWS_CM_00310]}
 */
enum class SubscriptionState : uint8_t
{
    kSubscribed,
    kNotSubscribed,
    kSubscriptionPending
};

/**
 * @brief Definition of SubscriptionStateChangeHandler.
 *
 * @remark
 * @ID{[SWS_CM_00311]}
 */
using SubscriptionStateChangeHandler = std::function<void(SubscriptionState)>;

// TODO: Not part of the public interface, remove later
template<typename T>
using UniquePtr = std::unique_ptr<T>;

using EventIdentifier = std::string;

//-------------Samples--------------------------------------------------

/**
 * \brief Sample allocatee pointer definition.
 *
 * \remark
 * @ID{[SWS_CM_00308]}
 */
template<typename SampleType>
using SampleAllocateePtr = pipc::loan::SamplePtr<SampleType>;

/**
 * Pointer to a sample
 *
 * \note This implementation might be changed by product vendor.
 */
template<typename SampleType>
using SamplePtr = ara::com::internal::SamplePtr<const SampleType>;

/**
 * \brief Container for a list of sample-pointers received via event communication.
 *
 *
 * \note This implementation might be changed by product vendor.
 * At least the container implementation must be compliant to C++11
 * containers according to: http://en.cppreference.com/w/cpp/concept/Container
 *
 */
template<typename SamplePtrType>
using SampleContainer = std::deque<SamplePtrType>;

/**
 * Converter function from an ARA sample to a custom transport
 * \note the template arguments are in the order of first the inputs and then outputs, similar to
 * EventGatewayTransportSender/-Receiver
 */
template<typename SampleMetaData, typename SampleType, typename TransportType>
using SampleToTransportConverter = std::function<void(const SampleMetaData&, const SampleType&, TransportType&)>;

/**
 * Converter function from a custom transport to an ARA sample
 * \note the template arguments are in the order of first the inputs and then outputs, similar to
 * EventGatewayTransportSender/-Receiver
 */
template<typename TransportType, typename SampleMetaData, typename SampleType>
using TransportToSampleConverter = std::function<void(const TransportType&, SampleMetaData&, SampleType&)>;

//-------------Methods--------------------------------------------------

/**
 * \brief Request processing modes for the service implementation side
 * (skeleton).
 *
 * \remark
 * @ID{[SWS_CM_00301]}
 */
enum class MethodCallProcessingMode : uint8_t
{
    kPoll,
    kEvent,
    kEventSingleThread
};

} // namespace com
} // namespace ara

#endif // COM_COM_TYPES_HPP
