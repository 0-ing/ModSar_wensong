//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/cfg/registry.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_CFG_REGISTRY_H_
#define UCM_AAP_LIBRARY_LIB_CFG_REGISTRY_H_

#include <array>
#include <cstddef>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/cfg/table.h"
#include "ucm/lib/cfg/parser.h"

namespace bosch {
namespace vrte {
namespace ucm {
namespace lib {
namespace cfg {

class Registry final
    : virtual protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ConfigParser, Simple);
#endif

public:
    explicit Registry() = default;

    Registry(Registry     &&) = delete;
    Registry(Registry const&) = delete;

    Registry& operator=(Registry     &&) = delete;
    Registry& operator=(Registry const&) = delete;

    ~Registry() = default;

    bool parse(Table&) noexcept { return pop<bool>(); }

    void register_parser(std::unique_ptr<Parser>&&) { return pop<void>(); }
};

}    // namespace cfg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_CFG_REGISTRY_H_
