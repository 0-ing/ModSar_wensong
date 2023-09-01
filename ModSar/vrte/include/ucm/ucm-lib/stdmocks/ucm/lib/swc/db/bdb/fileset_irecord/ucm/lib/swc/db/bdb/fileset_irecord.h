//==============================================================================
// C O P Y R I G H T
//------------------------------------------------------------------------------
// Copyright (c) 2021 by Robert Bosch GmbH. All rights reserved.
//
// This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
// distribution is an offensive act against international law and may be
// prosecuted under federal law. Its content is company confidential.
//==============================================================================

/// @file         tests/VRTE_UT/mocks/ucm/lib/swc/db/bdb/fileset_irecord/ucm/lib/swc/db/bdb/fileset_irecord.h
/// @brief
/// @copyright    Robert Bosch GmbH 2021
/// @author       Vesselin Mladenov
/// @version
/// @remarks

#ifndef UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_
#define UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_

#include "ucm/lib/swc/db/query.h"
#include "ucm/lib/swc/db/bdb/fileset.h"

#include "ucm/mock/sequence.h"

namespace bosch {
namespace vrte  {
namespace ucm   {
namespace lib   {
namespace swc   {
namespace db    {
namespace bdb   {

class FileSet_IRecord
        : public FileSet
        , virtual protected ucm::mock::Sequence
{
    constexpr static const char* prefix = "";
    constexpr static const char* suffix = "";
    constexpr static const char* fsname = "irecord";
public:

    explicit FileSet_IRecord(bool wlock, const std::string& path)
    : FileSet(wlock, path + "/" + prefix + fsname + suffix)
    {}

    FileSet_IRecord(FileSet_IRecord     &&) = default;
    FileSet_IRecord(FileSet_IRecord const&) = default;

    FileSet_IRecord& operator=(FileSet_IRecord     &&) = default;
    FileSet_IRecord& operator=(FileSet_IRecord const&) = default;

    virtual ~FileSet_IRecord() = default;

    Result count (Query&&)  {return pop<Result&&>();}
    Result select(Query&&) {return pop<Result&&>();}
    Result insert(Query&&) {return pop<Result&&>();}
    Result update(Query&&) {return pop<Result&&>();}
    Result remove(Query&&) {return pop<Result&&>();}
};


}    // namespace bdb
}    // namespace db
}    // namespace swc
}    // namespace lib
}    // namespace ucm
}    // namespace vrte
}    // namespace bosch

#endif // UCM_AAP_LIBRARY_LIB_UCM_LIB_SWC_DB_BDB__FILESET_IRECORD_H_
