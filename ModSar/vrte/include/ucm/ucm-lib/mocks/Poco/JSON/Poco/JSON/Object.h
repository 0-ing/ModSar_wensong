//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         Poco/JSON/Object.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Ashwin Kumar
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_POCO_JSON_OBJECT_H_
#define TESTS_VRTE_UT_MOCKS_POCO_JSON_OBJECT_H_

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include "Poco/Exception.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace cfg   {

extern bool exception_b;

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

namespace Poco {
namespace JSON {

struct JSONException : public Exception
{
    std::string name() const { return std::string(""); }

    std::string message() const { return std::string(""); }

    std::string displayText() const { return std::string(""); }
};

class Object
{
public:
    typedef Object *Ptr;
    typedef std::map<std::string, Dynamic::Var> ValueMap;
    typedef ValueMap::value_type ValueType;
    typedef ValueMap::iterator Iterator;
    typedef ValueMap::const_iterator ConstIterator;
    typedef std::vector<std::string> NameList;

    Object()
    {
    }
    bool has(const std::string& key)
    {
        if (!(key.compare(swcspecsname_))) {
            return false;
        }
        else {

            if (bosch::vrte::ucm::lib::cfg::exception_b) {
                throw std::runtime_error("exception");
            }
        }
        return has_;
    }

    Dynamic::Var get(const std::string& key)
    {
        Dynamic::Var Var_C { };
        (void)(key);
        return Var_C;
    }

    bool isObject(const std::string& key)
    {
        (void)(key);
        return isobj_;
    }

    template<typename T>
    T getValue(const char* key) const
    {
        return swcspecsname_;
    }

    bool has_{};
    bool isobj_{};
    std::string swcspecsname_{};

};

template<>
inline std::size_t Object::getValue(const char*) const
{
    return 1;
}



}    // namespace JSON
}    // namespace Poco

#endif /* TESTS_VRTE_UT_MOCKS_POCO_JSON_OBJECT_H_ */
