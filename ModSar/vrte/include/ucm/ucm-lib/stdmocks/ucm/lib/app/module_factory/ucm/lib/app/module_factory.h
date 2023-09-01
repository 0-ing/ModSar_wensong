//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/lib/app/module_factory/ucm/lib/app/module_factory.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_FACTORY_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_FACTORY_H_

#include <memory>
#include <string>

#include "ucm/lib/app/module.h"
#include "ucm/lib/app/core_context.h"
#include "ucm/lib/upd/transactions_manager.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace app   {

struct ModuleFactory
{
    explicit ModuleFactory() = default;

    ModuleFactory(ModuleFactory     &&) = default;
    ModuleFactory(ModuleFactory const&) = default;

    ModuleFactory& operator=(ModuleFactory     &&) = default;
    ModuleFactory& operator=(ModuleFactory const&) = default;

    virtual ~ModuleFactory() = default;

    virtual Module* create(CoreContext&, upd::TransactionsManager&)
    {
        return nullptr;
    }
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__MODULE_FACTORY_H_
