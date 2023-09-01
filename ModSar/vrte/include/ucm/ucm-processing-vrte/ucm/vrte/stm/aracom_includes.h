//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/vrte/stm/aracom_includes.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_PROCESSING_VRTE_STM_ARACOM_INCLUDES_H_
#define UCM_AAP_PROCESSING_VRTE_STM_ARACOM_INCLUDES_H_

#include <memory>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wstack-protector"
#pragma GCC diagnostic ignored "-Wstrict-overflow"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#include "ara/sm/update_request/updaterequest_proxy.h"
#include "ara/sm/update_request/updaterequest_common.h"
#pragma GCC diagnostic pop

#endif    // UCM_AAP_PROCESSING_VRTE_STM_ARACOM_INCLUDES_H_
