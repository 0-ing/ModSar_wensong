//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/hrecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HRECORD_H_

#include <cstdint>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/hrecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class HRecord final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__HRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__HRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__HRecord, Save);
#endif
public:
    explicit HRecord(Header&);
    explicit HRecord(Header&, swc::HRecord&&);

    HRecord(HRecord     &&) = default;
    HRecord(HRecord const&) = default;

    HRecord& operator=(HRecord     &&) = delete;
    HRecord& operator=(HRecord const&) = delete;

    ~HRecord() = default;

    void load(lib::utl::FileIO&);

    void save(lib::utl::FileIO&);

    swc::HRecord& record() &  noexcept;
    swc::HRecord  record() && noexcept;
    const swc::HRecord&  record() const & noexcept;

private:
    Header& header_;
    swc::HRecord record_{};
};

inline swc::HRecord& HRecord::record() &  noexcept
{
    return record_;
}

inline swc::HRecord HRecord::record() && noexcept
{
    return std::move(record_);
}

inline const swc::HRecord& HRecord::record() const & noexcept
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

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__HRECORD_H_
