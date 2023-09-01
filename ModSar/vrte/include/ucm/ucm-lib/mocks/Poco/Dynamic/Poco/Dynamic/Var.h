//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         Poco/Dynamic/Var.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Ashwin Kumar
/// @version
/// @remarks

#ifndef TESTS_VRTE_UT_MOCKS_POCO_DYNAMIC_POCO_DYNAMIC_VAR_H_
#define TESTS_VRTE_UT_MOCKS_POCO_DYNAMIC_POCO_DYNAMIC_VAR_H_

#include <memory>
#include "Poco/SharedPtr.h"

#include "ucm/mock/sequence.h"

namespace Poco {
namespace Dynamic {

class Var : virtual protected bosch::vrte::ucm::mock::Sequence
{
public:

    typedef std::shared_ptr<Var> Ptr;

    Var()
    {
    }

    template<typename T>
    const T& extract() const
    {
        return pop<T const&>();
    }
};

}    // namespace Dynamic
}    // namespace Poco

#endif /* TESTS_VRTE_UT_MOCKS_POCO_DYNAMIC_POCO_DYNAMIC_VAR_H_ */
