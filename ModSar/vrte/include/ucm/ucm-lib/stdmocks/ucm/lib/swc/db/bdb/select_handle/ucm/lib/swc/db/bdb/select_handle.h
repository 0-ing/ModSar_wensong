//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         ucm/lib/swc/db/bdb/select_handle.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__SELECT_HANDLE_H_
#define UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__SELECT_HANDLE_H_

#include <vector>
#include <memory>
#include <type_traits>

#include "ucm/mock/sequence.h"
#include "ucm/lib/swc/db/handle.h"
#include "ucm/lib/swc/db/bdb/fileset_irecord.h"
#include "ucm/lib/swc/db/bdb/fileset_hrecord.h"
#include "ucm/lib/swc/db/bdb/fileset_frecord.h"
#include "ucm/lib/swc/db/bdb/fileset_srecord.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {


class SelectHandle
        : public Handle
        , virtual protected ucm::mock::Sequence
{
public:
    explicit SelectHandle(Mutex& mutex, const Tuple& tuple)
    : SelectHandle(false, mutex, tuple)
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
    FileSet_IRecord fs_irecord_;
    FileSet_HRecord fs_hrecord_;
    FileSet_FRecord fs_frecord_;
    FileSet_SRecord fs_srecord_;

    explicit SelectHandle(bool wlock, Mutex& mutex, const Tuple& tuple)
    : Handle(wlock, mutex, tuple)
    , fs_irecord_{wlock_, specs()}
    , fs_hrecord_{wlock_, specs()}
    , fs_frecord_{wlock_, specs()}
    , fs_srecord_{wlock_, specs()}
    {}

    virtual Result count(Query&&) {return pop<Result&&>();}

    virtual Result select(Query&&) {return pop<Result&&>();}
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_UCM_LIB_SWC_DB_BDB__SELECT_HANDLE_H_
