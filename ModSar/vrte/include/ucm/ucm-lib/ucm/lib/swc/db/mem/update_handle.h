//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/mem/update_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__UPDATE_HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__UPDATE_HANDLE_H_

#include <vector>
#include <memory>
#include <type_traits>

#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/swc/db/mem/select_handle.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace mem   {


class UpdateHandle : public SelectHandle
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Insert1);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Insert2);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Insert3);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Insert4);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Update1);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Update2);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Update3);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Remove1);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, Remove2);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, DoQuery1);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, DoQuery2);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, DoQuery3);
    FRIEND_TEST(Test_ucm_lib_swc_db_mem__UpdateHandle, DoQuery4);
#endif
public:
    explicit UpdateHandle(Mutex& mutex, const Tuple&,
                          std::vector<IRecord>&,
                          std::vector<HRecord>&,
                          std::vector<FRecord>&,
                          std::vector<SRecord>&,
                          unique_type&, unique_type&,
                          unique_type&, unique_type&);

    UpdateHandle(UpdateHandle     &&) = default;
    UpdateHandle(UpdateHandle const&) = delete;

    UpdateHandle& operator=(UpdateHandle     &&) = delete;
    UpdateHandle& operator=(UpdateHandle const&) = delete;

    virtual ~UpdateHandle() = default;

    virtual void abort() noexcept override;

    virtual void commit() override;

    virtual Result do_query(Query&&) override;

protected:
    unique_type& iunique_;
    unique_type& hunique_;
    unique_type& funique_;
    unique_type& sunique_;

    virtual Result insert(Query&&);
    virtual Result update(Query&&);
    virtual Result remove(Query&&);

    std::vector<unique_type> insert(std::vector<IRecord>&&);
    void insert(std::vector<HRecord>&&, const std::vector<unique_type>&);
    void insert(std::vector<FRecord>&&, const std::vector<unique_type>&);
    void insert(std::vector<SRecord>&&);
};


}    // namespace mem
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__UPDATE_HANDLE_H_
