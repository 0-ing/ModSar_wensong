//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/mock/ucm/lib/pkg/mnf/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_

#include <memory>

#include "ucm/lib/pkg/mnf/types.h"
#include "ucm/lib/pkg/mnf/model/manifest.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace pkg   {
namespace mnf   {

struct Parser
{
};

struct Schema
{
};

struct Factory
{
    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;

    virtual ~Factory() = default;

    virtual std::unique_ptr<Parser>
    json_parser(unsigned long, unsigned long)
    {
        return std::make_unique<Parser>();
    }


    virtual std::unique_ptr<Schema>
    json_schema(unsigned long, unsigned long)
    {
        return std::make_unique<Schema>();
    }

    virtual bool
    is_schema_supported(unsigned long, unsigned long) noexcept
    {
        return true;
    }

    virtual bool
    is_parser_supported(unsigned long, unsigned long) noexcept
    {
        return true;
    }
};

}    // namespace mnf
}    // namespace pkg
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_PKG_MNF__FACTORY_H_
