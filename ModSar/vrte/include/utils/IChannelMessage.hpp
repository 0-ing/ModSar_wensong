//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file       IChannelMessage.hpp
/// @brief      Interface used by Channel to handle messages
/// @copyright  Robert Bosch GmbH  2018
/// @author     baetz
#ifndef EXM_ICHANNELMESSAGE_HPP_INCLUDED
#define EXM_ICHANNELMESSAGE_HPP_INCLUDED

#include "StdReturnType.hpp"

namespace exm {

/// @brief Interface used by Channel to handle messages.
/// Abstract definition of functionality necessary to send a message over
/// Channel.
class IChannelMessage {
public:

    /// Virtual Dtor for interfaces.

    virtual ~IChannelMessage() {
    } // Not covered: Deleting destructors of pure virtual base classes can not be called.


    /// @brief Get a pointer to the message header.
    /// Intended for receiving the header from the channel.
    /// @return  Pointer to a buffer capable of holding the entire header.
    virtual uint8_t* GetHeaderBuffer() = 0;


    /// @brief Get the expected header size.
    /// Intended for receiving the header from the channel.
    /// @return  The overall encoded header size.
    virtual uint32_t GetHeaderSize() const = 0;


    /// @brief Parsing and checking the message header.
    /// When this method is called, implementations shall parse the header content
    /// and eventually perform a check of the header content.
    /// @warning Especially the payload size shall be checked, as this could 
    /// lead to a buffer overflow.
    /// @return OK if successful, some error code otherwise.
    virtual StdReturnType ParseHeader() = 0;


    /// @brief Get a pointer to the message payload.
    /// Intended for receiving payload data from the channel.
    /// @return  Pointer to a buffer capable of holding the entire payload data.
    virtual uint8_t* GetPayloadBuffer() = 0;


    /// @brief Get the expected payload size.
    /// Return the exepected size of the payload.
    /// Must be exact, not a maximum value.
    /// Intended for receiving payload data from the channel.
    /// @return  Actual payload size.
    virtual uint32_t GetPayloadSize() const = 0;


    /// @brief Parse payload content from the buffer.
    /// When this method is called, implementations shall parse the payload content
    /// and eventually perform basic formal checks.
    /// @return OK if successful, some error code otherwise.
    virtual StdReturnType ParsePayload() = 0;



    /// @brief Getter for a pointer to the message.
    /// Intended for sending the message over a channel.
    /// The pointer must point to the complete, uninterrupted message.
    /// @return Pointer to message buffer.
    virtual const uint8_t* GetMessage() const = 0;


    /// @brief Getter for the overall message size.
    /// Intended for sending the message over a channel.
    /// @return Total size of the message (header + payload)
    virtual uint32_t GetMessageSize() const = 0;


    /// @brief Prepare message for sending.
    /// When called, implementations shall prepare the entire message for
    /// sending over a channel.
    /// This covers both serialization of the header and of message content.
    /// @return OK if successful, some error code otherwise.
    virtual StdReturnType PrepareMessage() = 0;

};

}  // namespace exm

#endif // EXM_ICHANNELMESSAGE_HPP_INCLUDED
