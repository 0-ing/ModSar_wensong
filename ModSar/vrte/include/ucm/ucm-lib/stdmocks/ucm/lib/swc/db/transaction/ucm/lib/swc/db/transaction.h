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



#include "ucm/mock/sequence.h"
#include "ucm/lib/log/logger.h"
#include "ucm/lib/swc/db/backend.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {


class Transaction
        : virtual protected ucm::mock::Sequence
{

public:
    explicit Transaction(bool wlock, std::vector<std::unique_ptr<Backend>>&)
    : wlock_{wlock}
    {
    }

    Transaction(Transaction     &&) = default;
    Transaction(Transaction const&) = delete;

    Transaction& operator=(Transaction     &&) = default;
    Transaction& operator=(Transaction const&) = delete;

    virtual ~Transaction() = default;

    void abort() noexcept {pop<void>();}

    void commit()  {pop<void>();}

    Result do_query(Query&&)  {return pop<Result&&>();}

    Result irecords_select()  {return pop<Result&&>();}
    Result frecords_select()  {return pop<Result&&>();}
    Result hrecords_select()  {return pop<Result&&>();}
    Result srecords_select()  {return pop<Result&&>();}
    Result irecords_select(std::string&&)  {return pop<Result&&>();}
    Result irecords_select(std::string&&, Version&&)  {return pop<Result&&>();}
    Result hrecords_select(std::string&&)  {return pop<Result&&>();}
    Result hrecords_select(std::string&&, Version&&)  {return pop<Result&&>();}
    Result hrecords_select(const astate_type&, const aerror_type&)  {return pop<Result&&>();}
    Result hrecords_select(const astate_type&)  {return pop<Result&&>();}
    Result frecords_select(std::string&&, Version&&)  {return pop<Result&&>();}
    Result frecords_select(std::string&&, Version&&, FRecord::Type&&)  {return pop<Result&&>();}
    Result srecords_select(std::string&&) {return pop<Result&&>();}
    Result srecords_select(std::string&&, Version&&) {return pop<Result&&>();}

    unique_type irecords_count()  {return pop<unique_type>();}
    unique_type frecords_count()  {return pop<unique_type>();}
    unique_type hrecords_count()  {return pop<unique_type>();}
    unique_type srecords_count()  {return pop<unique_type>();}
    unique_type irecords_count(const std::string&)  {return pop<unique_type>();}
    unique_type irecords_count(const std::string&, const Version&)  {return pop<unique_type>();}
    unique_type frecords_count(const std::string&, const Version&)  {return pop<unique_type>();}
    unique_type frecords_count(const std::string&,
                               const Version&,
                               const FRecord::Type&)  {return pop<unique_type>();}
    unique_type srecords_count(const std::string&) {return pop<unique_type>();}
    unique_type srecords_count(const std::string&, const Version&) {return pop<unique_type>();}

    Result swc_select_last(const std::string&, const Version&)  {return pop<Result&&>();}
    Result swc_select_last(const std::string&, const astate_type&)  {return pop<Result&&>();}
    Result swc_select_last(const std::string&,
                           const astate_type&,
                           const aerror_type&)  {return pop<Result&&>();}


    Result swc_replace(FRecord&&)  {return pop<Result&&>();}
    Result swc_replace(FRecord&&, const FRecord::Type&)  {return pop<Result&&>();}
    Result swc_replace(SRecord&&) {return pop<Result&&>();}


    Result swc_resolve(const IRecord&)  {return pop<Result&&>();}

    void swc_update(DepUnit&&, astate_type&&, aerror_type&&) {pop<void>();}
    void swc_update(DepUnit&&, FRecord&&, FRecord::Type) {pop<void>();}
    void swc_create(IRecord&&, FRecord&&) {pop<void>();}
    void swc_create(IRecord&&) {pop<void>();}
    void swc_create(FRecord&&) {pop<void>();}
    void swc_create(SRecord&&) {pop<void>();}
    void swc_create(HRecord&&) {pop<void>();}
    void swc_remove(FRecord&&) {pop<void>();}
    void swc_remove(FRecord&&, SRecord&&) {pop<void>();}
    void swc_remove(SRecord&&) {pop<void>();}

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
