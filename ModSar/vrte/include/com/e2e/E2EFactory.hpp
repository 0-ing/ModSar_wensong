#ifndef E2EFACTORY_HPP
#define E2EFACTORY_HPP

//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================
//
/// @file      E2EFactory.hpp
/// @brief     Factory methods for E2E protector and checker
/// @copyright Robert Bosch GmbH  2020
//=============================================================================

#include "e2e/E2EProfiles.hpp"
#include "e2e/IE2EChecker.hpp"
#include "e2e/IE2EProtector.hpp"

namespace com
{
namespace e2e
{
/**
 * @brief Function to get an E2E-protector , based on the configuration data
 *
 * Creates an instance of an E2E-protector on the heap based on the configuration data and returns a pointer to it.
 * HEAP-usage is assumed to be allowed during the creation of a proxy/skeleton class, but not during the usage of the
 * protector
 *
 * @param cde Configuration data for the E2E-protector
 * @return If provided configuration is valid , return a pointer to the E2E-protector instance  , otherwise return a
 * disabled protector
 */
IE2EProtector* getE2EProtector(const ProfileConfig& cde);

/**
 * @brief Function to get an E2E-checker , based on the configuration data
 *
 * Creates an instance of an E2E-checker on the heap based on the configuration data and returns a pointer to it.
 * HEAP-usage is assumed to be allowed during the creation of a proxy/skeleton class, but not during the usage of the
 * checker
 *
 * @param cde Configuration data for the E2E-checker
 * @return If provided configuration is valid , return a pointer to the E2E-checker instance , otherwise return a
 * disabled checker
 */
IE2EChecker* getE2EChecker(const ProfileConfig& cde);

} // namespace e2e
} // namespace com

#endif
