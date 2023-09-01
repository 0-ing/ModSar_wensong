//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2020-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file sync.h
/// @brief This file contains common types definitions for the logging API.
///
/// @attention Due to limitation of the C++ language, some internal implementation
/// (e.g. the function bodies) are coded directly into this header file.
/// Such code is NOT meant to be used or referred to by a user directly,
/// and is subject to CHANGE WITHOUT NOTICE.
/// Therefore DO NOT DEPEND ON any implementation details!
//==============================================================================

#ifndef ARA_LOG_SYNC_H_
#define ARA_LOG_SYNC_H_

namespace ara {
namespace log {

/**
 * @defgroup sync Sync log messages
 * @brief Flush log buffers
 */

/// @addtogroup sync
/// @{

/// @brief Sync console log messages from buffers to stdout
///
/// This call will block until all messages that were in the buffer are forwarded to the OS.
/// If the process segfaults directly after the call returned, then all messages should still
/// appear on the console.
void Sync();

/// @}

} /* namespace log */
} /* namespace ara */

#endif  // ARA_LOG_SYNC_H_
