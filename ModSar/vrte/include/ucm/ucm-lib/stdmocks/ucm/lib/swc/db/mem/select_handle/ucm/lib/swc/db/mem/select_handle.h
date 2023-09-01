//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/mem/select_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_

#include <vector>
#include <memory>
#include <type_traits>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/handle.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace mem   {


class SelectHandle
        : public Handle
        , virtual protected ucm::mock::Sequence
{
public:
    explicit SelectHandle(Mutex& mutex, const Tuple& tuple,
                          std::vector<IRecord>& irecords,
                          std::vector<HRecord>& hrecords,
                          std::vector<FRecord>& frecords,
                          std::vector<SRecord>& srecords)
    : SelectHandle(false, mutex, tuple, irecords, hrecords, frecords, srecords)
    {}

    SelectHandle(SelectHandle     &&) = default;
    SelectHandle(SelectHandle const&) = delete;

    SelectHandle& operator=(SelectHandle     &&) = default;
    SelectHandle& operator=(SelectHandle const&) = delete;

    virtual ~SelectHandle() = default;

    virtual void abort() noexcept override {pop<void>();}

    virtual void commit() override {pop<void>();}

    virtual Result do_query(Query&&) override  {return pop<Result&&>();}

protected:
    std::vector<IRecord>& irecords_;
    std::vector<HRecord>& hrecords_;
    std::vector<FRecord>& frecords_;
    std::vector<SRecord>& srecords_;

    explicit SelectHandle(bool wlock,
                          Mutex& mutex, const Tuple& tuple,
                          std::vector<IRecord>& irecords,
                          std::vector<HRecord>& hrecords,
                          std::vector<FRecord>& frecords,
                          std::vector<SRecord>& srecords)
    : Handle(wlock, mutex, tuple)
    , irecords_{irecords}
    , hrecords_{hrecords}
    , frecords_{frecords}
    , srecords_{srecords}
    {}

    virtual Result count(Query&&)  {return pop<Result&&>();}

    virtual Result select(Query&&)  {return pop<Result&&>();}
};


}    // namespace mem
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_MEM__SELECT_HANDLE_H_
