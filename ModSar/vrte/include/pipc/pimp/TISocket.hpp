/// @copyright : 2022 Robert Bosch GmbH. All rights reserved

#ifndef PIPC_PIMP_TISOCKET_HPP
#define PIPC_PIMP_TISOCKET_HPP

#include "pipc/e2e/Trusted.hpp"
#include "pipc/queue/internal/ReturnVal.hpp"

#include <utility>

namespace pipc
{
namespace pimp
{
/**
 * @brief Template interface for a socket.
 *
 * @todo
 * Clean up the notify handling. It probably shouldn't be a separate
 * send function, instead another template parameter TNotifier.
 */
template<typename TSocket>
class TISocket
{
public:
    static_assert(!std::is_polymorphic<TSocket>::value,
                  "Only non-polymorphic classes can be accessed through interfaces.");

    /** @brief This is an interface, an object by itself must never exist. */
    TISocket()                         = delete;
    TISocket(const TISocket<TSocket>&) = delete;
    TISocket(TISocket<TSocket>&&)      = delete;

    /** @brief Allow implicit conversions back to the real type. */
    constexpr operator TSocket&()
    {
        return *reinterpret_cast<TSocket*>(this);
    }

    /** @brief Check which type of payload protection is configured for the socket. */
    static constexpr e2e::E2EProtection GetPayloadProtection()
    {
        return TSocket::GetPayloadProtection();
    }

    /** @brief Send a message over the socket. */
    template<typename T>
    inline ReturnVal send(const T& val)
    {
        return reinterpret_cast<TSocket*>(this)->template send<T>(val);
    }

    /** @brief Send function with in-place construction into the queue. */
    template<typename T, typename... Args>
    inline ReturnVal send_emplace(Args&&... args)
    {
        return reinterpret_cast<TSocket*>(this)->template send_emplace<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Send a message over without notification.
     *
     * @remark For benchmarks only.
     */
    template<typename T>
    inline ReturnVal send_no_notify(const T& val)
    {
        return reinterpret_cast<TSocket*>(this)->template send_no_notify<T>(val);
    }

    /**
     * @brief Send_emplace without notifiaction.
     *
     * @remark For benchmarks only.
     */
    template<typename T, typename... Args>
    inline ReturnVal send_emplace_no_notify(Args&&... args)
    {
        return reinterpret_cast<TSocket*>(this)->template send_emplace_no_notify<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Method to try to receive from a socket (non-blocking).
     */
    template<typename T>
    inline ReturnVal try_receive(T& val)
    {
        return reinterpret_cast<TSocket*>(this)->template try_receive<T>(val);
    }

    /** @brief Try to peek into the receive queue. */
    template<typename T>
    inline ReturnVal try_peek(T*& val)
    {
        return reinterpret_cast<TSocket*>(this)->template try_peek<T>(val);
    }

    /** @brief Pop from the receive queue without looking at the data again. */
    inline ReturnVal try_pop()
    {
        return reinterpret_cast<TSocket*>(this)->try_pop();
    }

    /**
     * @brief Wait for a receive notification.
     */
    inline void wait()
    {
        return reinterpret_cast<TSocket*>(this)->wait();
    }

    /**
     * @brief Notify the own rx channel.
     *
     * The self-notification can be used to stop a listener sitting on the socket.
     */
    inline void notify_self()
    {
        return reinterpret_cast<TSocket*>(this)->notify_self();
    }
};

} // namespace pimp
} // namespace pipc

#endif // PIPC_PIMP_TISOCKET_HPP
