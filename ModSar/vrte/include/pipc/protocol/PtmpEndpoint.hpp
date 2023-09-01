#ifndef PIPC_PROTOCOL_PTMP_ENDPOINT_HPP
#define PIPC_PROTOCOL_PTMP_ENDPOINT_HPP

#include "EndpointId.hpp"
#include "PtpEndpoint.hpp"
#include "TIEndpoint.hpp"

#include <array>
#include <atomic>
#include <cstddef>

namespace pipc
{
namespace protocol
{
/**
 * @brief A "Point-to-Multi-Point" endpoint with (de-)multiplexing capabilities.
 *
 * The PtmpEndpoint is used only for incoming messages and cannot send by itself.
 * It additionally contains up to NEndpoints separate PtpEndpoints, which can be used
 * for sending back messages.
 * One of the PtmpLayers takes responsibility of demultiplexing the incoming message to one of the PtpEndpoints and
 * forwarding the message together with the resolved endpoint idx into endpoints.
 * The PtpEndpoints' layers can contain endpoint-specific state information for each layer, while the PtmpLayers
 * typically take care of control flow and can include optional state information related to all PtpEndpoints.
 *
 * @remark
 * Typical use-case examples for a server endpoint:
 *
 * - Each client uses a unique socket to communicate with the server.
 *   This requires demultiplexing on the Network Layer.
 * - Each client uses a dedicated port to identify itself at the server.
 *   This requires demultiplexing on the Transport Layer.
 * - The server establishes a session for each connected client;
 *   sockets & ports can be used multiple times, but the tuple socket|port must be unique.
 *   This requires demultiplexing on the Session Layer.
 *
 * The last use-case is the one we typically use for PIPC components.
 */
template<size_t NEndpoints,
         typename TNetworkLayer,
         typename TTransportLayer,
         typename TSessionLayer,
         typename TAppLayer,
         typename TNetworkPtmpLayer,
         typename TTransportPtmpLayer,
         typename TSessionPtmpLayer,
         typename TAppPtmpLayer>
class PtmpEndpoint : public EndpointBase<TNetworkPtmpLayer, TTransportPtmpLayer, TSessionPtmpLayer, TAppPtmpLayer>
{
    friend class Layer;
    using BaseClass = EndpointBase<TNetworkPtmpLayer, TTransportPtmpLayer, TSessionPtmpLayer, TAppPtmpLayer>;

public:
    using PtpEndpoint = protocol::PtpEndpoint<TNetworkLayer, TTransportLayer, TSessionLayer, TAppLayer>;

    /** @brief We adhere to the TIEndpoint interface. */
    inline operator TIEndpoint<PtmpEndpoint>&()
    {
        return *reinterpret_cast<TIEndpoint<PtmpEndpoint>*>(this);
    }

    /**
     * @brief Get the endpoint identified by the given index.
     *
     * If idx refers to an invalid entry, a nullptr is returned.
     */
    PtpEndpoint* get(EndpointId idx)
    {
        PtpEndpoint* endpoint = nullptr;
        if (idx < NEndpoints)
        {
            auto& entry = endpointEntries_[idx];
            if (entry.valid)
            {
                endpoint = &entry.endpoint;
            }
        }
        return endpoint;
    }

    /**
     * @brief Get all endpoints including their valid flags.
     *
     * Can be used for a caller to iterate through the endpoints.
     * It is the responsibility of the caller to check whether
     * the endpoints are actually valid.
     *
     * @todo
     * This API exposes too much, we should implement Iterators like
     * with linked lists. Those could automatically skip invalid entries.
     */
    auto& getEndpointEntries()
    {
        return endpointEntries_;
    }

    /**
     * @brief Get the number of currently valid endpoints.
     *
     * @remark
     * Used mainly for testing.
     */
    size_t getValidEndpoints()
    {
        size_t validEndpoints = 0;
        for (auto& entry : this->getEndpointEntries())
        {
            if (entry.valid)
            {
                validEndpoints++;
            }
        }
        return validEndpoints;
    }
    /**
     * @brief Return the index of a given endpoint.
     *
     * @remark
     * If endpoint does not relate to an entry of the called instance, the
     * behavior is undefined.
     */
    EndpointId idx(const PtpEndpoint& endpoint)
    {
        size_t diff    = reinterpret_cast<size_t>(&endpoint) - reinterpret_cast<size_t>(&endpointEntries_);
        EndpointId idx = static_cast<EndpointId>(diff / sizeof(EndpointEntry));
        return idx;
    }

