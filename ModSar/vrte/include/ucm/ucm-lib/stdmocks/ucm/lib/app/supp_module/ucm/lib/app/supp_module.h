//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/app/supp_module.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_APP__SUPP_MODULE_H_
#define UCM_AAP_LIBRARY__UCM_LIB_APP__SUPP_MODULE_H_

#include <vector>
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

class SuppModule : public Module
{
protected:
    explicit SuppModule(CoreContext& ctx,
                        upd::TransactionsManager& tmanager,
                        const std::string& name,
                        const std::string& version,
                        const std::string& buildid,
                        const std::string& githash)
        : Module(name, version, buildid, githash)
        , context_{ctx}
        , tmanager_{tmanager}
    {}

public:
    SuppModule(SuppModule     &&) = delete;
    SuppModule(SuppModule const&) = delete;

    SuppModule& operator=(SuppModule     &&) = delete;
    SuppModule& operator=(SuppModule const&) = delete;

    virtual ~SuppModule() = default;

protected:
    CoreContext& context_;
    upd::TransactionsManager& tmanager_;
};

}    // namespace app
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY__UCM_LIB_APP__SUPP_MODULE_H_
