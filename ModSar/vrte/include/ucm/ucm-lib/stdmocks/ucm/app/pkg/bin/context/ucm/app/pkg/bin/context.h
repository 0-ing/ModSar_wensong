//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocks/ucm/app/pkg/bin/context/ucm/app/pkg/bin/context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_

#include "ucm/lib/buf/model.h"
#include "ucm/lib/sec/provider.h"
#include "ucm/lib/utl/object_locker.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {

class Context : public lib::utl::ObjectLocker
{
public:
    using Buffer  = lib::buf::Model;

    explicit Context(lib::sec::Provider& sec_provider)
        : sec_provider_{sec_provider}
    {}

    Context(Context     &&) = default;
    Context(Context const&) = delete;

    Context& operator=(Context     &&) = default;
    Context& operator=(Context const&) = delete;

    virtual ~Context() = default;

    virtual Buffer& data_buffer() noexcept = 0;

    virtual Buffer& auth_buffer() noexcept = 0;

    lib::sec::Provider& sec_provider() noexcept
    {
        return sec_provider_;
    }

protected:
    /// @brief Reference to UCM wide security provider.
    lib::sec::Provider& sec_provider_;
};

}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN__CONTEXT_H_
