//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/transaction.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__TRANSACTION_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__TRANSACTION_H_


#if defined(GOOGLE_TEST)
#include "gtest/gtest_prod.h"
#endif

#include "ucm/lib/log/logger.h"
#include "ucm/lib/swc/db/backend.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Transaction
{
#if defined(GOOGLE_TEST)
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, CTor);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, Abort);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, Commit);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery2);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery3);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery4);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery5);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery6);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery7);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, DoQuery8);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, IRecords_Count);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, HRecords_Count);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, FRecords_Count);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, IRecords_Select);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, HRecords_Select);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, FRecords_Select);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_SelectLast1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_SelectLast2);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Resolve);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Replace1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Replace2);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Create1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Create2);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Create3);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Create4);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Remove);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Update1);
    FRIEND_TEST(Test_ucm_lib_swc_db__Transaction, SwC_Update2);
#endif
public:
    explicit Transaction(bool wlock, std::vector<std::unique_ptr<Backend>>&);

    Transaction(Transaction     &&) = default;
    Transaction(Transaction const&) = delete;

    Transaction& operator=(Transaction     &&) = default;
    Transaction& operator=(Transaction const&) = delete;

    virtual ~Transaction();

    void abort() noexcept;

    void commit();

    Result do_query(Query&&);

    Result irecords_select();
    Result frecords_select();
    Result hrecords_select();
    Result srecords_select();
    Result irecords_select(std::string&&);
    Result irecords_select(std::string&&, Version&&);
    Result hrecords_select(std::string&&);
    Result hrecords_select(std::string&&, Version&&);
    Result hrecords_select(const astate_type&, const aerror_type&);
    Result hrecords_select(const astate_type&);
    Result frecords_select(std::string&&, Version&&);
    Result frecords_select(std::string&&, Version&&, FRecord::Type&&);
    Result srecords_select(std::string&&);
    Result srecords_select(std::string&&, Version&&);

    unique_type irecords_count();
    unique_type frecords_count();
    unique_type hrecords_count();
    unique_type srecords_count();
    unique_type irecords_count(const std::string&);
    unique_type irecords_count(const std::string&, const Version&);
    unique_type frecords_count(const std::string&, const Version&);
    unique_type frecords_count(const std::string&,
                               const Version&,
                               const FRecord::Type&);
    unique_type srecords_count(const std::string&);
    unique_type srecords_count(const std::string&, const Version&);

    Result swc_select_last(const std::string&, const Version&);
    Result swc_select_last(const std::string&, const astate_type&);
    Result swc_select_last(const std::string&,
                           const astate_type&,
                           const aerror_type&);


    Result swc_replace(FRecord&&);
    Result swc_replace(FRecord&&, const FRecord::Type&);
    Result swc_replace(SRecord&&);

    Result swc_resolve(const IRecord&);

    void swc_update(DepUnit&&, astate_type&&, aerror_type&&);
    void swc_update(DepUnit&&, FRecord&&, FRecord::Type);
    void swc_create(IRecord&&, FRecord&&, SRecord&&);
    void swc_create(IRecord&&, FRecord&&);
    void swc_create(IRecord&&);
    void swc_create(FRecord&&);
    void swc_create(SRecord&&);
    void swc_create(HRecord&&);
    void swc_remove(FRecord&&, SRecord&&);
    void swc_remove(SRecord&&);
    void swc_remove(FRecord&&);

protected:
    bool wlock_{false};
    log::Logger logger_{};
    std::vector<std::unique_ptr<Handle>> handles_{};
};


}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB__TRANSACTION_H_
