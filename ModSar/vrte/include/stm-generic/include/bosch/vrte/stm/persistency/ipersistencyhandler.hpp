//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2018-2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      libs/common/include/bosch/vrte/stm/persistency/ipersistencyhandler.hpp
/// @brief     Interface for Persistency Handler
/// @copyright Robert Bosch GmbH 2018-2021
/// @author    VRTE StM Team
//
//=============================================================================

#ifndef BOSCH_VRTE_STM_PERSISTENCY_IPERSISTENCYHANDLER_HPP_INCLUDED
#define BOSCH_VRTE_STM_PERSISTENCY_IPERSISTENCYHANDLER_HPP_INCLUDED

#include <string>

namespace bosch
{
namespace vrte
{
namespace stm
{
namespace persistency
{

class CIPersistencyHandler
{
public:
    virtual ~CIPersistencyHandler() = default;

    /// @brief: This function shall implement the initialization routine for establishing the connection with underlying
    /// persitency manager
    virtual void initialize() = 0;

    /// @brief: This function shall implement the logic to write a value to the file for a given key
    /// @param[in]: f_key   : Key
    /// @param[in]: f_value : Value
    /// @returns: Result of operation (success/failure)
    virtual bool writeToFile(const std::string& f_key, const std::string& f_value) = 0;

    /// @brief: This function shall implement the logic to retrieve data from the file identified by a key
    /// @param[in]:  f_key   : Key
    /// @param[out]: f_value : Value
    /// @returns: Result of operation (success/failure)
    virtual bool readFromFile(const std::string& f_key, std::string& f_value) const = 0;

    /// @brief: This function shall implement the logic to reset a key
    /// @param[in]: f_key : Key
    /// @returns: Result of operation (success/failure)
    virtual bool resetValue(const std::string& f_key) = 0;

    /// @brief: This function shall implement the logic to sync the data from RAM to physical storage
    virtual void flush() = 0;
};
}  // namespace persistency
}  // namespace stm
}  // namespace vrte
}  // namespace bosch

#endif  // BOSCH_VRTE_STM_PERSISTENCY_IPERSISTENCYHANDLER_HPP_INCLUDED
