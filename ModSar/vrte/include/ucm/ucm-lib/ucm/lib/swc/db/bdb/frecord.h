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

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/frecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FRecord final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__FRecord, Save);
#endif
public:
    explicit FRecord(Header&);
    explicit FRecord(Header&, swc::FRecord&&);

    FRecord(FRecord     &&) = default;
    FRecord(FRecord const&) = default;

    FRecord& operator=(FRecord     &&) = delete;
    FRecord& operator=(FRecord const&) = delete;

    ~FRecord() = default;

    void load(lib::utl::FileIO&);

    void save(lib::utl::FileIO&);

    swc::FRecord& record() &  noexcept;
    swc::FRecord  record() && noexcept;
    const swc::FRecord&  record() const & noexcept;

private:
    Header& header_;
    swc::FRecord record_{};
};

inline swc::FRecord& FRecord::record() &  noexcept
{
    return record_;
}

inline swc::FRecord FRecord::record() && noexcept
{
    return std::move(record_);
}

inline const swc::FRecord& FRecord::record() const & noexcept
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

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FRECORD_H_
