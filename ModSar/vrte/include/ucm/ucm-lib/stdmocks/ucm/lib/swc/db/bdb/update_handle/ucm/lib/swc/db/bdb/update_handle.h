//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/update_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__UPDATE_HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__UPDATE_HANDLE_H_

#include <vector>
#include <memory>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/bdb/select_handle.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {


class UpdateHandle
      : public SelectHandle
      , protected ucm::mock::Sequence
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, Count);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, Select);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, Insert);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, Update);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, Remove);
    FRIEND_TEST(Test_ucm_lib_swc_db_bdb__UpdateHandle, DoQuery);
#endif
public:
    explicit UpdateHandle(Mutex& mutex, const Tuple& tuple)
    : SelectHandle(true, mutex, tuple)
    {}

    UpdateHandle(UpdateHandle     &&) = default;
    UpdateHandle(UpdateHandle const&) = delete;

    UpdateHandle& operator=(UpdateHandle     &&) = default;
    UpdateHandle& operator=(UpdateHandle const&) = delete;

    virtual ~UpdateHandle();

    virtual void abort() noexcept override {pop<void>();}

    virtual void commit() override {pop<void>();}

    virtual Result do_query(Query&&) override {return pop<Result>();}

protected:
    virtual Result insert(Query&&) {return pop<Result>();}
    virtual Result update(Query&&) {return pop<Result>();}
    virtual Result remove(Query&&) {return pop<Result>();}

};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__UPDATE_HANDLE_H_
