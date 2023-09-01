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

#ifndef TESTS_VRTE_UT_MOCKS_POCO_SHAREDPTR_H_
#define TESTS_VRTE_UT_MOCKS_POCO_SHAREDPTR_H_

namespace Poco {

template<typename T>
class SharedPtr
{
public:
    SharedPtr()
    {
    }
    T* operator ->()
    {
        T* Status_T { };
        return Status_T;
    }
};
} // namespace poco

#endif /* TESTS_VRTE_UT_MOCKS_POCO_JSON_POCO_JSON_SHAREDPTR_H_ */
