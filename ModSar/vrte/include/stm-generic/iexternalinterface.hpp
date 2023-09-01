//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/eh/include/bosch/vrte/stm/eh/iexternalinterface.hpp
/// @brief     BaseClass to create stm external interfaces objects
/// @copyright Robert Bosch GmbH 2018-2022
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_EH_IEXTERNALINTERFACE_HPP_INCLUDED
#define BOSCH_VRTE_STM_EH_IEXTERNALINTERFACE_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace eh
{

/// @brief This class is implemented by clients to enable themselves to
///        register with Event handler and receive events.
class CIExternalInterface
{
public:
    /// @brief Destructor
    virtual ~CIExternalInterface() = default;

    /// @brief Push event from EH to internal event handling thread.
    /// @param[in] f_event   Numerical event ID
    /// @param[in] f_data    Event payload
    virtual void acceptEventFromEh(const uint64_t f_event, const std::string& f_data = std::string()) = 0;
};

}  // namespace eh
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_EH_IEXTERNALINTERFACE_HPP_INCLUDED
