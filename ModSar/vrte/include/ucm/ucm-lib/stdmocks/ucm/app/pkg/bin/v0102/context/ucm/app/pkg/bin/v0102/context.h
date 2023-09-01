//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2022 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         tests/VRTE_UT/stdmocs/ucm/app/pkg/bin/v0102/context/ucm/app/pkg/bin/v0102/context.h
/// @brief
/// @copyright    Robert Bosch GmbH 2022
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup bosch_vrte_ucm_app_pkg_bin_v0102


#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_

#include "ucm/lib/buf/model.h"
#include "ucm/app/pkg/bin/context.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v0102 {

class Context : public bosch::vrte::ucm::app::pkg::bin::Context
{
public:

    explicit Context(lib::sec::Provider& sp)
    	: bosch::vrte::ucm::app::pkg::bin::Context(sp)
    {}

    Context(Context     &&) = default;
    Context(Context const&) = delete;

    Context& operator=(Context     &&) = default;
    Context& operator=(Context const&) = delete;

    virtual ~Context() = default;

    Buffer& data_buffer() noexcept override
    { return pop<Buffer&>(); }

    Buffer& auth_buffer() noexcept override
    { return pop<Buffer&>(); }
};

}    // namespace v0102
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V0102__CONTEXT_H_
