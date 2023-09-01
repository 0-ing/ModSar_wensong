//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2017 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
/// @file      LoaderConfig.hpp
/// @brief     Manifest Loader configuration

#ifndef _LOADERCONFIG_HPP_INCLUDED
#define _LOADERCONFIG_HPP_INCLUDED

#include <stdint.h>
#include "utils/PrimaryConfig.hpp"

namespace exm
{
namespace ldr
{
    /// @brief Maximum number of arguments for an instance
    static constexpr uint8_t    ENV_STR_MAX = utils::MAX_EFFECTIVE_ENV_VARIABLES;

    static constexpr uint32_t   SUPPLEMENTARY_GROUPS_MAX = utils::MAX_SUPPLEMENTARY_GROUPS;               ///< @brief Maximum number of supplementary groups for an instance
    static constexpr uint32_t   INSTANCE_NAME_SIZE = utils::INSTANCE_NAME_SIZE;                           ///< @brief Size of instance name
    static constexpr uint32_t   ARG_ENV_SIZE = utils::ARG_ENV_SIZE;                                       ///< @brief Argument size for an instance
    static constexpr uint8_t    ARG_STR_MAX = utils::MAX_ARGUMENTS;                                       ///< @brief Maximum number of arguments for an instance
    static constexpr uint8_t    DEPENDENCY_MAX = utils::MAX_PROCESS_DEPENDENCY;                           ///< @brief Maximum number of dependencies allowed for an instance
    static constexpr uint8_t    RESOLVER_MAX = utils::MAX_PROCESS_RESOLVER;                               ///< @brief Maximum number of resolvers allowed for an instance
    static constexpr int32_t    SCHED_DEFAULT_PRIO = 10;                                                  ///< @brief Default scheduling priority  in the system
    static constexpr uint32_t   MAX_FG_STATES_PER_APPLICATION= utils::MAX_FUNC_GROUP_STATE_PER_PROCESS;   ///< @brief Number of configurable Function Group States per application instance.
    static constexpr uint32_t   DEFAULT_PROCESS_ENTER_TIMEOUT_MS = 10000U;                                ///< @brief Default enter timeout, which is used if no value is set in config.
    static constexpr uint32_t   DEFAULT_PROCESS_EXIT_TIMEOUT_MS = 10000U;                                 ///< @brief Default exit timeout, which is used if no value is set in config.
}
}
#endif
