//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file         IThreadAttrParserUtility.hpp
/// @brief        Abstract interface for thread atribute parser utility.
/// @author


#ifndef _ITHREADATTRPARSERUTILITY_HPP_INCLUDED
#define _ITHREADATTRPARSERUTILITY_HPP_INCLUDED

#include "utils/StdReturnType.hpp"
#include "utils/String.hpp"
#include "utils/memory.hpp"

#include "json/json_storer_interface.h"
#include "json/json_input_interface.h"

namespace bosch
{
namespace vrte
{
namespace exm
{

typedef ::exm::utils::String<10U> SchedulingPolicyName;

typedef ::exm::utils::String<100U> ThreadNamePrefix;

typedef uint32_t RunMask;

/// @brief Abstract interface for thread atribute parser utility
class IThreadAttrParserUtility : public json::JsonStorerInterface, public json::JsonInputInterface
{
public:
    /// @brief Destructor
    virtual ~IThreadAttrParserUtility() noexcept
    {}

    /// @brief Constructor
    IThreadAttrParserUtility() noexcept
    {}

    /// @brief prevent copy construction
    /// @private
    IThreadAttrParserUtility(const IThreadAttrParserUtility &other) = delete;

    /// @brief prevent copy assignment
    /// @private
    IThreadAttrParserUtility& operator=(const IThreadAttrParserUtility& other) = delete;

    /// @brief Function to set the input string, which has to be parsed
    /// @param[in] string Input string
    /// @return StdReturnType::OK success, otherwise an error occurred.
    virtual ::exm::StdReturnType setInputString(const char* string) = 0;

    ::exm::utils::placed_ptr<ThreadNamePrefix> threadNamePrefix;                     // Thread name
    ::exm::utils::placed_ptr<RunMask> threadRunmask;                     // Thread cpu affinity
    ::exm::utils::placed_ptr<int32_t> threadSchedPrio;                   // Thread scheduling priority
    ::exm::utils::placed_ptr<SchedulingPolicyName> threadSchedPol;       // Thread scheduling policy
    ::exm::utils::placed_ptr<uint32_t> threadStackSize;                  // Thread scheduling priority
};
}
}
}

#endif // _ITHREADATTRPARSERUTILITY_HPP_INCLUDED
