/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef SESSION_PROVIDER_ID_HPP
#define SESSION_PROVIDER_ID_HPP

#include "pipc/utils/FixedString.hpp"

namespace pipc
{
namespace session
{
/**
 * @brief Provider Identifier
 *
 * The ProviderId struct represents a unique identifier for a service component,
 * which can be referred to for Service Discovery.
 * It is composed of 4 distinct Ids (Service Id, Instance Id, Component Id, Type Id).
 *
 * @remark
 * The ProviderId is designed to nicely map to ARA services:
 *   PIPC Service Id   -> ARA Service Interface Id
 *   PIPC Instance Id  -> ARA Service Instance Id
 *   PIPC Component Id -> ARA Event/Method Id
 *   PIPC TypeId Id    -> ARA Deployment Type (e.g. IPC or Some/Ip)
 * This way an ARA service instance can be mapped to a list of PIPC ProviderIds
 * by taking into account only the Service Id and Instance Id portions of them.
 */
struct ProviderId
{
    /** @brief Default constructor. */
    inline ProviderId() = default;

    /**
     * @brief Constructor with all members of the ProviderId
     */
    constexpr ProviderId(uint64_t serviceId, uint32_t instanceId, uint16_t componentId, uint8_t typeId)
        : serviceId(serviceId), instanceId(instanceId), componentId(componentId), typeId(typeId)
    {
    }

    /**
     * @brief Constructor with serviceId, instanceId & componentId.
     *
     * This constructor is used for backwards compatibility to the initial
     * format of the ProviderId.
     */
    constexpr ProviderId(uint16_t serviceId, uint16_t instanceId, uint16_t componentId)
        : serviceId(serviceId), instanceId(instanceId), componentId(componentId), typeId(0U)
    {
    }

    /**
     * @brief Constructor with a baseProviderId and a componentId.
     */
    constexpr ProviderId(const ProviderId& baseProviderId, uint16_t componentId)
        : serviceId(baseProviderId.serviceId),
          instanceId(baseProviderId.instanceId),
          componentId(componentId),
          typeId(baseProviderId.typeId)
    {
    }

    /** @brief Equal operator. */
    inline bool operator==(const ProviderId& other) const
    {
        bool same = (serviceId == other.serviceId) && (instanceId == other.instanceId)
                    && (componentId == other.componentId) && (typeId == other.typeId);
        return same;
    }

    /** @brief Not Equal operator */
    inline bool operator!=(const ProviderId& other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Convert the ProviderId to a numeric string.
     *
     * @remark
     * Resulting string example '01234567_deadc0de_beef_ee\0'.
     */
    utils::FixedString<64U> toString() const
    {
        char providerId[64U];
        sprintf(providerId, "%016lx_%08x_%04x_%02x", serviceId, instanceId, componentId, typeId);
        return providerId;
    }

    /**
     * @brief Convert the ProviderId to a numeric string with two suffixes.
     *
     * @remark
     * Resulting string example '01234567_deadc0de_beef_ee_0123_4567\0'.
     */
    utils::FixedString<64U> toString(uint16_t suffix0, uint16_t suffix1) const
    {
        char providerId[64U];
        sprintf(providerId,
                "%016lx_%08x_%04x_%02x_%04x_%04x",
                serviceId,
                instanceId,
                componentId,
                typeId,
                suffix0,
                suffix1);
        return providerId;
    }

    /** @brief The Id defining the service. */
    uint64_t serviceId;
    /** @brief The Id defining the instance. */
    uint32_t instanceId;
    /** @brief The Id defining the component. */
    uint16_t componentId;
    /** @brief The Id defining the type of the service. */
    uint8_t typeId;
};

} // namespace session
} // namespace pipc

#endif // SESSION_PROVIDER_ID_HPP
