//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         tests/VRTE_UT/mocks/ucm/lib/swc/db/bdb/srecord/ucm/lib/swc/db/bdb/srecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__SRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__SRECORD_H_

#include "ucm/lib/swc/srecord.h"
#include "ucm/lib/swc/db/bdb/header.h"

#include "ucm/mock/sequence.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

struct SRecord : virtual protected ucm::mock::Sequence

{
    explicit SRecord(Header& header)
        : header_{header}
    {}

    explicit SRecord(Header& header, swc::SRecord&& record)
        : header_{header}
        , record_{record}
    {}

    SRecord(SRecord     &&) = default;
    SRecord(SRecord const&) = default;

    SRecord& operator=(SRecord     &&) = default;
    SRecord& operator=(SRecord const&) = default;

    ~SRecord() = default;

    void load(lib::utl::FileIO&)
    {
        record_ = pop<swc::SRecord&>();
    }

    void save(lib::utl::FileIO&) {}

    swc::SRecord& record() &  noexcept;
    swc::SRecord  record() && noexcept;
    const swc::SRecord&  record() const & noexcept;

private:
    Header& header_;
    swc::SRecord record_{};
};

inline swc::SRecord& SRecord::record() &  noexcept
{
    return record_;
}

inline swc::SRecord SRecord::record() && noexcept
{
    return std::move(record_);
}

inline const swc::SRecord& SRecord::record() const & noexcept
{
    return record_;
}


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__SRECORD_H_

