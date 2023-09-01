//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/frecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FRECORD_H_

#include <cstdint>
#include <type_traits>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/frecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FRecord final : virtual protected ucm::mock::Sequence
{
public:
    explicit FRecord(Header& header)
    : header_{header}
    {
    }
    explicit FRecord(Header& header, swc::FRecord&& record)
    : header_{header}
    , record_(std::move(record))
    {
    }

    FRecord(FRecord     &&) = default;
    FRecord(FRecord const&) = default;

    FRecord& operator=(FRecord     &&) = default;
    FRecord& operator=(FRecord const&) = default;

    ~FRecord() = default;

    void load(lib::utl::FileIO&) {}

    void save(lib::utl::FileIO&) {}

    swc::FRecord& record() &  noexcept;
    swc::FRecord  record() && noexcept;
    const swc::FRecord&  record() const & noexcept;

private:
    Header& header_;
    swc::FRecord record_{};
};

inline swc::FRecord& FRecord::record() &  noexcept
{
    return pop<swc::FRecord&>();
}

inline swc::FRecord FRecord::record() && noexcept
{
    return pop<swc::FRecord>();
}

inline const swc::FRecord& FRecord::record() const & noexcept
{
    return pop<swc::FRecord const&>();
}


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FRECORD_H_
