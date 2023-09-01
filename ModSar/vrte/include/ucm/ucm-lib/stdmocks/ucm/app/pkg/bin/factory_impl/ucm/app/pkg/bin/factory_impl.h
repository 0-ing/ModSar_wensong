//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/bin/factory_impl/ucm/app/pkg/bin/factory_impl.h
/// @brief        Implementation of factory for SWP process/compose objects.
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_

#include <array>
#include <algorithm>

#include "ucm/lib/buf/array.h"
#include "ucm/app/pkg/bin/types.h"
#include "ucm/lib/pkg/bin/factory.h"
#include "ucm/app/pkg/bin/ctx_cache.h"
#include "ucm/app/pkg/bin/v01xx/bitable.h"

#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

class FactoryImpl final
    : public lib::pkg::bin::Factory
    , virtual protected ucm::mock::Sequence
{
public:
    explicit FactoryImpl(lib::sec::Provider& sp)
        : lib::pkg::bin::Factory(sp)
    {}

    FactoryImpl(FactoryImpl     &&) = default;
    FactoryImpl(FactoryImpl const&) = default;

    FactoryImpl& operator=(FactoryImpl     &&) = default;
    FactoryImpl& operator=(FactoryImpl const&) = default;

    ~FactoryImpl() = default;

    bool is_supported(uint32_t, uint32_t) const noexcept override
    { return pop<bool>(); }

    std::unique_ptr<lib::pkg::bin::SWP_Compose>
    swp_compose(const std::string&, uint32_t, uint32_t) override
    { return pop<std::unique_ptr<lib::pkg::bin::SWP_Compose>&&>(); }

    std::unique_ptr<lib::pkg::bin::SWP_Process>
    swp_process(const lib::pkg::bin::AuthBlock&,
                const std::string&, const std::string&) override
    { return pop<std::unique_ptr<lib::pkg::bin::SWP_Process>&&>(); }
};

}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__FACTORY_IMPL_H_
