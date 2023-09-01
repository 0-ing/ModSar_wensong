//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/srecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       dsh8cob
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__SRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__SRECORD_H_

#include <cstdint>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/srecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class SRecord final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__SRecord, CTor);
#endif
public:
    explicit SRecord(Header&);
    explicit SRecord(Header&, swc::SRecord&&);

    SRecord(SRecord     &&) = default;
    SRecord(SRecord const&) = default;

    SRecord& operator=(SRecord     &&) = delete;
    SRecord& operator=(SRecord const&) = delete;

    ~SRecord() = default;

    void load(lib::utl::FileIO&);

    void save(lib::utl::FileIO&);

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
