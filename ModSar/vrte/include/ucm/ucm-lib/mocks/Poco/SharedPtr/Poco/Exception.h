//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         Poco/SharedPtr.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Ashwin Kumar
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_POCO_EXEPTION_H_
#define TESTS_VRTE_UT_MOCKS_POCO_SHAREDPTR_H_

#include <stdexcept>

namespace Poco {

struct Exception : public std::exception
{
    const char* message() const noexcept
    {
        return "string";
    }
};

} // namespace poco

#endif /* TESTS_VRTE_UT_MOCKS_POCO_JSON_POCO_JSON_SHAREDPTR_H_ */
