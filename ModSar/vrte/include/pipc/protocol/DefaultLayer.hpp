#ifndef PIPC_PROTOCOL_DEFAULTLAYER_HPP
#define PIPC_PROTOCOL_DEFAULTLAYER_HPP

#include "Layer.hpp"
#include "Message.hpp"
#include "Protocol.hpp"
#include "TIMessage.hpp"

namespace pipc
{
namespace protocol
{
/**
 * @brief A Layer definition with some default functionality.
 *
 * This default layer serves as a skeleton to provide an
 * interface and basic passthrough behavior.
 *
 * @todo
 * We still need to implement requestActivation and requestDeactivation.
 */
class DefaultLayer
{
protected:
    /** @brief Helper struct to print an error for functions, which shall not be called. */
    template<typename... T>
    struct dependent_false
    {
        static constexpr bool value = false;
    };

public:
    /** @brief State shortcut. */
    using State = LayerState;

    /** @brief StateChange shortcut. */
    using StateChange = LayerStateChange;

    /** @brief PtpEndpoint shortcut for derived classes. */
    template<typename... Types>
    using PtpEndpoint = protocol::PtpEndpoint<Types...>;

    /** @brief Message shortcut for derived classes. */
    template<typename TPayload, size_t NLayer, typename... Types>
    using Message = protocol::Message<TPayload, NLayer, Types...>;

    /** @brief The header information for messages of this layer. */
    using Header = Placeholder;

    /** @brief The payload for incoming messages of this layer. */
    using PayloadRx = Placeholder;

    /** @brief The payload for outgoing messages of this layer. */
    using PayloadTx = Placeholder;

    /** @brief Equal operator. */
    inline bool operator==(const DefaultLayer&) const
    {
        return true;
    }

    /**
     * @brief The interface to fill the header for outgoing messages.
     *
     * @remark
     * The default layer does not contribute any header information.
     */
    constexpr void prepare(Header&)
    {
    }

    /**
     * @brief The send function must be implemented by the very first layer.
     *
     * @remark
     * The default layer does not permit sending.
     *
     * @remark
     * Academically speaking, we would require a send function for every layer,
     * which puts the header in and passes onto the send function
     * of the next lower layer. This would result in filling the header
     * backwards, though.
     */
    template<typename T>
    constexpr ReturnCode send(const T&)
    {
        static_assert(dependent_false<T>::value, "Cannot send through the default layer.");
        return ReturnCode::kNetworkError;
    }

    /**
     * @brief Check whether the state of this layer is valid.
     *
     * @remark
     * The default layer returns the lower layer's valid function.
     */
    // template<size_t N, typename... TLayers>
    // constexpr bool valid(Endpoint<TLayers...>& endpoint)
    // {
    //     return endpoint.template getLayer<N - 1>().valid();
    // }

    /**
     * @brief Get the state of this layer.
     *
     * @remark
     * The default layer returns the lower layer's state.
     */
    template<size_t N, typename E>
    constexpr LayerState getState(E& endpoint)
    {
        return endpoint.template getLayer<N - 1>().getState();
    }

    /**
     * @brief Process a state change from a lower layer.
     *
     * @remark
     * The default layer passes the state change to the next layer.
     */
    template<size_t NLayer, typename E, typename... TArgs>
    constexpr void processNotification(E& endpoint, StateChange state, TArgs&&... args)
    {
        protocol::ForwardNotification<NLayer>(endpoint, state, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Receive a message and optional additional arguments.
     *
     * Variant for PtpEndpoints. Note that
     * TMsg is actually a protocol::Message configured for this header,
     * so header() and payload() can be directly called.
     *
     * @remark
     * The default layer simply passes the message to the next layer.
     *
     * A real layer can override this and should then do the following:
     * - Check if the message is really addressed at this layer
     * -> If no, validate and forward it
     * -> If yes, process it and forward state changes, if necessary
     */
    template<size_t NLayer, typename TMsg, typename T0, typename T1, typename T2, typename T3, typename... TArgs>
    constexpr ReturnCode receive(PtpEndpoint<T0, T1, T2, T3>& endpoint, TMsg& msg, TArgs&&... args)
    {
        return protocol::Forward<NLayer>(endpoint, msg, std::forward<TArgs>(args)...);
    }

    /**
     * @brief Receive a message and optional additional arguments.
     *
     * Variant for PtmpEndpoints.
     */
    template<size_t NLayer,
             typename TMsg,
             size_t NEndpoints,
             typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7,
             typename... TArgs>
    constexpr ReturnCode receive(PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
                                      TMsg& msg,
                                      TArgs&&... args)
    {
        return protocol::Forward<NLayer>(endpoint, msg, std::forward<TArgs>(args)...);
    }
};

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_DEFAULTLAYER_HPP
