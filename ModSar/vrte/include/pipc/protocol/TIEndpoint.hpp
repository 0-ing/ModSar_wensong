#ifndef PIPC_PROTOCOL_TIENDPOINT_HPP
#define PIPC_PROTOCOL_TIENDPOINT_HPP

#include "EndpointId.hpp"

#include <utility>

namespace pipc
{
namespace protocol
{
/**
 * @brief Template Interface for a generic endpoint.
 *
 * This Template Interface provides a way for layers to access
 * the API of the endpoints they are used with.
 *
 * @remark
 * TIEndpoint contains a superset of API functions, not all might be available.
 */
template<typename TEndpoint>
class TIEndpoint
{
public:
    static_assert(!std::is_polymorphic<TEndpoint>::value,
                  "Only non-polymorphic classes can be accessed through template interfaces.");

    /** @brief This is an interface, an object by itself must never exist. */
    TIEndpoint()                  = delete;
    TIEndpoint(const TIEndpoint&) = delete;
    TIEndpoint(TIEndpoint&&)      = delete;

    /** @brief Allow implicit conversions back to the real type. */
    constexpr operator TEndpoint&()
    {
        return *reinterpret_cast<TEndpoint*>(this);
    }

    /** @brief Send a message through the endpoint. */
    template<typename T>
    inline void send(T&& msg)
    {
        return self().send(std::forward<T>(msg));
    }

    /** @brief Send a datagram message through the endpoint. */
    template<typename T>
    inline void sendDatagram(T&& msg)
    {
        return self().sendDatagram(std::forward<T>(msg));
    }

    /**
     * @brief Get a PtpEndpoint by index.
     *
     * @todo
     * This made it fail, no more TIEndpoint...
     */
    template<typename TPtpEndpoint = typename TEndpoint::PtpEndpoint>
    inline TIEndpoint<TPtpEndpoint>* get(EndpointId idx)
    {
        return reinterpret_cast<TIEndpoint<TPtpEndpoint>*>(self().get(idx));
    }

private:
    inline TEndpoint& self()
    {
        return *this;
    }
};

} // namespace protocol
} // namespace pipc

#endif // PIPC_PROTOCOL_TIENDPOINT_HPP
