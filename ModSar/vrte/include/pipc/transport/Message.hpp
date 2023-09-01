/// @copyright : 2022 Robert Bosch GmbH. All rights reserved.

#ifndef PIPC_TRANSPORT_MESSAGE_HPP
#define PIPC_TRANSPORT_MESSAGE_HPP

#include "PtpLayer.hpp"
#include "pipc/pimp/PtpLayer.hpp"
#include "pipc/protocol/Layer.hpp"
#include "pipc/protocol/Message.hpp"
#include "pipc/utils/Tuple.hpp"

namespace pipc
{
namespace transport
{
/** @brief Definition of a Message on the transport layer. */
template<typename T>
using Message = protocol::Message<T, protocol::kTransport, pimp::PtpLayer, transport::PtpLayer>;

/** @brief Definition of a Datagram, containing only a dst port and a payload. */
template<typename T>
class Datagram
{
public:
    /** @brief Default constructor. */
    constexpr Datagram() : data_()
    {
    }

    /** @brief Get the header of the datagram (transport layer). */
    transport::PtpLayer::DataHeader& header() const
    {
        return data_.template get<protocol::kTransport>();
    }

    /** @brief Get the payload of the datagram. */
    T& payload() const
    {
        return data_.template get<protocol::kTransport + 1>();
    }

    /** @brief Equal operator (used mainly for testing). */
    inline bool operator==(const Datagram& other) const
    {
        return data_ == other.data_;
    }

private:
    alignas(8) utils::Tuple<pimp::PtpLayer::Header, transport::PtpLayer::DataHeader, T> data_;
};

} // namespace transport
} // namespace pipc

#endif // PIPC_TRANSPORT_MESSAGE_HPP
