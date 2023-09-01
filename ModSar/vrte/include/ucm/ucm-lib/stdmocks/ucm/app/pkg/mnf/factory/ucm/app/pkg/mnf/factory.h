//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/mnf/factory/ucm/app/pkg/mnf/factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_mnf

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_

#include "ucm/mock/sequence.h"
#include "ucm/lib/pkg/mnf/factory.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace mnf   {

class Factory
        : public lib::pkg::mnf::Factory
{
public:
    explicit Factory() = default;

    Factory(      Factory&&) = default;
    Factory(const Factory &) = default;

    Factory& operator=(      Factory&&) = default;
    Factory& operator=(const Factory &) = default;

    virtual ~Factory() = default;

    std::unique_ptr<lib::pkg::mnf::Parser>
    json_parser(unsigned long, unsigned long) override
    { return pop<std::unique_ptr<lib::pkg::mnf::Parser>&&>(); }

    std::unique_ptr<lib::pkg::mnf::Schema>
    json_schema(unsigned long, unsigned long) override
    { return pop<std::unique_ptr<lib::pkg::mnf::Schema>&&>(); }

    bool is_schema_supported(unsigned long, unsigned long) noexcept override
    { return pop<bool>(); }

    bool is_parser_supported(unsigned long, unsigned long) noexcept override
    { return pop<bool>(); }
};

}    // namespace mnf
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_MNF__FACTORY_H_
