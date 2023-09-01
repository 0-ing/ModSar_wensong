//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright Robert Bosch GmbH 2018. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file      PrimaryConfig.hpp
/// @brief     Primary configuration of exm
/// @author    Arnaud Riess

#ifndef UTILS_PRIMARYCONFIG_HPP_INCLUDED
#define UTILS_PRIMARYCONFIG_HPP_INCLUDED

#include "utils/Types.hpp"
#include <stdint.h>

namespace exm
{
namespace utils
{
constexpr uint32_t MAX_STARTUPCONFIGURATIONS_PER_PROCESS = 10U; ///< Maximum number of startup configuration per process
constexpr uint32_t MAX_SUPPLEMENTARY_GROUPS
    = 384U;                           ///< Maximum number of supplementary groups per process
constexpr uint32_t PROCESS_MAX = 80U; ///< Maximum number of processes
constexpr uint32_t MAX_PROCESS_DEPENDENCY = 10U; ///< Maximum number of process dependencies
constexpr uint32_t MAX_PROCESS_RESOLVER = 40U;   ///< Maximum number of process resolvers
constexpr uint32_t MAX_ARGUMENTS = 20U;          ///< Maximum number of arguments
constexpr uint32_t MAX_ENV_VARIABLES = 20U;      ///< Maximum number of env variables
constexpr uint32_t MAX_LENGTH_OF_PATH = 100U;    ///< Maximum size of path for executable
constexpr uint32_t MAX_DIR_SIZE = 100U;          ///< Maximum size of current working directory path
constexpr uint32_t MAXSIZE_FUNC_GROUP_OR_STATE_NAME
    = 100U; ///< Maximum size of func group name or func group state name
constexpr uint8_t MAXSIZE_SECPOL_TYPE_NAME = 100U; ///< Maximum size of QNX type name
constexpr uint32_t MAX_FUNC_GROUP = 40U;           ///< Maximum number of function groups
constexpr uint32_t MAX_RESOURCE_GROUP = 20U;       ///< Maximum number of function groups
constexpr uint32_t MAX_FUNC_GROUP_STATE_PER_FG
    = 20U; ///< Maximum number of states per function group
constexpr uint32_t MAX_PROCESS_PER_FUNC_GROUP_STATE
    = 80U; ///< Maximum number of processes per function group state
constexpr uint32_t MAX_FUNC_GROUP_STATE_PER_PROCESS
    = 10U; ///< Maximum number of function group states per process
constexpr uint32_t MAX_FUNC_GROUP_CHANNEL = 3U; ///< Maximum number of function group channels
constexpr uint32_t MAX_FUNC_GROUP_PARALLEL_REQUEST
    = 20U; ///< Maximum number of function group parallel requests
constexpr uint32_t MAX_PIPE_MESSAGE_SIZE = 5120U; ///< Maximum size of a message sent through a pipe
constexpr uint32_t SYSCALL_TIMEOUT = 200U;        ///< Syscall timeout
constexpr uint32_t RESOURCE_GROUP_NAME_SIZE
    = 100U; ///< Maximum size of a Resource Group partition name. it is 15 in QNX documentation
constexpr char MACHINE_RESOURCE_GROUP_NAME[RESOURCE_GROUP_NAME_SIZE]
    = "MachineResourceGroup";             ///< Machine Resource Group Name
constexpr uint32_t INSTANCE_NAME_SIZE = 100U; ///< @brief Maximum size of instance name

/// @brief Maximum number of env variables. 3 additional environment
///        varibales are needed for passing following values to the Processes:
///        ProcessIdentifier, TraceLogLevel, TraceLogId
constexpr uint32_t MAX_EFFECTIVE_ENV_VARIABLES = MAX_ENV_VARIABLES + 3U;

/// @brief Maximum function group state transition per "set state" request
static constexpr uint32_t maxTransitionsPerRequest = 10U;

/// @brief Maximum number of limits per process
static constexpr uint32_t MAX_PROCESS_LIMITS = 3U;

/// @brief Argument size for an instance
static constexpr uint32_t ARG_ENV_SIZE = 500U;

/// @brief maximum number of file descriptors to be used for communicating state change
constexpr uint32_t MAX_FD = 3U;

} /* namespace utils */
} /* namespace exm */

#endif
