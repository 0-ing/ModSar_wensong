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
//
/// @file VersionInfo_LibrbAralog.h
/// @brief VersionInfo Interface to be used interally. This is a private header-file!
//==============================================================================
#ifndef ARA_LOG_VERSIONINFO_LIBRBARALOG_H_
#define ARA_LOG_VERSIONINFO_LIBRBARALOG_H_

#ifdef __cplusplus
extern "C" {
#endif

/// @brief VersionInfo_LibrbAralog
/// Get version information and dependencies.
/// @return char *
/// @retval null terminated version information
const char* VersionInfo_LibrbAralog(void);

#ifdef __cplusplus
}
#endif

#endif  // ARA_LOG_VERSIONINFO_LIBRBARALOG_H_
