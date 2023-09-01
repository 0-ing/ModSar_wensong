#ifndef COM_SOMEIP_HEADER_GEN_HPP
#define COM_SOMEIP_HEADER_GEN_HPP

#include "config/IServiceIntfCfg.hpp"

namespace com
{
namespace binding
{
/**
 * @brief Class used on the application side to add SOME/IP headers to events
 */
class SomeipHeaderGen
{
public:
    using EventCfgSomeIp = com::config::EventCfgSomeIp;

    /**
     * @brief Destructor
     */
    ~SomeipHeaderGen()
    {
    }

    static const uint32_t HEADER_SIZE      = 8;      ///< Size of the SOME/IP header
    static const uint16_t CLIENT_ID        = 0x0000; ///< SOME/IP Client ID
    static const uint8_t PROTOCOL_VERSION  = 1;      ///< SOME/IP Protocol version
    static const uint8_t INTERFACE_VERSION = 1;      ///< SOME/IP Interface version
    static const uint8_t MESSAGE_TYPE
        = 2; ///< SOME/IP Message type. This value is equivalent with ara::com::someip::e_message_type::NOTIFICATION
    static const uint8_t RETURN_CODE
        = 0; ///< SOME/IP Return code. This value is equivalent with ara::com::someip::e_return_code::E_OK

    static const uint8_t CLIENT_ID_INDEX_H  = 0; ///< Position of the high byte Client ID in the buffer
    static const uint8_t CLIENT_ID_INDEX_L  = 1; ///< Position of the low byte Client ID in the buffer
    static const uint8_t SESSION_ID_INDEX_H = 2; ///< Position of the high byte Session ID in the buffer
    static const uint8_t SESSION_ID_INDEX_L = 3; ///< Position of the low byte Session ID in the buffer
    static const uint8_t PROTOCOL_INDEX     = 4; ///< Position of the Protocol version in the buffer
    static const uint8_t INTERFACE_INDEX    = 5; ///< Position of the Interface version in the buffer
    static const uint8_t MESSAGE_TYPE_INDEX = 6; ///< Position of the Message type in the buffer
    static const uint8_t RETURN_CODE_INDEX  = 7; ///< Position of the Return code in the buffer

    /**
     * @brief Function that adds the SOME/IP header to a buffer. The header will be placed at the begging of the buffer,
     * and the buffer must be at least @ref HEADER_SIZE. The SOME/IP header is composed of:
     *  - Request ID(Client ID/Session ID) [4 bytes]
     *  - Protocol Version [1 byte]
     *  - Interface Version [1 byte]
     *  - Message Type [1 byte]
     *  - Return Code [1 byte]
     *
     * @param f_buffer Buffer where to place the someip header.
     * @param f_bufferSize Total size of the @ref f_buffer. The buffer must be at least @ref HEADER_SIZE
     * @param f_eventCfg Configuration of the Some/IP event. The configuration is used to calculate if the event is of
     * type SOME/IP-TP
     * @return true if the someip header was added to the buffer, otherwise false
     */
    static bool addHeader(uint8_t* f_buffer, uint32_t f_bufferSize, const EventCfgSomeIp& f_eventCfg);

    /**
     * @brief Function that checks the SOME/IP header from a buffer. The header is be placed at the begging of the
     * buffer, and the buffer must be at least @ref HEADER_SIZE. The SOME/IP header is composed of:
     *  - Request ID(Client ID/Session ID) [4 bytes]
     *  - Protocol Version [1 byte]
     *  - Interface Version [1 byte]
     *  - Message Type [1 byte]
     *  - Return Code [1 byte]
     *
     * @param f_buffer Buffer where to place the someip header.
     * @param f_bufferSize Total size of the @ref f_buffer. The buffer must be at least @ref HEADER_SIZE
     * @param f_eventCfg Configuration of the Some/IP event. The configuration is used to calculate if the event is of
     * type SOME/IP-TP
     * @return true if the someip header is as expected, otherwise false
     */
    static bool checkHeader(const uint8_t* f_buffer, uint32_t f_bufferSize, const EventCfgSomeIp& f_eventCfg);

private:
    static const uint32_t TP_HEADER_SIZE = 12; ///< Size of header for SOME/IP-TP
};

} // namespace binding
} // namespace com

#endif // COM_SOMEIP_HEADER_GEN_HPP
