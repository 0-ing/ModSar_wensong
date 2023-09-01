//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         Poco/JSON/Array.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Ashwin Kumar
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_POCO_JSON_POCO_JSON_ARRAY_H_
#define TESTS_VRTE_UT_MOCKS_POCO_JSON_POCO_JSON_ARRAY_H_

#include <memory>
#include <vector>
#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"

namespace Poco {
namespace JSON {

class Array
{
public:

    typedef Array *Ptr;
    typedef std::vector<Dynamic::Var> ValueVec;
    typedef std::vector<Dynamic::Var>::iterator Iterator;
    typedef std::vector<Dynamic::Var>::const_iterator ConstIterator;
    ValueVec _values {};

    Array(int options = 0) {}
    /// Creates an empty Array.
    ///
    /// If JSON_ESCAPE_UNICODE is specified, when the object is
    /// stringified, all unicode characters will be escaped in the
    /// resulting string.

    Array(const Array& copy) = default;
    /// Creates an Array by copying another one.

#ifdef POCO_ENABLE_CPP11

        Array(Array&& other) = default;
        /// Move constructor

        Array& operator=(Array&& other) = default;
        /// Move assignment operator.

#endif // POCO_ENABLE_CPP11

    Array& operator=(const Array& other) = default;
    /// Assignment operator.

    virtual ~Array() = default;

    ValueVec::const_iterator begin() const
    {
        /* if (_values.empty()) */
        /*     return ConstIterator {}; // work-around for POCO empty array */
        return _values.cbegin();
    }

    ValueVec::const_iterator end() const
    {
        /* if (_values.empty()) */
        /*     return ConstIterator {}; // work-around for POCO empty array */
        return _values.cend();
    }

    std::size_t size() const
    {
        return _values.size();
    }

};


}    // namespace JSON
}    // namespace Poco

#endif /* TESTS_VRTE_UT_MOCKS_POCO_JSON_POCO_JSON_ARRAY_H_ */
