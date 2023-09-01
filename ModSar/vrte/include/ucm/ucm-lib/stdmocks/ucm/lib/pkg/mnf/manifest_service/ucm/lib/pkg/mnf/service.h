//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/mock/ucm/lib/pkg/mnf/service.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_

#include <array>
#include <memory>

#include "ucm/lib/pkg/mnf/factory.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

struct Service final
{
    explicit Service() = default;

    Service(      Service&&) = default;
    Service(const Service &) = delete;

    Service& operator=(      Service&&) = default;
    Service& operator=(const Service &) = delete;

    ~Service() = default;

    Result parse_file(const std::string&) noexcept
    {
        return Result(Manifest{});
    }

    Result parse_buff(const std::string&) noexcept
    {
        return Result(Manifest{});
    }

    void register_factory(std::unique_ptr<Factory>&&) {}
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__SERVICE_H_
