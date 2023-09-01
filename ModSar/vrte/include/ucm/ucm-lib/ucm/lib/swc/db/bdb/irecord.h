//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/irecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_

#include <cstdint>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/irecord.h"
#include "ucm/lib/swc/db/bdb/header.h"


namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class IRecord final
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__IRecord, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__IRecord, Load);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__IRecord, Save);
#endif
public:
    explicit IRecord(const Header&);
    explicit IRecord(const Header&, swc::IRecord&&);

    IRecord(IRecord     &&) = default;
    IRecord(IRecord const&) = default;

    IRecord& operator=(IRecord     &&) = delete;
    IRecord& operator=(IRecord const&) = delete;

    ~IRecord() = default;

    void load(lib::utl::FileIO&);

    void save(lib::utl::FileIO&);

    swc::IRecord& record() &  noexcept;
    swc::IRecord  record() && noexcept;
    const swc::IRecord&  record() const & noexcept;

private:
    const Header& header_;
    swc::IRecord record_{};
};

inline swc::IRecord& IRecord::record() &  noexcept
{
    return record_;
}

inline swc::IRecord IRecord::record() && noexcept
{
    return std::move(record_);
}

inline const swc::IRecord& IRecord::record() const & noexcept
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

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__IRECORD_H_
