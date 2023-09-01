//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         ThreadAttrParserUtility.hpp
/// @brief        Provides interfaces to gather the user configured thread attributes
/// @author

#ifndef _THREADATTRPARSERUTILITY_HPP_INCLUDED
#define _THREADATTRPARSERUTILITY_HPP_INCLUDED

#include "IThreadAttrParserUtility.hpp"
#include "utils/String.hpp"
#include "utils/PrimaryConfig.hpp"

namespace bosch
{
namespace vrte
{
namespace exm
{

/// @brief Class which provides interfaces to gather the user configured thread attributes
class ThreadAttrParserUtility : public IThreadAttrParserUtility
{
public:
    /// @brief Constructor
    ThreadAttrParserUtility(): IThreadAttrParserUtility(), jsonString(), json_char_count(0U)
    {}

    /// @brief Destructor
    virtual ~ThreadAttrParserUtility() noexcept
    {}

    /// @brief prevent copy construction
    /// @private
    ThreadAttrParserUtility(const ThreadAttrParserUtility& other) = delete;

    /// @brief prevent copy assignment
    /// @private
    ThreadAttrParserUtility& operator=(const ThreadAttrParserUtility& other) = delete;

    virtual bool CreateAndEnterSubnodeArrayToObject(const char* name) noexcept override;

    virtual bool CreateAndEnterSubnodeArrayToArray() noexcept override;

    virtual bool CreateAndEnterSubnodeObjectToObject(const char* name) noexcept override;

    virtual bool CreateAndEnterSubnodeObjectToArray() noexcept override;

    virtual bool AddStringToArray(const char* value) noexcept override;

    virtual bool AddBoolToArray(const bool value) noexcept override;

    virtual bool AddDoubleToArray(const double value) noexcept override;  // PRQA S 2427 # This is an abstract interface defined outside ExM. Furthermore, this interface function will not be used by ExM.

    virtual bool AddInt32ToArray(const int32_t value) noexcept override;

    virtual bool AddNullToArray() noexcept override;

    virtual bool AddStringToObject(const char* name, const char* value) noexcept override;

    virtual bool AddBoolToObject(const char* name, const bool value) noexcept override;

    virtual bool AddDoubleToObject(const char* name, const double value) noexcept override; // PRQA S 2427 # This is an abstract interface defined outside ExM. Furthermore, this interface function will not be used by ExM.

    virtual bool AddInt32ToObject(const char* name, const int32_t value) noexcept override;

    virtual bool AddNullToObject(const char* name) noexcept override;

    virtual bool CloseArrayAndLeaveSubnode() noexcept override;

    virtual bool CloseObjectAndLeaveSubnode() noexcept override;

    virtual bool getc_implementation(char& c) noexcept override;

    virtual ::exm::StdReturnType setInputString(const char* inputString) override;

private:
    ::exm::utils::String<::exm::utils::ARG_ENV_SIZE> jsonString;     // String to store json input
    uint32_t json_char_count;
};
}
}
}

#endif // _THREADATTRPARSERUTILITY_HPP_INCLUDED
