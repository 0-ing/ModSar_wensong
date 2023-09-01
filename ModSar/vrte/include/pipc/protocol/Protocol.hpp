#ifndef PIPC_PROTOCOL_PROTOCOL_HPP
#define PIPC_PROTOCOL_PROTOCOL_HPP

#include "Layer.hpp"
#include "PtmpEndpoint.hpp"
#include "PtpEndpoint.hpp"
#include "TIEndpoint.hpp"
#include "TIMessage.hpp"
#include "pipc/ReturnCode.hpp"

#include <stddef.h>
#include <stdint.h>
#include <utility>

namespace pipc
{
namespace protocol
{
/**
 * @brief Create a new message for the given PtpEndpoint and layer.
 */
template<typename TPayload, size_t NLayer, typename T0, typename T1, typename T2, typename T3>
inline Message<TPayload, NLayer, T0, T1, T2, T3> CreateMessage(PtpEndpoint<T0, T1, T2, T3>&)
{
    using TMsg = typename PtpEndpoint<T0, T1, T2, T3>::template Message<TPayload, NLayer>;
    return TMsg{};
}

/**
 * @brief Forward a received message and optional arguments to the next upper layer.
 *
 * API for PtpEndpoints, which can be called by the layers.
 */
template<size_t NLayer, typename TMsg, typename T0, typename T1, typename T2, typename T3, typename... TArgs>
inline typename std::enable_if<(NLayer < kApp), ReturnCode>::type Forward(PtpEndpoint<T0, T1, T2, T3>& endpoint,
                                                                                  TMsg& msg,
                                                                                  TArgs&&... args)
{
    constexpr size_t nLayer = NLayer + 1;
    auto& nextLayer         = endpoint.template getLayer<nLayer>();
    using PayloadRx         = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
    using TNewMsg           = Message<PayloadRx, nLayer, T0, T1, T2, T3>;
    auto& pdu               = static_cast<TNewMsg&>(msg);
    return nextLayer.template receive<nLayer>(endpoint, pdu, std::forward<TArgs&&>(args)...);
}

/**
 * @brief Forward a received message and optional arguments to the next upper layer.
 *
 * API for PtmpEndpoints, which can be called by the layers.
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
inline typename std::enable_if<(NLayer < kApp), ReturnCode>::type Forward(
    PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
    TMsg& msg,
    TArgs&&... args)
{
    constexpr size_t nLayer = NLayer + 1;
    auto& nextLayer         = endpoint.template getLayer<nLayer>();
    using PayloadRx         = typename std::decay<decltype(nextLayer)>::type::PayloadRx;
    using TNewMsg           = Message<PayloadRx, nLayer, T4, T5, T6, T7>;
    auto& pdu               = static_cast<TNewMsg&>(msg);
    return nextLayer.template receive<nLayer>(endpoint, pdu, std::forward<TArgs>(args)...);
}

/** @brief Sink for no additional layers to receive from. */
template<size_t NLayer, typename TEndpoint, typename TMsg, typename... TArgs>
inline typename std::enable_if<(NLayer == kApp), ReturnCode>::type Forward(TEndpoint&, TMsg&, TArgs&&...)
{
    return ReturnCode::kOk;
}

/**
 * @brief Forward a state change notification and optional arguments to the next upper layer.
 *
 * API for PtpEndpoints, which can be called by the layers.
 */
template<size_t NLayer, typename T0, typename T1, typename T2, typename T3, typename... TArgs>
inline typename std::enable_if<(NLayer < kApp), void>::type ForwardNotification(
    PtpEndpoint<T0, T1, T2, T3>& endpoint,
    LayerStateChange state,
    TArgs&&... args)
{
    constexpr size_t nLayer = NLayer + 1;
    auto& nextLayer         = endpoint.template getLayer<nLayer>();
    nextLayer.template processNotification<nLayer>(endpoint, state, std::forward<TArgs>(args)...);
}

/**
 * @brief Forward a state change notification and optional arguments to the next upper layer.
 *
 * API for PtmpEndpoints, which can be called by the layers.
 */
template<size_t NLayer,
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
inline typename std::enable_if<(NLayer < kApp), void>::type ForwardNotification(
    PtmpEndpoint<NEndpoints, T0, T1, T2, T3, T4, T5, T6, T7>& endpoint,
    LayerStateChange state,
    TArgs&&... args)
{
    constexpr size_t nLayer = NLayer + 1;
    auto& nextLayer         = endpoint.template getLayer<nLayer>();
    nextLayer.template processNotification<nLayer>(endpoint, state, std::forward<TArgs>(args)...);
}

/** @brief Sink for no additional layers to forward notifications to. */
template<size_t NLayer, typename TEndpoint, typename... TArgs>
inline typename std::enable_if<(NLayer == kApp), void>::type ForwardNotification(TEndpoint&,
                                                                                         LayerStateChange,
                                                                                         TArgs&&...)
{
}

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_PROTOCOL_HPP
