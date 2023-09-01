//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/bit_process.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_PROCESS_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_PROCESS_H_

#include "ucm/app/pkg/bin/v01xx/bitable.h"
#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class BIT_Process final 
      : public BITable
      , virtual protected ucm::mock::Sequence
{
    using Base = BITable;

public:
    explicit BIT_Process() = default;

    BIT_Process(BIT_Process     &&) = default;
    BIT_Process(BIT_Process const&) = delete;

    BIT_Process& operator=(BIT_Process     &&) = default;
    BIT_Process& operator=(BIT_Process const&) = delete;

    ~BIT_Process() = default;

    virtual void reset() noexcept {}

    Error set_records(const void*, size_t) noexcept
    { return pop<Error>(); }
};


}    // namespace v01xx
}    // namespace bin
}    // namespace pkg
}    // namespace app
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

/// @}

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_PROCESS_H_
