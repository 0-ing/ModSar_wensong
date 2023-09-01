#ifndef IE2ECHECKER_HPP
#define IE2ECHECKER_HPP

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
/// @file      IE2EChecker.hpp
/// @brief     Interface for E2E checker
/// @copyright Robert Bosch GmbH  2020
//=============================================================================

#include "ara/com/e2e/result.h"
#include "e2e/e2e_types.hpp"

#include <cstdint>

namespace com
{
namespace e2e
{
/**
 * \brief E2E-Checker interface
 */
class IE2EChecker
{
public:
    using e2eResult = ara::com::e2e::Result;

    virtual ~IE2EChecker()
    {
    }

    /**
     * @brief Returns the size of the e2e-protection header for the actual checker behind the interface.
     *
     * The return value of this function represents the N bytes from the front of the buffer that need to be skipped (
     * this also depends on the offset).
     *
     * @return Size in bytes of the e2e-protection header
     */
    virtual std::size_t getE2EHeaderLength() = 0;

    /**
     * @brief Check the e2e-protection header
     *
     * Checks the e2e-protection header stored in the beginning of the buffer against the payload.
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this HHHHPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6).For SomeIp-transfers , the SomeIp data will be added in front of the buffer. If there
     * is SomeIp data to be added, setOffset(8) will be used. In this case the buffer should look like this:
     * SSSSSSSSHHHHPPPPPP where: S - someip data (8 bytes), H - e2e header data (in this example 4 bytes), P - payload
     * to be protected (in this example 6 bytes). The additionalHeader and additionalHeaderLength are unused.
     *
     * @param buffer Input buffer for the checker
     * @param length Length of the input buffer
     * @param additionalHeader Not used
     * @param additionalHeaderLength Not used
     * @return Check result of the sample
     */
    virtual e2eResult check(const uint8_t* buffer,
                            std::size_t length,
                            const uint8_t* additionalHeader,
                            std::size_t additionalHeaderLength)
        = 0;

    /**
     * @brief Check the e2e-protection header(for the client side in case of method communication)
     *
     * Checks the e2e-protection header stored in the beginning of the buffer against the payload.
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this HHHHPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6).For SomeIp-transfers , the SomeIp data will be added in front of the buffer. If there
     * is SomeIp data to be added, setOffset(8) will be used. In this case the buffer should look like this:
     * SSSSSSSSHHHHPPPPPP where: S - someip data (8 bytes), H - e2e header data (in this example 4 bytes), P - payload
     * to be protected (in this example 6 bytes).
     *
     * @param[in] messageType Message type
     * @param[in] messageResult Message result
     * @param[in] counter E2E counter
     * @param[in] buffer Input buffer for the checker
     * @param[in] length Length of the input buffer
     * @return Check result of the sample
     */
    virtual e2eResult check(MessageType messageType,
                            MessageResult messageResult,
                            uint32_t counter,
                            const uint8_t* buffer,
                            std::size_t length)
        = 0;

    /**
     * @brief Check the e2e-protection header(for the server side in case of method communication)
     *
     * Checks the e2e-protection header stored in the beginning of the buffer against the payload.
     * The length of the buffer is the return value from getE2EHeaderLength + the length of the payload.
     * Before calling the function the buffer should look like this HHHHPPPPPP (return value from getE2EHeaderLength is
     * 4 and payload length is 6).For SomeIp-transfers , the SomeIp data will be added in front of the buffer. If there
     * is SomeIp data to be added, setOffset(8) will be used. In this case the buffer should look like this:
     * SSSSSSSSHHHHPPPPPP where: S - someip data (8 bytes), H - e2e header data (in this example 4 bytes), P - payload
     * to be protected (in this example 6 bytes).
     *
     * @param[in] messageType Message type
     * @param[in] messageResult Message result
     * @param[out] dataId Configured data ID.Used for error handling.
     * @param[out] sourceId Source ID contained in the e2e-protection header.Used for e2e protect function.
     * @param[out] counter E2E counter contained in the e2e-protection header.Used for e2e protect function.
     * @param[in] buffer Input buffer for the checker
     * @param[in] length Length of the input buffer
     * @return Check result of the sample
     */
    virtual e2eResult check(MessageType messageType,
                            MessageResult messageResult,
                            uint32_t& dataId,
                            uint32_t& sourceId,
                            uint32_t& counter,
                            const uint8_t* buffer,
                            std::size_t length)
        = 0;

    /**
     * @brief setOffset Sets the offset where the e2e header should be found. For example:
     * - If setOffset(0) the buffer should look like HHHHPPPPPP
     * - If setOffset(4) the buffer should look like PPPPHHHHPPPP
     * @param offset index from the start of the buffer where the e2e header should be found
     */
    virtual void setOffset(uint32_t offset) = 0;
};

} // namespace e2e
} // namespace com

#endif
