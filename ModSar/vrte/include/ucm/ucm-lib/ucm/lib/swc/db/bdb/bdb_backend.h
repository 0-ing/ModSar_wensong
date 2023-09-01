//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/bin/bdb_backend.h
/// @brief
/// @copyright    Robert Bosch GmbH 2020
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_SWC_DB_BDB__BDB_BACKEND_H_
#define UCM_AAP_LIBRARY_LIB_SWC_DB_BDB__BDB_BACKEND_H_

#include <string>
#include <atomic>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/handle.h"
#include "ucm/lib/swc/db/backend.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class BDB_Backend final : public Backend
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, Shutdown);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, Startoff);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, SelectHanle);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__BDB_Backend, UpdateHanle);
#endif

    constexpr static const char *backend_name   = "SwC_BDB";
    constexpr static const bool  irecord_enable = true;
    constexpr static const bool  hrecord_enable = true;
    constexpr static const bool  frecord_enable = true;
    constexpr static const bool  srecord_enable = true;

public:
    explicit BDB_Backend(std::string&&)
        noexcept(std::is_nothrow_constructible<Backend>::value &&
                 std::is_nothrow_constructible<std::string>::value);


    BDB_Backend(BDB_Backend     &&) = delete;
    BDB_Backend(BDB_Backend const&) = delete;

    BDB_Backend& operator=(BDB_Backend     &&) = delete;
    BDB_Backend& operator=(BDB_Backend const&) = delete;

    virtual ~BDB_Backend();

    virtual void startoff() override;
    virtual void shutdown() override;

    virtual std::unique_ptr<Handle> select_handle() override;
    virtual std::unique_ptr<Handle> update_handle() override;

private:
    void ensure_directory();
};

}    // namespace bin
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_SWC_DB_BDB__BDB_BACKEND_H_
