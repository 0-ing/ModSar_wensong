#ifndef PROTOCOL_TIMESSAGE_HPP
#define PROTOCOL_TIMESSAGE_HPP

#include <utility>

namespace pipc
{
namespace protocol
{
/**
 * @brief Template Interface for a protocol message.
 *
 * This Template Interface provides a way for layers to access
 * their respective header and payload information.
 */
template<typename TPayload, typename THeader, typename TMessage>
class TIMessage
{
public:
    static_assert(!std::is_polymorphic<TMessage>::value,
                  "Only non-polymorphic classes can be accessed through template interfaces.");

    /** @brief This is an interface, an object by itself must never exist. */
    TIMessage()                 = delete;
    TIMessage(const TIMessage&) = delete;
    TIMessage(TIMessage&&)      = delete;

    /** @brief Get the header of the message. */
    inline THeader& header()
    {
        return reinterpret_cast<TMessage*>(this)->header();
    }

    /** @brief Get the payload of the message. */
    inline TPayload& payload()
    {
        return reinterpret_cast<TMessage*>(this)->payload();
    }
};

/** @brief Type Trait to check if a given type is a TIMessage. */
template<typename>
struct IsTIMessage : std::false_type
{
};
template<typename TPayload, typename THeader, typename TMessage>
struct IsTIMessage<TIMessage<TPayload, THeader, TMessage>> : std::true_type
{
};

} // namespace protocol
} // namespace pipc

#endif // PROTOCOL_TIMESSAGE_HPP
