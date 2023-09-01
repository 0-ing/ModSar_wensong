//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/pkg/mnf/configuration.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__CONFIGURATION_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__CONFIGURATION_H_

#include <string>
#include <vector>
#include <limits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/pkg/mnf/model/artifact_security.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

class Configuration final
    : protected virtual mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test__ucm_lib_pkg_mnf__Model, TEST__CTor);
#endif
    constexpr static std::size_t maxid() noexcept
    {
        return std::numeric_limits<std::size_t>::max();
    }

public:
    explicit Configuration() = default;

    explicit Configuration(std::size_t&&,
                           std::string&&) {}

    explicit Configuration(std::size_t&&,
                           std::vector<std::string>&&) {}

    Configuration(      Configuration&&) = default;
    Configuration(const Configuration &) = default;

    Configuration& operator=(      Configuration&&) = default;
    Configuration& operator=(const Configuration &) = default;

    ~Configuration() = default;

    const auto& script()  const noexcept;
    const auto& fgroups() const noexcept;

private:
    std::size_t script_id_{maxid()};
    std::vector<std::string> fgroups_{};
};

inline const auto& Configuration::script() const noexcept
{
    return pop<std::size_t const&>();
}

inline const auto& Configuration::fgroups() const noexcept
{
    return pop<std::vector<std::string> const&>();
}


}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__CONFIGURATION_H_
