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

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/mem/select_handle.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace mem   {


class UpdateHandle
        : public SelectHandle
        , virtual protected ucm::mock::Sequence
{

public:
    explicit UpdateHandle(Mutex& mutex, const Tuple& tuple,
                          std::vector<IRecord>& irecords,
                          std::vector<HRecord>& hrecords,
                          std::vector<FRecord>& frecords,
                          std::vector<SRecord>& srecords,
                          unique_type& iunique, unique_type& hunique,
                          unique_type& funique, unique_type& sunique)
    : SelectHandle(true, mutex, tuple, irecords, hrecords, frecords, srecords)
    , iunique_{iunique}
    , hunique_{hunique}
    , funique_{funique}
    , sunique_{sunique}
    {}

    UpdateHandle(UpdateHandle     &&) = default;
    UpdateHandle(UpdateHandle const&) = delete;

    UpdateHandle& operator=(UpdateHandle     &&) = default;
    UpdateHandle& operator=(UpdateHandle const&) = delete;

    virtual ~UpdateHandle() = default;

    virtual void abort() noexcept override {pop<void>();}

    virtual void commit() override {pop<void>();}

    virtual Result do_query(Query&&) override {return pop<Result&&>();}

protected:
    unique_type& iunique_;
    unique_type& hunique_;
    unique_type& funique_;
    unique_type& sunique_;

    virtual Result insert(Query&&) {return pop<Result&&>();}
    virtual Result update(Query&&) {return pop<Result&&>();}
    virtual Result remove(Query&&) {return pop<Result&&>();}

    std::vector<unique_type> insert(std::vector<IRecord>&&) {return pop<std::vector<unique_type>>();}
    void insert(std::vector<HRecord>&&, const std::vector<unique_type>&) {pop<void>();}
    void insert(std::vector<FRecord>&&, const std::vector<unique_type>&) {pop<void>();}
    void insert(std::vector<SRecord>&&) {}
};


}    // namespace mem
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__UPDATE_HANDLE_H_
