#ifndef IE2EPROTECTOR_HPP
#define IE2EPROTECTOR_HPP

//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      IE2EProtector.hpp
/// @brief     Interface for E2E protector
/// @copyright Robert Bosch GmbH  2020
//=============================================================================

#include "e2e/e2e_types.hpp"

#include <cstddef>
#include <cstdint>

namespace com
{
namespace e2e
{
/// @brief The ProtectStatus represents the results of the E2E protect
enum class ProtectStatus : uint8_t
{
    kOk,                         ///< E2E protection is configured ok.
    kNullBuffer             = 1, ///< Buffer is null.
    kIncorrectLength        = 2, ///< Buffer length is incorrect.
    kIncorrectMessageType   = 3, ///< Message type is incorrect.
    kIncorrectMessageResult = 4, ///< Message result is incorrect.
    kIncorrectSourceId      = 5, ///< Source ID is incorrect.
    kIncorrectCounter       = 6, ///< Counter is incorrect.
    kError                  = 7, ///< Error(unimplemented) .
    kProtectDisabled             ///< No E2E protect status available (no E2E protection is configured).
};

/**
 * \brief E2E-Protector interface
 */
class IE2EProtector
{
public:
    virtual ~IE2EProtector()
    {
    }

    /**
     * @brief Returns the size needed for the e2e-protection header for the actual protector behind the interface
     *
     * @return Size in bytes of the e2e-protection-header
     */
    virtual std::size_t getE2EHeaderLength() = 0;

    /**
     * @brief Computes the e2e-protection header and stores it in the beginning of the buffer
     *
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this XXXXPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6), the value of XXXX is undefined after calling the function. The buffer should look
     * like this HHHHPPPPPP where HHHH is the computed header and the payload remains unchanged. For SomeIp-transfers ,
     * the SomeIp data will be added in front of the buffer. If there is SomeIp data to be added, setOffset(8) will be
     * used.In this case, the buffer before calling the protect function should look like SSSSSSSSXXXXPPPPPP (where: S -
     * someip data (8 bytes) , the rest of the buffer is similar to the first example) and after the protect function ,
     * the buffer should look like this SSSSSSSSHHHHPPPPPP. The additionalHeader and additionalHeaderLength are unused.
     *
     * @param buffer Input buffer to be protected
     * @param length Length of the input buffer
     * @param additionalHeader Not used
     * @param additionalHeaderLength Not used
     * @return The result of the E2E protect
     */
    virtual ProtectStatus protect(uint8_t* buffer,
                                  std::size_t length,
                                  const uint8_t* additionalHeader,
                                  std::size_t additionalHeaderLength)
        = 0;

    /**
     * @brief Computes the e2e-protection header and stores it in the beginning of the buffer(for the client side in
     * case of method communication)
     *
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this XXXXPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6), the value of XXXX is undefined after calling the function. The buffer should look
     * like this HHHHPPPPPP where HHHH is the computed header and the payload remains unchanged. For SomeIp-transfers ,
     * the SomeIp data will be added in front of the buffer. If there is SomeIp data to be added, setOffset(8) will be
     * used.In this case, the buffer before calling the protect function should look like SSSSSSSSXXXXPPPPPP (where: S -
     * someip data (8 bytes) , the rest of the buffer is similar to the first example) and after the protect function ,
     * the buffer should look like this SSSSSSSSHHHHPPPPPP.
     *
     * @param[in] messageType Message type
     * @param[in] messageResult Message result
     * @param[out] counter E2E counter contained in the e2e-protection header.Used for e2e check function.
     * @param[inout] buffer Input buffer to be protected
     * @param[in] length Length of the input buffer
     * @return The result of the E2E protect
     */
    virtual ProtectStatus protect(MessageType messageType,
                                  MessageResult messageResult,
                                  uint32_t& counter,
                                  uint8_t* buffer,
                                  std::size_t length)
        = 0;

    /**
     * @brief Computes the e2e-protection header and stores it in the beginning of the buffer(for the server side in
     * case of method communication)
     *
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this XXXXPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6), the value of XXXX is undefined after calling the function. The buffer should look
     * like this HHHHPPPPPP where HHHH is the computed header and the payload remains unchanged. For SomeIp-transfers ,
     * the SomeIp data will be added in front of the buffer. If there is SomeIp data to be added, setOffset(8) will be
     * used.In this case, the buffer before calling the protect function should look like SSSSSSSSXXXXPPPPPP (where: S -
     * someip data (8 bytes) , the rest of the buffer is similar to the first example) and after the protect function ,
     * the buffer should look like this SSSSSSSSHHHHPPPPPP.
     *
     * @param[in] messageType Message type
     * @param[in] messageResult Message result
     * @param[in] sourceId Source ID
     * @param[in] counter E2E counter
     * @param[inout] buffer Input buffer to be protected
     * @param[in] length Length of the input buffer
     * @return The result of the E2E protect
     */
    virtual ProtectStatus protect(MessageType messageType,
                                  MessageResult messageResult,
                                  uint32_t sourceId,
                                  uint32_t counter,
                                  uint8_t* buffer,
                                  std::size_t length)
        = 0;

    /**
     * @brief setOffset Sets the offset where the e2e header should be placed. For example:
     * - If setOffset(0) the buffer would look like HHHHPPPPPP
     * - If setOffset(4) the buffer would look like PPPPHHHHPPPP
     * @param offset index from the start of the buffer where the e2e header would be placed
     */
    virtual void setOffset(uint32_t offset) = 0;
};

} // namespace e2e
} // namespace com

#endif
