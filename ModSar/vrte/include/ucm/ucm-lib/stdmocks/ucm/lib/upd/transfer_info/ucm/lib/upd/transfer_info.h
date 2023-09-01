//=============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//=============================================================================

/// @file         ucm/lib/upd/transfer_info.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY__UCM_LIB_UPD__TRANSFER_INFO__H_
#define UCM_AAP_LIBRARY__UCM_LIB_UPD__TRANSFER_INFO__H_

#include "ucm/lib/types.h"
#include "ucm/lib/swc/depunit.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace upd   {

class TransferInfo final
{
public:
    struct Data
    {
        id_type      transaction_id_{};
        usize_type   bytes_received_{};
        usize_type   blocks_received_{};
        swc::DepUnit dependency_unit_{};
    };

    explicit TransferInfo(Data&& data)
        : data_(data) {}

    TransferInfo(TransferInfo     &&) = default;
    TransferInfo(TransferInfo const&) = default;

    TransferInfo& operator=(TransferInfo     &&) = default;
    TransferInfo& operator=(TransferInfo const&) = default;

    ~TransferInfo() = default;

    Data& data() & noexcept;

    Data data() && noexcept;

    const Data& data() const & noexcept;

private:
    Data data_{};
};

inline TransferInfo::Data& TransferInfo::data() & noexcept
{
    return data_;
}

inline TransferInfo::Data TransferInfo::data() && noexcept
{
    return std::move(data_);
}

inline const TransferInfo::Data& TransferInfo::data() const & noexcept
{
    return data_;
}



}    // namespace upd
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif    // UCM_AAP_LIBRARY__UCM_LIB_UPD__TRANSFER_INFO__H_
