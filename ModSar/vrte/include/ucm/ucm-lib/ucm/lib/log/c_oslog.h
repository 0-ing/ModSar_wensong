//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/log/c_oslog.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_LOG__C_OSLOG_H_
#define UCM_AAP_LIBRARY__UCM_LIB_LOG__C_OSLOG_H_


#ifdef __linux__
#include <syslog.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void oslog_init(const char *progname);
void oslog_fini(void);

#if defined(UCMS_SYSLOG_ENABLE)

#if defined(__QNX__) || defined(__QNXNTO__)

void oslog_info(const char* format, ... );
void oslog_error(const char* format, ... );
void oslog_debug(const char* format, ... );

#else   // defined(__QNX__) || defined(__QNXNTO__)

#define oslog_info(...)  syslog(LOG_INFO, __VA_ARGS__)
#define oslog_error(...) syslog(LOG_ERR, __VA_ARGS__)
#define oslog_debug(...) syslog(LOG_DEBUG, __VA_ARGS__)

#endif  // defined(__QNX__) || defined(__QNXNTO__)

#else   // defined(UCMS_SYSLOG_ENABLE)

#define oslog_info(...)  ((void)0)
#define oslog_error(...) ((void)0)
#define oslog_debug(...) ((void)0)

#endif  // defined(UCMS_SYSLOG_ENABLE)

#ifdef __cplusplus
}
#endif


#endif // UCM_AAP_LIBRARY__UCM_LIB_LOG__C_OSLOG_H_
