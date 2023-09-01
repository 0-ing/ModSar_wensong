//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/log/c_oslog/ucm/lib/log/c_oslog.h
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

inline static void oslog_init(const char *progname __attribute__((unused)))
{
}

inline static void oslog_fini(void)
{
}

#define oslog_info(...)  ((void)0)
#define oslog_error(...) ((void)0)
#define oslog_debug(...) ((void)0)

#ifdef __cplusplus
}
#endif


#endif // UCM_AAP_LIBRARY__UCM_LIB_LOG__C_OSLOG_H_
