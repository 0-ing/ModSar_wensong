//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/app/pkg/bin/v01xx/bit_compose.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks
/// @ingroup      bosch_vrte_ucm_app_pkg_bin_v01xx

#ifndef UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_
#define UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_

#include "ucm/lib/log/ref_logger.h"
#include "ucm/app/pkg/bin/v01xx/bitable.h"
#include "ucm/app/pkg/bin/v01xx/auth_block.h"
#include "ucm/app/pkg/bin/v01xx/data_block.h"

#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace app   {
namespace pkg   {
namespace bin   {
namespace v01xx {

class BIT_Compose final
    : public BITable
    , virtual protected ucm::mock::Sequence
{
    using Base = BITable;

public:

    explicit BIT_Compose(std::size_t, std::size_t,
                         std::size_t, std::size_t) noexcept {}

    BIT_Compose(BIT_Compose     &&) = default;
    BIT_Compose(BIT_Compose const&) = default;

    BIT_Compose& operator=(BIT_Compose     &&) = default;
    BIT_Compose& operator=(BIT_Compose const&) = delete;

    ~BIT_Compose() = default;

    size_t swp_size() const noexcept
    { return pop<size_t>(); }

    Error add_files(const std::vector<sfile_pair>&) noexcept
    { return pop<Error>(); }

    Error save_package(lib::utl::FileIO&, DataBlock& ,
                       const std::vector<sfile_pair>&) noexcept
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

#endif // UCM_AAP_LIBRARY__UCM_APP_PKG_BIN_V01XX__BIT_COMPOSE_H_
