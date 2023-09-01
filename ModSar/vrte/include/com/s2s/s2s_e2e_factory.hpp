//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by DENSO CORPORATION and Robert Bosch GmbH.
// All rights reserved.
//
// This file is property of DENSO CORPORATION and Robert Bosch GmbH. Any
// unauthorized copy, use or distribution is an offensive act against
// international law and may be prosecuted under federal law. Its content is
// company confidential.
//=============================================================================
#ifndef S2S_E2E_FACTORY_HPP
#define S2S_E2E_FACTORY_HPP

#include "s2s/s2s_types.hpp"

namespace com
{
namespace s2s
{
/**
 * @brief Get protector
 * @param cfg configuration for E2E
 * @return Protector
 */
com::e2e::IE2EProtector* getProtector(const S2SE2EConfig& cfg);

/**
 * @brief Get checker
 * @param cfg configuration for E2E
 * @return Checker
 */
com::e2e::IE2EChecker* getChecker(const S2SE2EConfig& cfg);

} // namespace s2s
} // namespace com

#endif