    /**
     * @brief Allocate a new endpoint.
     *
     * Returns a pointer to the new endpoint and the idx, if allocation succeeds.
     * If it fails due to no more slots being available, returns a nullptr.
     *
     * @todo
     * Returns the default-constructed endpoint from the array, would be cool to construct it upon allocation.
     */
    PtpEndpoint* allocate(EndpointId& idx)
    {
        idx = 0;
        for (idx = 0; idx < NEndpoints; idx++)
        {
            auto& entry = endpointEntries_[idx];
            auto valid  = entry.valid.load(std::memory_order_relaxed);
            if (!valid)
            {
                // To support concurrent allocation we need to use compare_exchange
                if (entry.valid.compare_exchange_strong(valid, true))
                {
                    return &entry.endpoint;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief Deallocate an endpoint.
     *
     * @todo
     * Who triggers invalidations? Probably responsibility of the caller, since
     * this class does not know which layers are affected.
     */
    void deallocate(EndpointId idx)
    {
        endpointEntries_[idx].valid.store(false, std::memory_order_release);
    }

    /**
     * @brief Find function to check for an endpoint's existence.
     *
     * The function provides an API to check whether some endpoint is already
     * present in the list of endpoint entries. The endpoint is compared for
     * equality up to NLayer.
     *
     * If a match is found, index is set to the position of the match and a pointer to the endpoint is returned.
     * If no match is found, a nullptr is returned.
     *
     * @remark
     * If multiple matches are possible, only the first match will be returned.
     */
    template<size_t NLayer>
    inline PtpEndpoint* find(PtpEndpoint& endpoint, EndpointId& idx) noexcept
    {
        PtpEndpoint* ep;
        for (idx = 0; idx < NEndpoints; idx++)
        {
            ep = get(idx);
            if ((ep) && (endpoint.template isSame<NLayer>(*ep)))
            {
                return ep;
            }
        }
        return nullptr;
    }

    /**
     * @brief Receive a message and optional arguments through the endpoint.
     *
     * @todo
     * Proper support of const for msg.
     */
    template<typename TMsg, typename... TArgs>
    inline ReturnCode receive(TMsg& msg, TArgs&&... args)
    {
        // std::cout << "PtmpEndpoint: Receiving message..." << std::endl;
        auto& nextLayer = this->template getLayer<kNetwork>();
        using PayloadRx = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
        using TNewMsg   = typename BaseClass::template Message<PayloadRx, kNetwork>;
        auto& pdu       = *reinterpret_cast<TNewMsg*>(&msg);
        return nextLayer.template receive<kNetwork>(*this, pdu, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Receive a message and optional arguments through the endpoint.
     *
     * @todo
     * Needed for testing, check if we can always use rvalue refs.
     */
    template<typename TMsg, typename... TArgs>
    inline ReturnCode receive(TMsg&& msg, TArgs&&... args)
    {
        // std::cout << "PtmpEndpoint: Receiving message..." << std::endl;
        auto& nextLayer = this->template getLayer<kNetwork>();
        using PayloadRx = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
        using TNewMsg   = typename BaseClass::template Message<PayloadRx, kNetwork>;
        auto& pdu       = *reinterpret_cast<TNewMsg*>(&msg);
        return nextLayer.template receive<kNetwork>(*this, pdu, std::forward<TArgs>(args)...);
    }

private:
    /**
     * @brief A single endpoint entry.
     *
     */
    struct EndpointEntry
    {
        /** @brief The actual endpoint data. */
        PtpEndpoint endpoint;
        /**
         * @brief Flag whether the entry is valid (= allocated)
         *
         * @remark
         * Is atomic to support lock-free reservations.
         *
         * @todo
         * Check if we need a 'reserved' intermediate state.
         */
        std::atomic<bool> valid{false};
    };

    /** @brief A list of all PtpEndpoints. */
    std::array<EndpointEntry, NEndpoints> endpointEntries_;
};

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_PTMP_ENDPOINT_HPP
